#include "moai-tb/MOAITBPopupWindow.h"

int MOAITBPopupWindow::_show ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBPopupWindow, "U" )
	u32 align    = state.GetValue < u32 >( 2, (u32)TB_ALIGN_BOTTOM );
	TBPopupAlignment alignment( (TB_ALIGN)align );
	self->GetInternal()->Show( alignment );
	return 0;
}

int MOAITBPopupWindow::_showAt ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBPopupWindow, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	u32 align = state.GetValue < u32 >( 4, (u32)TB_ALIGN_BOTTOM );
	TBPopupAlignment alignment( TBPoint( x, y ), (TB_ALIGN)align );
	self->GetInternal()->Show( alignment );
	return 0;
}

int MOAITBPopupWindow::_showWithOffset ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBPopupWindow, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	int offx = state.GetValue < int >( 4, 0 );
	int offy = state.GetValue < int >( 5, 0 );
	u32 align = state.GetValue < u32 >( 6, (u32)TB_ALIGN_BOTTOM );
	TBPopupAlignment alignment( TBPoint( x, y ), TBPoint( offx, offy ) );
	alignment.align = (TB_ALIGN)align;
	self->GetInternal()->Show( alignment );
	return 0;
}
//----------------------------------------------------------------//
MOAITBPopupWindow::MOAITBPopupWindow () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWindow )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBPopupWindow::~MOAITBPopupWindow () {
}


//----------------------------------------------------------------//
void MOAITBPopupWindow::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWindow::RegisterLuaClass( state );
}

//----------------------------------------------------------------//
void MOAITBPopupWindow::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWindow::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "show",             _show           },
		{ "showAt",           _showAt         },
		{ "showWithOffset",   _showWithOffset },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
