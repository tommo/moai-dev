#include "moai-tb/MOAITBScrollContainer.h"

int MOAITBScrollContainer::_setAdaptToContentSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetAdaptToContentSize( flag );
	return 0;
}

int MOAITBScrollContainer::_getAdaptToContentSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "U" )
	state.Push( self->GetInternal()->GetAdaptToContentSize() );
	return 1;
}

int MOAITBScrollContainer::_setAdaptContentSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetAdaptContentSize( flag );
	return 0;
}

int MOAITBScrollContainer::_getAdaptContentSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "U" )
	state.Push( self->GetInternal()->GetAdaptContentSize() );
	return 1;
}

int MOAITBScrollContainer::_setScrollMode ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "UN" )
	u32 mode    = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetScrollMode( (SCROLL_MODE)mode );
	return 0;
}

int MOAITBScrollContainer::_getScrollMode ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollContainer, "U" )
	state.Push( self->GetInternal()->GetScrollMode() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBScrollContainer::MOAITBScrollContainer () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBScrollContainer::~MOAITBScrollContainer () {
}


//----------------------------------------------------------------//
void MOAITBScrollContainer::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBScrollContainer::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setAdaptToContentSize",   _setAdaptToContentSize },
		{ "getAdaptToContentSize",   _getAdaptToContentSize },
		{ "setAdaptContentSize",   _setAdaptContentSize },
		{ "getAdaptContentSize",   _getAdaptContentSize },
		{ "getScrollMode",   _getScrollMode },
		{ "setScrollMode",   _setScrollMode },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
