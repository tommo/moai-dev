#include "moai-tb/MOAITBSelectList.h"

// int MOAITBSelectList::_setSqueezable ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "UB" )
// 	bool flag    = state.GetValue < bool >( 2, false );
// 	self->GetInternal()->SetSqueezable( flag );
// 	return 0;
// }

// int MOAITBSelectList::_getSqueezable ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "U" )
// 	state.Push( self->GetInternal()->GetSqueezable() );
// 	return 1;
// }

// int MOAITBSelectList::_setAutoRepeat ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "UB" )
// 	bool flag    = state.GetValue < bool >( 2, false );
// 	self->GetInternal()->SetAutoRepeat( flag );
// 	return 0;
// }

// int MOAITBSelectList::_getAutoRepeat ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "U" )
// 	state.Push( self->GetInternal()->GetAutoRepeat() );
// 	return 1;
// }

// int MOAITBSelectList::_setToggleMode ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "UB" )
// 	bool toggle    = state.GetValue < bool >( 2, false );
// 	self->GetInternal()->SetToggleMode( toggle );
// 	return 0;
// }

// int MOAITBSelectList::_getToggleMode ( lua_State *L ) {
// 	MOAI_LUA_SETUP( MOAITBSelectList, "U" )
// 	state.Push( self->GetInternal()->GetToggleMode() );
// 	return 1;
// }

//----------------------------------------------------------------//
MOAITBSelectList::MOAITBSelectList () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBSelectList::~MOAITBSelectList () {
}


//----------------------------------------------------------------//
void MOAITBSelectList::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBSelectList::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		// { "setSqueezable",   _setSqueezable },
		// { "getSqueezable",   _getSqueezable },
		// { "setAutoRepeat",   _setAutoRepeat },
		// { "getAutoRepeat",   _getAutoRepeat },
		// { "getToggleMode",   _getToggleMode },
		// { "setToggleMode",   _setToggleMode },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
