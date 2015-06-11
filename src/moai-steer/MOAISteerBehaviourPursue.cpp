#include "moai-steer/MOAISteerBehaviourPursue.h"

int MOAISteerBehaviourPursue::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourPursue, "UU" )
	MOAISteerController* target = state.GetLuaObject < MOAISteerController >( 2, 0 );
	MOAITransformBase* transformTarget = state.GetLuaObject < MOAITransformBase >( 2, 0 );
	if( target ) {
		self->SetTarget( target );
	}
	else if (transformTarget)
	{
		self->SetTarget( transformTarget );
	}
	self->SetPredictionTime( state.GetValue < float >( 2, 0.5f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourPursue::MOAISteerBehaviourPursue() :
	mPredictionTime( 0.5f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourPursue::~MOAISteerBehaviourPursue() {
	this->mTarget.Set( *this, 0 );
	this->mTransformTarget.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourPursue::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !mTarget && !mTransformTarget ) return false;
	
	ZLVec3D loc;
	if (mTarget)
	{
		loc = this->mTarget->GetLoc();
	}
	else if (mTransformTarget)
	{
		loc = this->mTransformTarget->GetWorldLoc();
	}

	ZLVec3D diff = loc - this->GetOwner()->GetLoc();

	float distanceSqrd   = diff.LengthSqrd();
	float speedSqrd      = this->GetOwner()->GetLinearVelocity().LengthSqrd();
	float predictionTime = this->mPredictionTime;

	if ( speedSqrd > 0 ) {
		// Calculate prediction time if speed is not too small to give a reasonable value
		float predictionTimeSqrd = distanceSqrd / speedSqrd;
		if (predictionTimeSqrd < predictionTime * predictionTime)
			predictionTime = sqrtf( predictionTimeSqrd );
	}

	// Calculate and seek/flee the predicted position of the target
	loc.Add( this->GetOwner()->GetLinearVelocity(), predictionTime ); //predicted loc

	acc.mLinear.Init( loc - this->GetOwner()->GetLoc() );
	this->GetActualLimiter()->FitMaxLinearAcceleration( acc.mLinear );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourPursue::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourPursue::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
