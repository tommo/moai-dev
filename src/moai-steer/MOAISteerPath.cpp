#include "moai-steer/MOAISteerPath.h"


int MOAISteerPath::_isLoop ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPath, "U" )
	state.Push( self->IsLoop() );
	return 1;
}

int MOAISteerPath::_getLength ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPath, "U" )
	state.Push( self->GetLength() );
	return 1;
}

int MOAISteerPath::_findNearestPoint ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPath, "U" )
	ZLVec3D from = state.GetVec3D( 2, 0.0f );
	float distance;
	state.Push( self->FindNearestPoint( from, distance ) );
	state.Push( distance );
	return 4;
}

int MOAISteerPath::_findPointOnPath ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPath, "UN" )
	float distance = state.GetValue < float >( 2, 0.0f );
	state.Push( self->FindPointOnPath( distance ) );
	return 3;
}

//----------------------------------------------------------------//
MOAISteerPath::MOAISteerPath()
{
	RTTI_SINGLE( MOAISteerPath )
}

MOAISteerPath::~MOAISteerPath() {
}


//----------------------------------------------------------------//
void MOAISteerPath::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
}

void MOAISteerPath::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ "isLoop",              _isLoop               },
    { "getLength",           _getLength            },
    { "findNearestPoint",    _findNearestPoint     },
    { "findPointOnPath",     _findPointOnPath      },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
