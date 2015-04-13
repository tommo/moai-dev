#include "moai-tb/MOAITBWindow.h"

int MOAITBWindow::_isActive ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "U" )
 	state.Push( self->GetInternal()->IsActive() );
 	return 1;
 } 

int MOAITBWindow::_activate ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "U" )
 	self->GetInternal()->Activate();
 	return 0;
 } 

int MOAITBWindow::_ensureFocus ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "U" )
 	self->GetInternal()->EnsureFocus();
 	return 0;
 } 

int MOAITBWindow::_setSettings ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "UN" )
 	u32 settings = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->SetSettings( ( WINDOW_SETTINGS )settings );
 	return 0;
 } 

int MOAITBWindow::_getSettings ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "U" )
 	u32 settings = self->GetInternal()->GetSettings();
 	state.Push( settings );
 	return 1;
 } 

int MOAITBWindow::_resizeToFitContent ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWindow, "U" )
 	u32 fitPolicy = state.GetValue < u32 >( 2, 0 );
 	self->GetInternal()->ResizeToFitContent( ( TBWindow::RESIZE_FIT )fitPolicy );
 	return 0;
 } 


//----------------------------------------------------------------//
MOAITBWindow::MOAITBWindow () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBWindow::~MOAITBWindow () {
}


//----------------------------------------------------------------//
void MOAITBWindow::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	state.SetField ( -1, "WINDOW_SETTINGS_NONE",         ( u32 )WINDOW_SETTINGS_NONE         );
	state.SetField ( -1, "WINDOW_SETTINGS_TITLEBAR",     ( u32 )WINDOW_SETTINGS_TITLEBAR     );
	state.SetField ( -1, "WINDOW_SETTINGS_RESIZABLE",    ( u32 )WINDOW_SETTINGS_RESIZABLE    );
	state.SetField ( -1, "WINDOW_SETTINGS_CLOSE_BUTTON", ( u32 )WINDOW_SETTINGS_CLOSE_BUTTON );
	state.SetField ( -1, "WINDOW_SETTINGS_CAN_ACTIVATE", ( u32 )WINDOW_SETTINGS_CAN_ACTIVATE );

	state.SetField ( -1, "WINDOW_SETTINGS_DEFAULT",      ( u32 )WINDOW_SETTINGS_DEFAULT      );

	state.SetField ( -1, "RESIZE_FIT_PREFERRED",         ( u32 )TBWindow::RESIZE_FIT_PREFERRED         );
	state.SetField ( -1, "RESIZE_FIT_MINIMAL",           ( u32 )TBWindow::RESIZE_FIT_MINIMAL           );
	state.SetField ( -1, "RESIZE_FIT_CURRENT_OR_NEEDED", ( u32 )TBWindow::RESIZE_FIT_CURRENT_OR_NEEDED );

	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBWindow::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "isActive",           _isActive           },
    { "activate",           _activate           },
    { "ensureFocus",        _ensureFocus        },
    { "setSettings",        _setSettings        },
    { "getSettings",        _getSettings        },
    { "resizeToFitContent", _resizeToFitContent },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
