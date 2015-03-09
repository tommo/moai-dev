#include "moai-steer/MOAISteerBehaviourSeparation.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourSeparation::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourSeparation, "UU" )
	MOAISteerProximity* proximity = state.GetLuaObject < MOAISteerProximity >( 2, 0 );
	if( proximity ) {
		self->SetProximity( proximity );
	}
	self->SetDecayCoefficient( state.GetValue < float >( 3, 1.0f ) );
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourSeparation::MOAISteerBehaviourSeparation() :
	mDecayCoefficient( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourSeparation::~MOAISteerBehaviourSeparation() {
	this->mProximity.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourSeparation::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mProximity ) return false;
	this->mCurrentAcceleration = &acc;
	u32 count = this->mProximity->FindNeighbors( this );
	this->mCurrentAcceleration = NULL;	
	return count > 0;
}


bool MOAISteerBehaviourSeparation::OnReportNeighbor( MOAISteerController* neighbor ) {
		ZLVec3D diff = this->GetOwner()->GetLoc() - neighbor->GetLoc();
		float distanceSqrd = diff.LengthSqrd();
		if( distanceSqrd == 0.0f ) return true;
		float maxAcceleration = this->GetActualLimiter()->GetMaxLinearAcceleration();
		// Calculate the strength of repulsion through inverse square law decay
		float strength = min( this->mDecayCoefficient / distanceSqrd, 1.0f );
		// Add the acceleration
		// Optimized code for linear.mulAdd(diff.norm(), strength);
		this->mCurrentAcceleration->mLinear.Add( diff, ( strength * maxAcceleration ) / sqrtf( distanceSqrd ) );
		return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourSeparation::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourSeparation::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
