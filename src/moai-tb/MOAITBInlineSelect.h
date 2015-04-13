#ifndef	MOAITBInlineSelect_H
#define	MOAITBInlineSelect_H

#include "MOAITBWidget.h"
#include "tb_inline_select.h"

//================================================================//
// MOAITBInlineSelect
//================================================================//

class MOAITBInlineSelect :
	public MOAITBWidget {
private:
	
	static int _setLimits          ( lua_State* L );
	static int _getLimits          ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBInlineSelect )
	MOAI_TB_CREATE_INTERNAL ( TBInlineSelect )

public:
	MOAI_TB_GET_INTERNAL    ( TBInlineSelect )

  DECL_LUA_FACTORY ( MOAITBInlineSelect )
	
	//----------------------------------------------------------------//
						MOAITBInlineSelect			();
						~MOAITBInlineSelect			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
