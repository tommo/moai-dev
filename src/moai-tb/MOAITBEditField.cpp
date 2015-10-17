#include "moai-tb/MOAITBEditField.h"

int MOAITBEditField::_setMultiline ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetMultiline( flag );
	return 0;
}


int MOAITBEditField::_isMultiline ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetMultiline() );
	return 1;
}

int MOAITBEditField::_setStyling ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetStyling( flag );
	return 0;
}

int MOAITBEditField::_isStyling ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetStyling() );
	return 1;
}

int MOAITBEditField::_setReadOnly ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetReadOnly( flag );
	return 0;
}


int MOAITBEditField::_isReadOnly ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetReadOnly() );
	return 1;
}

int MOAITBEditField::_setWrapping ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetWrapping( flag );
	return 0;
}

int MOAITBEditField::_isWrapping ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetWrapping() );
	return 1;
}

int MOAITBEditField::_setAdaptToContent ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UB" )
	bool flag    = state.GetValue < bool >( 2, false );
	self->GetInternal()->SetAdaptToContentSize( flag );
	return 0;
}

int MOAITBEditField::_isAdaptToContent ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetAdaptToContentSize() );
	return 1;
}

int MOAITBEditField::_setVirtualWidth ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UN" )
	u32 width  = state.GetValue < u32 >( 2, false );
	self->GetInternal()->SetVirtualWidth( width );
	return 0;
}

int MOAITBEditField::_getVirtualWidth ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( self->GetInternal()->GetVirtualWidth() );
	return 1;
}

int MOAITBEditField::_setEditType ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UN" )
	u32 editType    = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetEditType( (EDIT_TYPE)editType );
	return 0;
}

int MOAITBEditField::_getEditType ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( (u32)self->GetInternal()->GetEditType() );
	return 1;
}

int MOAITBEditField::_setTextAlign ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "UN" )
	u32 align    = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetTextAlign( (TB_TEXT_ALIGN)align );
	return 0;
}

int MOAITBEditField::_getTextAlign ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	state.Push( (u32)self->GetInternal()->GetTextAlign() );
	return 1;
}

int MOAITBEditField::_setPlaceholderText ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "US" )
	cc8* text    = state.GetValue < cc8* >( 2, "" );
	self->GetInternal()->SetPlaceholderText( text );
	return 0;
}

int MOAITBEditField::_getPlaceholderText ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBEditField, "U" )
	TBStr s;
	if ( self->GetInternal()->GetPlaceholderText( s ) ) {
		state.Push( s.CStr() );
		return 1;
	} else {
		return 0;
	}
}


//----------------------------------------------------------------//
MOAITBEditField::MOAITBEditField () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBEditField::~MOAITBEditField () {
}


//----------------------------------------------------------------//
void MOAITBEditField::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	state.SetField ( -1, "EDIT_TYPE_TEXT",         ( u32 )EDIT_TYPE_TEXT        );
	state.SetField ( -1, "EDIT_TYPE_SEARCH",       ( u32 )EDIT_TYPE_SEARCH      );
	state.SetField ( -1, "EDIT_TYPE_PASSWORD",     ( u32 )EDIT_TYPE_PASSWORD    );
	state.SetField ( -1, "EDIT_TYPE_EMAIL",        ( u32 )EDIT_TYPE_EMAIL       );
	state.SetField ( -1, "EDIT_TYPE_PHONE",        ( u32 )EDIT_TYPE_PHONE       );
	state.SetField ( -1, "EDIT_TYPE_URL",          ( u32 )EDIT_TYPE_URL         );
	state.SetField ( -1, "EDIT_TYPE_NUMBER",       ( u32 )EDIT_TYPE_NUMBER      );
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBEditField::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setMultiline",        _setMultiline       },
		{ "isMultiline",         _isMultiline        },
		{ "setStyling",          _setStyling         },
		{ "isStyling",           _isStyling          },
		{ "setReadOnly",         _setReadOnly        },
		{ "isReadOnly",          _isReadOnly         },
		{ "setWrapping",         _setWrapping        },
		{ "isWrapping",          _isWrapping         },
		{ "setAdaptToContent",   _setAdaptToContent  },
		{ "isAdaptToContent",    _isAdaptToContent   },
		{ "setVirtualWidth",     _setVirtualWidth    },
		{ "getVirtualWidth",     _getVirtualWidth    },
		{ "setEditType",         _setEditType        },
		{ "getEditType",         _getEditType        },
		{ "setTextAlign",        _setTextAlign       },
		{ "getTextAlign",        _getTextAlign       },
		{ "setPlaceholderText",  _setPlaceholderText },
		{ "getPlaceholderText",  _getPlaceholderText },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
