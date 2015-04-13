#include "moai-tb/MOAITBLayout.h"

int MOAITBLayout::_setSpacing ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	int spacing = state.GetValue < int >( 2, 0 );
 	self->GetInternal()->SetSpacing( spacing );
 	return 0;
 }

int MOAITBLayout::_getSpacing ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "U" )
 	state.Push( self->GetInternal()->GetSpacing() );
 	return 1;
 }

int MOAITBLayout::_getOverflowScroll ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "U" )
 	state.Push( self->GetInternal()->GetOverflowScroll() );
 	return 1;
 }

int MOAITBLayout::_setOverflowScroll ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	int scroll = state.GetValue < int >( 2, 0 );
 	self->GetInternal()->SetOverflowScroll( scroll );
 	return 0;
 }

int MOAITBLayout::_setPaintOverflowFadeout ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UB" )
 	bool flag = state.GetValue < bool >( 2, 0 );
 	self->GetInternal()->SetPaintOverflowFadeout( flag );
 	return 0;
 }

int MOAITBLayout::_setLayoutSize ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutSize( (LAYOUT_SIZE)value );
 	return 0;
 }

int MOAITBLayout::_setLayoutPosition ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutPosition( (LAYOUT_POSITION)value );
 	return 0;
 }

int MOAITBLayout::_setLayoutOverflow ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutOverflow( (LAYOUT_OVERFLOW)value );
 	return 0;
 }

int MOAITBLayout::_setLayoutDistribution ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutDistribution( (LAYOUT_DISTRIBUTION)value  );
 	return 0;
 }

int MOAITBLayout::_setLayoutDistributionPosition ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutDistributionPosition( (LAYOUT_DISTRIBUTION_POSITION)value );
 	return 0;
 }

int MOAITBLayout::_setLayoutOrder ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBLayout, "UN" )
 	u32 value = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetLayoutOrder( (LAYOUT_ORDER)value );
 	return 0;
 }


//----------------------------------------------------------------//
MOAITBLayout::MOAITBLayout () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBLayout::~MOAITBLayout () {
}


//----------------------------------------------------------------//
void MOAITBLayout::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBLayout::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "getSpacing",                    _getSpacing                    },
		{ "setSpacing",                    _setSpacing                    },
		{ "getOverflowScroll",             _getOverflowScroll             },
		{ "setOverflowScroll",             _setOverflowScroll             },
		{ "setPaintOverflowFadeout",       _setPaintOverflowFadeout       },
		{ "setLayoutSize",                 _setLayoutSize                 },
		{ "setLayoutPosition",             _setLayoutPosition             },
		{ "setLayoutOverflow",             _setLayoutOverflow             },
		{ "setLayoutDistribution",         _setLayoutDistribution         },
		{ "setLayoutDistributionPosition", _setLayoutDistributionPosition },
		{ "setLayoutOrder",                _setLayoutOrder                },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
