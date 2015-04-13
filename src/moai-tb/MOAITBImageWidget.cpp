#include "moai-tb/MOAITBImageWidget.h"

int MOAITBImageWidget::_setImage ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBImageWidget, "US" )
	cc8* fileName = state.GetValue < cc8* >( 2, "" );
	self->GetInternal()->SetImage( fileName );
	return 0;
}

//----------------------------------------------------------------//
MOAITBImageWidget::MOAITBImageWidget () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBImageWidget::~MOAITBImageWidget () {
}


//----------------------------------------------------------------//
void MOAITBImageWidget::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBImageWidget::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setImage",    _setImage },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
