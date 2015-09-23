#include "moai-steer/MOAISteerBehaviourEvade.h"

int MOAISteerBehaviourEvade::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourEvade, "UU" )
	MOAISteerController* target = state.GetLuaObject < MOAISteerController >( 2, 0 );
	if( target ) {
		self->SetTarget( target );
	}
	self->SetPredictionTime( state.GetValue < float >( 3, 0.5f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourEvade::MOAISteerBehaviourEvade() :
	mPredictionTime( 0.5f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourEvade::~MOAISteerBehaviourEvade() {
	this->mTarget.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourEvade::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !mTarget ) return false;
	
	ZLVec3D loc  = this->mTarget->GetLoc();
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

	acc.mLinear.Init( this->GetOwner()->GetLoc() - loc ); //opposite of PURSUE
	this->GetActualLimiter()->FitMaxLinearAcceleration( acc.mLinear );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourEvade::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourEvade::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
