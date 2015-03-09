#include "moai-steer/MOAISteerBehaviourScript.h"

int MOAISteerBehaviourScript::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "UF" )
	self->mOnCalculate.SetRef ( *self, state, 2 );
	return 0;
}

int MOAISteerBehaviourScript::_getMaxLinearSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	if( !self->GetOwner() ) return 0;
	state.Push( self->GetActualLimiter()->GetMaxLinearSpeed() );
	return 1;
}

int MOAISteerBehaviourScript::_getMaxAngularSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	if( !self->GetOwner() ) return 0;
	state.Push( self->GetActualLimiter()->GetMaxAngularSpeed() );
	return 1;
}

int MOAISteerBehaviourScript::_getMaxLinearAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	if( !self->GetOwner() ) return 0;
	state.Push( self->GetActualLimiter()->GetMaxLinearAcceleration() );
	return 1;
}

int MOAISteerBehaviourScript::_getMaxAngularAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	if( !self->GetOwner() ) return 0;
	state.Push( self->GetActualLimiter()->GetMaxAngularAcceleration() );
	return 1;
}

int MOAISteerBehaviourScript::_setLinearAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	ZLVec3D acc = state.GetVec3D( 2, 0.0f );
	self->mLinearAcceleration = acc;
	return 0;
}

int MOAISteerBehaviourScript::_setAngularAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourScript, "U" )
	float acc = state.GetValue < float >( 2, 0.0f );
	self->mAngularAcceleration = acc;
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourScript::MOAISteerBehaviourScript() :
	mLinearAcceleration( 0.0f, 0.0f, 0.0f ),
	mAngularAcceleration( 0.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourScript::~MOAISteerBehaviourScript() {
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourScript::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if ( this->mOnCalculate ) {
	
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		if ( this->mOnCalculate.PushRef ( state )) {
			this->PushLuaUserdata( state );
			this->GetOwner()->PushLuaUserdata( state );
			state.Push( elapsed );
			state.Push( delta );
			state.DebugCall ( 4, 1 );
			if( !state.GetValue < bool >( -1, true ) ) return false;
		}
	}
	acc.Init( this->mLinearAcceleration, this->mAngularAcceleration );
	return true;
}

//----------------------------------------------------------------//
void MOAISteerBehaviourScript::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourScript::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",                     _setup                     },
		{ "setLinearAcceleration",     _setLinearAcceleration     },
    { "setAngularAcceleration",    _setAngularAcceleration    },
    { "getMaxLinearAcceleration",  _getMaxLinearAcceleration  },
    { "getMaxAngularAcceleration", _getMaxAngularAcceleration },
    { "getMaxLinearSpeed",         _getMaxLinearSpeed         },
    { "getMaxAngularSpeed",        _getMaxAngularSpeed        },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
