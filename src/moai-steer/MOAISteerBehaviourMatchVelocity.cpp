#include "moai-steer/MOAISteerBehaviourMatchVelocity.h"

int MOAISteerBehaviourMatchVelocity::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourMatchVelocity, "UUN" )
	MOAISteerController* target = state.GetLuaObject < MOAISteerController >( 2, 0 );
	if( !target ) return 0;
	self->SetTarget( target );
	self->SetTimeToTarget( state.GetValue < float >( 3, 1.0f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourMatchVelocity::MOAISteerBehaviourMatchVelocity() :
	mTimeToTarget( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourMatchVelocity::~MOAISteerBehaviourMatchVelocity() {
	this->mTarget.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourMatchVelocity::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	// Acceleration tries to get to the target velocity without exceeding max acceleration
	if( !this->mTarget ) return false;

	ZLVec3D targetAcc( this->mTarget->GetLinearVelocity() );
	targetAcc.Sub( this->GetOwner()->GetLinearVelocity() );
	targetAcc.Scale( 1.0f/mTimeToTarget );
	this->GetActualLimiter()->LimitLinearAcceleration( targetAcc );
	acc.mLinear.Init( targetAcc );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourMatchVelocity::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourMatchVelocity::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",   _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
