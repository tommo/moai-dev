#include "moai-tb/MOAITBTabContainer.h"

//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAITBTabLayout::MOAITBTabLayout () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

MOAITBTabLayout::~MOAITBTabLayout () {
}

//----------------------------------------------------------------//
void MOAITBTabLayout::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

void MOAITBTabLayout::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL  }
	};
	luaL_register ( state, 0, regTable );
}



//----------------------------------------------------------------//
//----------------------------------------------------------------//
int MOAITBTabContainer::_setAlignment ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "UN" )
	u32 align    = state.GetValue < u32 >( 2, false );
	self->GetInternal()->SetAlignment( (TB_ALIGN)align );
	return 0;
}

int MOAITBTabContainer::_getAlignment ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "U" )
	state.Push( self->GetInternal()->GetAlignment() );
	return 1;
}

int MOAITBTabContainer::_setCurrentPage ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "UN" )
	u32 pageIdx    = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetCurrentPage( pageIdx );
	return 0;
}

int MOAITBTabContainer::_getCurrentPage ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "U" )
	state.Push( self->GetInternal()->GetCurrentPage() );
	return 1;
}

int MOAITBTabContainer::_getPageCount ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "UN" )
	state.Push( self->GetInternal()->GetNumPages() );
	return 1;
}

int MOAITBTabContainer::_getCurrentPageWidget ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "U" )
	PushTBWidgetOrNil( state, self->GetInternal()->GetCurrentPageWidget() );
	return 1;
}

int MOAITBTabContainer::_getTabLayout ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTabContainer, "U" )
	PushTBWidgetOrNil( state, self->GetInternal()->GetTabLayout() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBTabContainer::MOAITBTabContainer () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBTabContainer::~MOAITBTabContainer () {
}


//----------------------------------------------------------------//
void MOAITBTabContainer::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBTabContainer::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setAlignment",           _setAlignment         },
		{ "getAlignment",           _getAlignment         },
		{ "setCurrentPage",         _setCurrentPage       },
		{ "getCurrentPage",         _getCurrentPage       },
		{ "getPageCount",           _getPageCount         },
		{ "getCurrentPageWidget",   _getCurrentPageWidget },
		{ "getTabLayout",           _getTabLayout         },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
