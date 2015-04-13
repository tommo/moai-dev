#ifndef	MOAITBCOMMON_H
#define	MOAITBCOMMON_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// COMMON MACRO
//================================================================//
#define MOAI_TB_EMPTY_WIDGET( clazz, baseclazz ) \
class MOAITB##clazz: public MOAITB##baseclazz {\
private:\
	MOAI_TB_NEW( MOAITB##clazz )\
	MOAI_TB_CREATE_INTERNAL ( TB##clazz )\
public:\
	MOAI_TB_GET_INTERNAL    ( TB##clazz )\
  DECL_LUA_FACTORY ( MOAITB##clazz )\
	MOAITB##clazz			() { RTTI_BEGIN RTTI_EXTEND( MOAITB##baseclazz ) RTTI_END };\
	~MOAITB##clazz			() {};\
	void RegisterLuaClass ( MOAILuaState& state ) {\
		MOAITB##baseclazz::RegisterLuaClass( state );\
		luaL_Reg regTable [] = { { "new", _new }, { NULL,  NULL } };\
		luaL_register ( state, 0, regTable );\
	};\
	void RegisterLuaFuncs ( MOAILuaState& state ) {\
		MOAITB##baseclazz::RegisterLuaFuncs( state );\
	};\
};

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( ClickLabel, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( SkinImage, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( Separator, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( Mover, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( Resizer, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( Dimmer, Widget ) ;

//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( Container, Widget ) ;
#endif
