#include "moai-tb/MOAITBSlider.h"

int MOAITBSlider::_setLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSlider, "UNNN" )
	float min  = state.GetValue < float >( 2, 0.0 );
	float max  = state.GetValue < float >( 3, 0.0 );
	self->GetInternal()->SetLimits( min, max );
	return 0;
}

int MOAITBSlider::_getLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSlider, "U" )
	state.Push( self->GetInternal()->GetMinValue() );
	state.Push( self->GetInternal()->GetMaxValue() );
	return 3;
}

int MOAITBSlider::_getStep ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBSlider, "U" )
	state.Push( self->GetInternal()->GetSmallStep() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBSlider::MOAITBSlider () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBSlider::~MOAITBSlider () {
}


//----------------------------------------------------------------//
void MOAITBSlider::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBSlider::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setLimits",           _setLimits         },
		{ "getLimits",           _getLimits         },
		{ "getStep",             _getStep           },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
