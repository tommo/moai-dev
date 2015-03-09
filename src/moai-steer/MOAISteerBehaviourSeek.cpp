#include "moai-steer/MOAISteerBehaviourSeek.h"

int MOAISteerBehaviourSeek::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourSeek, "UU" )
	MOAITransformBase* target = state.GetLuaObject < MOAITransformBase >( 2, 0 );
	if( target ) {
		self->SetTarget( target );
	}
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourSeek::MOAISteerBehaviourSeek() :
	mTarget( 0 )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourSeek::~MOAISteerBehaviourSeek() {
	if( this->mTarget ) {
		this->LuaRelease( this->mTarget );
	}
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourSeek::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	//TODO
	if( !mTarget ) return false;
	ZLVec3D v( this->mTarget->GetWorldLoc() );
	v.Sub( this->GetOwner()->GetLoc() );
	this->GetActualLimiter()->FitMaxLinearAcceleration( v );
	acc.mLinear.Init( v );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourSeek::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourSeek::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
