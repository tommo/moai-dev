#ifndef	MOAITBTEXTFIELD_H
#define	MOAITBTEXTFIELD_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// MOAITBTextField
//================================================================//

class MOAITBTextField :
	public MOAITBWidget {
public:
	// enum Events{
	// 	EVENT_CLICK = MOAITBLabel::TOTAL_EVENTS,
	// 	EVENT_DOWN,
	// 	EVENT_UP,
	// 	EVENT_TOGGLE,
	// 	TOTAL_EVENTS,
	// };

private:
	
	static int _setSqueezable    ( lua_State* L );
	static int _getSqueezable    ( lua_State* L );
	static int _setTextAlign     ( lua_State* L );
	static int _getTextAlign     ( lua_State* L );
	

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBTextField )
	MOAI_TB_CREATE_INTERNAL ( TBTextField )

protected:
	// virtual void ConnectEvents() {
	// 	MOAITBLabel::ConnectEvents();
	// 	ConnectEventCallBack( GetInternalControl()->onPress,  EVENT_CLICK );
	// 	ConnectEventCallBack( GetInternalControl()->onDown,   EVENT_DOWN );
	// 	ConnectEventCallBack( GetInternalControl()->onUp,     EVENT_UP );
	// 	ConnectEventCallBack( GetInternalControl()->onToggle, EVENT_TOGGLE );
	// };

public:
	MOAI_TB_GET_INTERNAL    ( TBTextField )

  DECL_LUA_FACTORY ( MOAITBTextField )
	
	//----------------------------------------------------------------//
						MOAITBTextField			();
						~MOAITBTextField			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
