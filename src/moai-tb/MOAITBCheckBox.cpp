#include "moai-tb/MOAITBCheckBox.h"

//----------------------------------------------------------------//
//MOAITBRadioCheckBox
//----------------------------------------------------------------//
MOAITBRadioCheckBox::MOAITBRadioCheckBox () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBRadioCheckBox::~MOAITBRadioCheckBox () {
}


//----------------------------------------------------------------//
void MOAITBRadioCheckBox::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBRadioCheckBox::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL  }
	};
	luaL_register ( state, 0, regTable );
}


//----------------------------------------------------------------//
//MOAITBCheckBox
//----------------------------------------------------------------//
MOAITBCheckBox::MOAITBCheckBox () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBRadioCheckBox )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBCheckBox::~MOAITBCheckBox () {
}

//----------------------------------------------------------------//
void MOAITBCheckBox::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}
//----------------------------------------------------------------//
void MOAITBCheckBox::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL  }
	};
	luaL_register ( state, 0, regTable );
}



//----------------------------------------------------------------//
// MOAITBRadioButton
//----------------------------------------------------------------//
MOAITBRadioButton::MOAITBRadioButton () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBRadioCheckBox )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBRadioButton::~MOAITBRadioButton () {
}

//----------------------------------------------------------------//
void MOAITBRadioButton::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}
//----------------------------------------------------------------//
void MOAITBRadioButton::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL  }
	};
	luaL_register ( state, 0, regTable );
}
