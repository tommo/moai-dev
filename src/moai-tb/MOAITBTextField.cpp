#include "moai-tb/MOAITBTextField.h"

int MOAITBTextField::_setSqueezable ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTextField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetSqueezable( flag );
	return 0;
}

int MOAITBTextField::_getSqueezable ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTextField, "U" )
	state.Push( self->GetInternal()->GetSqueezable() );
	return 1;
}

int MOAITBTextField::_setTextAlign ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTextField, "UN" )
	u32 align    = state.GetValue < u32 >( 2, false );
	self->GetInternal()->SetTextAlign( (TB_TEXT_ALIGN)align );
	return 0;
}

int MOAITBTextField::_getTextAlign ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBTextField, "U" )
	state.Push( (u32)self->GetInternal()->GetTextAlign() );
	return 1;
}

//----------------------------------------------------------------//
MOAITBTextField::MOAITBTextField () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBTextField::~MOAITBTextField () {
}


//----------------------------------------------------------------//
void MOAITBTextField::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	state.SetField ( -1, "TB_TEXT_ALIGN_LEFT",     ( u32 )TB_TEXT_ALIGN_LEFT    );
	state.SetField ( -1, "TB_TEXT_ALIGN_RIGHT",    ( u32 )TB_TEXT_ALIGN_RIGHT   );
	state.SetField ( -1, "TB_TEXT_ALIGN_CENTER",   ( u32 )TB_TEXT_ALIGN_CENTER  );

	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBTextField::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setSqueezable",   _setSqueezable  },
		{ "getSqueezable",   _getSqueezable  },
		{ "setTextAlign",    _setTextAlign   },
		{ "getTextAlign",    _getTextAlign   },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
