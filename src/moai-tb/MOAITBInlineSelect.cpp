#include "moai-tb/MOAITBInlineSelect.h"

int MOAITBInlineSelect::_setLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBInlineSelect, "UNNN" )
	float min  = state.GetValue < float >( 2, 0.0 );
	float max  = state.GetValue < float >( 3, 0.0 );
	self->GetInternal()->SetLimits( min, max );
	return 0;
}

int MOAITBInlineSelect::_getLimits ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBInlineSelect, "U" )
	state.Push( self->GetInternal()->GetMinValue() );
	state.Push( self->GetInternal()->GetMaxValue() );
	return 3;
}


//----------------------------------------------------------------//
MOAITBInlineSelect::MOAITBInlineSelect () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBInlineSelect::~MOAITBInlineSelect () {
}


//----------------------------------------------------------------//
void MOAITBInlineSelect::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBInlineSelect::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setLimits",           _setLimits         },
		{ "getLimits",           _getLimits         },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
