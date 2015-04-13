#ifndef	MOAITBSLIDER_H
#define	MOAITBSLIDER_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// MOAITBSlider
//================================================================//

class MOAITBSlider :
	public MOAITBWidget {
private:
	
	static int _setLimits          ( lua_State* L );
	static int _getLimits          ( lua_State* L );
	static int _getStep            ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBSlider )
	MOAI_TB_CREATE_INTERNAL ( TBSlider )

public:
	MOAI_TB_GET_INTERNAL    ( TBSlider )

  DECL_LUA_FACTORY ( MOAITBSlider )
	
	//----------------------------------------------------------------//
						MOAITBSlider			();
						~MOAITBSlider			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
