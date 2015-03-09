#include "moai-steer/MOAISteerBehaviourFlee.h"

int MOAISteerBehaviourFlee::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourFlee, "UU" )
	MOAITransformBase* target = state.GetLuaObject < MOAITransformBase >( 2, 0 );
	if( target ) {
		self->SetTarget( target );
	}
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourFlee::MOAISteerBehaviourFlee() :
	mTarget( 0 )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourFlee::~MOAISteerBehaviourFlee() {
	if( this->mTarget ) {
		this->LuaRelease( this->mTarget );
	}
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourFlee::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !mTarget ) return false;
	ZLVec3D v( this->GetOwner()->GetLoc() );
	v.Sub( this->mTarget->GetWorldLoc() );
	this->GetActualLimiter()->FitMaxLinearAcceleration( v );
	
	acc.mLinear.Init( v );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourFlee::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourFlee::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
