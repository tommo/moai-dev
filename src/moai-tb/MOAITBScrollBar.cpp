#include "moai-tb/MOAITBScrollBar.h"

int MOAITBScrollBar::_setLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollBar, "UNNN" )
	float min  = state.GetValue < float >( 2, 0.0 );
	float max  = state.GetValue < float >( 3, 0.0 );
	float span = state.GetValue < float >( 4, 0.0 );
	self->GetInternal()->SetLimits( min, max, span );
	return 0;
}

int MOAITBScrollBar::_getLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollBar, "U" )
	state.Push( self->GetInternal()->GetMinValue() );
	state.Push( self->GetInternal()->GetMaxValue() );
	state.Push( self->GetInternal()->GetVisible()  );
	return 3;
}

int MOAITBScrollBar::_canScroll ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollBar, "U" )
	state.Push( self->GetInternal()->CanScroll() );
	return 1;
}

int MOAITBScrollBar::_canScrollNegative ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollBar, "U" )
	state.Push( self->GetInternal()->CanScrollNegative() );
	return 1;
}

int MOAITBScrollBar::_canScrollPositive ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBScrollBar, "U" )
	state.Push( self->GetInternal()->CanScrollPositive() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBScrollBar::MOAITBScrollBar () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBScrollBar::~MOAITBScrollBar () {
}


//----------------------------------------------------------------//
void MOAITBScrollBar::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBScrollBar::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setLimits",           _setLimits         },
		{ "getLimits",           _getLimits         },
		{ "canScroll",           _canScroll         },
		{ "canScrollNegative",   _canScrollNegative },
		{ "canScrollPositive",   _canScrollPositive },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
