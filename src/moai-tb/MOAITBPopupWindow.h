#ifndef	MOAITBPOPUPWINDOW_H
#define	MOAITBPOPUPWINDOW_H

#include "MOAITBWindow.h"
#include "tb_popup_window.h"

//================================================================//
// MOAITBPopupWindow
//================================================================//

class MOAITBPopupWindow :
	public MOAITBWindow {
private:
	
	static int _show           ( lua_State* L );
	static int _showAt         ( lua_State* L );
	static int _showWithOffset ( lua_State* L );

	//----------------------------------------------------------------//
	// MOAI_TB_NEW( MOAITBPopupWindow )
	// MOAI_TB_CREATE_INTERNAL ( TBPopupWindow )

public:
	MOAI_TB_GET_INTERNAL    ( TBPopupWindow )

  DECL_LUA_FACTORY ( MOAITBPopupWindow )
	
	//----------------------------------------------------------------//
						MOAITBPopupWindow			();
						~MOAITBPopupWindow			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
