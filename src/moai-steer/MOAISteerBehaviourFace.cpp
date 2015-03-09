#include "moai-steer/MOAISteerBehaviourFace.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourFace::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourFace, "UU" )
	MOAITransformBase* target = state.GetLuaObject < MOAITransformBase >( 2, 0 );
	if( target ) {
		self->SetTarget( target );
	}
	self->SetTimeToTarget      ( state.GetValue < float >( 3, 1.0f )  );
	self->SetAlignTolerance    ( state.GetValue < float >( 4, 10.0f ) );
	self->SetDecelerationRadius( state.GetValue < float >( 5, 30.0f ) );
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourFace::MOAISteerBehaviourFace()
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviourReachOrientation )
	RTTI_END
}

MOAISteerBehaviourFace::~MOAISteerBehaviourFace() {
	this->mTarget.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourFace::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mTarget ) return false;
	ZLVec3D diff = this->mTarget->GetWorldLoc() - this->GetOwner()->GetLoc();
	if( diff.LengthSqrd() == 0.0f ) return false;
	float angle = atan2( diff.mY, diff.mX );
	this->SetTargetOrientation( angle * R2D );
	return MOAISteerBehaviourReachOrientation::OnCalculate( acc, elapsed, delta );
}


//----------------------------------------------------------------//
void MOAISteerBehaviourFace::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviourReachOrientation::RegisterLuaClass( state );
}

void MOAISteerBehaviourFace::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviourReachOrientation::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
