#ifndef	MOAITBScrollBar_H
#define	MOAITBScrollBar_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// MOAITBScrollBar
//================================================================//

class MOAITBScrollBar :
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
	
	static int _setLimits          ( lua_State* L );
	static int _getLimits          ( lua_State* L );
	static int _canScroll          ( lua_State* L );
	static int _canScrollNegative  ( lua_State* L );
	static int _canScrollPositive  ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBScrollBar )
	MOAI_TB_CREATE_INTERNAL ( TBScrollBar )

protected:
	// virtual void ConnectEvents() {
	// 	MOAITBLabel::ConnectEvents();
	// 	ConnectEventCallBack( GetInternalControl()->onPress,  EVENT_CLICK );
	// 	ConnectEventCallBack( GetInternalControl()->onDown,   EVENT_DOWN );
	// 	ConnectEventCallBack( GetInternalControl()->onUp,     EVENT_UP );
	// 	ConnectEventCallBack( GetInternalControl()->onToggle, EVENT_TOGGLE );
	// };

public:
	MOAI_TB_GET_INTERNAL    ( TBScrollBar )

  DECL_LUA_FACTORY ( MOAITBScrollBar )
	
	//----------------------------------------------------------------//
						MOAITBScrollBar			();
						~MOAITBScrollBar			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
