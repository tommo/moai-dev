#ifndef	MOAITBCHECKBOX_H
#define	MOAITBCHECKBOX_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// MOAITBRadioCheckBox
//================================================================//

class MOAITBRadioCheckBox :
	public MOAITBWidget {
private:
	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBRadioCheckBox )
	MOAI_TB_CREATE_INTERNAL ( TBRadioCheckBox )
public:
	MOAI_TB_GET_INTERNAL    ( TBRadioCheckBox )
  DECL_LUA_FACTORY ( MOAITBRadioCheckBox )
	//----------------------------------------------------------------//
						MOAITBRadioCheckBox			();
						~MOAITBRadioCheckBox			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


//================================================================//
// MOAITBCheckBox
//================================================================//

class MOAITBCheckBox :
	public MOAITBRadioCheckBox {
private:
	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBCheckBox )
	MOAI_TB_CREATE_INTERNAL ( TBRadioCheckBox )
public:
	MOAI_TB_GET_INTERNAL    ( TBRadioCheckBox )
  DECL_LUA_FACTORY ( MOAITBCheckBox )
	//----------------------------------------------------------------//
						MOAITBCheckBox			();
						~MOAITBCheckBox			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


//================================================================//
// MOAITBRadioButton
//================================================================//

class MOAITBRadioButton :
	public MOAITBRadioCheckBox {
private:
	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBRadioButton )
	MOAI_TB_CREATE_INTERNAL ( TBRadioCheckBox )
public:
	MOAI_TB_GET_INTERNAL    ( TBRadioCheckBox )
  DECL_LUA_FACTORY ( MOAITBRadioButton )
	//----------------------------------------------------------------//
						MOAITBRadioButton			();
						~MOAITBRadioButton			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
