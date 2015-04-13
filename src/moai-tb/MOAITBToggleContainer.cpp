#include "moai-tb/MOAITBToggleContainer.h"
//----------------------------------------------------------------//
//----------------------------------------------------------------//
int MOAITBToggleContainer::_setToggle ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBToggleContainer, "UN" )
	u32 toggle    = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetToggle( (TBToggleContainer::TOGGLE)toggle );
	return 0;
}

int MOAITBToggleContainer::_getToggle ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBToggleContainer, "U" )
	state.Push( (u32)self->GetInternal()->GetToggle() );
	return 1;
}

int MOAITBToggleContainer::_setInvert ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBToggleContainer, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetInvert( flag );
	return 0;
}

int MOAITBToggleContainer::_getInvert ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBToggleContainer, "U" )
	state.Push( self->GetInternal()->GetInvert() );
	return 1;
}

int MOAITBToggleContainer::_isOn ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBToggleContainer, "U" )
	state.Push( self->GetInternal()->GetIsOn() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBToggleContainer::MOAITBToggleContainer () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBToggleContainer::~MOAITBToggleContainer () {
}


//----------------------------------------------------------------//
void MOAITBToggleContainer::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	state.SetField ( -1, "TOGGLE_NOTHING",    ( u32 )TBToggleContainer::TOGGLE_NOTHING    );
	state.SetField ( -1, "TOGGLE_ENABLED",    ( u32 )TBToggleContainer::TOGGLE_ENABLED    );
	state.SetField ( -1, "TOGGLE_OPACITY",    ( u32 )TBToggleContainer::TOGGLE_OPACITY    );
	state.SetField ( -1, "TOGGLE_EXPANDED",   ( u32 )TBToggleContainer::TOGGLE_EXPANDED   );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBToggleContainer::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setToggle",   _setToggle },
		{ "getToggle",   _getToggle },
		{ "setInvert",   _setInvert },
		{ "getInvert",   _getInvert },
		{ "isOn",        _isOn      },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}


//----------------------------------------------------------------//
//----------------------------------------------------------------//

int MOAITBSection::_getLayout ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSection, "U" )
	PushTBWidgetOrNil( state, self->GetInternal()->GetLayout() );
	return 1;
}

int MOAITBSection::_getHeader ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSection, "U" )
	PushTBWidgetOrNil( state, self->GetInternal()->GetHeader() );
	return 1;
}

int MOAITBSection::_getContainer ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSection, "U" )
	PushTBWidgetOrNil( state, self->GetInternal()->GetContainer() );
	return 1;
}

int MOAITBSection::_setPendingScrollIntoView ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSection, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetPendingScrollIntoView( flag );
	return 0;
}


//----------------------------------------------------------------//
MOAITBSection::MOAITBSection () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBSection::~MOAITBSection () {
}

//----------------------------------------------------------------//
void MOAITBSection::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBSection::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "getLayout",                  _getLayout                },
		{ "getHeader",                  _getHeader                },
		{ "getContainer",               _getContainer             },
		{ "setPendingScrollIntoView",   _setPendingScrollIntoView },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
