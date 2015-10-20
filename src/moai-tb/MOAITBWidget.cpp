#include "MOAITBWidget.h"
#include "MOAITBMgr.h"
#include "MOAITBSkin.h"
#include "tb_widgets.h"
#include "tb_window.h"
#include "tb_popup_window.h"


//----------------------------------------------------------------//
//----------------------------------------------------------------//
int MOAITBWidgetEvent::_getType ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( (u32)self->mEvent->type );
 	return 1;
 }

int MOAITBWidgetEvent::_getWidget ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	MOAITBWidget::PushTBWidgetOrNil( state, self->mEvent->target );
 	return 1;
 }

int MOAITBWidgetEvent::_getLoc ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->target_x );
 	state.Push( self->mEvent->target_y );
 	return 2;
 }

int MOAITBWidgetEvent::_getDelta ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->delta_x );
 	state.Push( self->mEvent->delta_y );
 	return 2;
 }

int MOAITBWidgetEvent::_getCount ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->count );
 	return 1;
 }

int MOAITBWidgetEvent::_getKey ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->key );
 	return 1;
 }

int MOAITBWidgetEvent::_getSpecialKey ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->special_key );
 	return 1;
 }

int MOAITBWidgetEvent::_getModifiers ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( (u32)self->mEvent->modifierkeys );
 	return 1;
 }

int MOAITBWidgetEvent::_hasModifiers ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "UN" )
 	u32 flags = state.GetValue < u32 >( 2, 0 );
 	bool checked = ( self->mEvent->modifierkeys & flags ) != 0;
 	state.Push( checked );
 	return 1;
 }

int MOAITBWidgetEvent::_getRefID ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( (u32)self->mEvent->ref_id );
 	return 1;
 }

int MOAITBWidgetEvent::_isTouch ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->touch );
 	return 1;
 }

int MOAITBWidgetEvent::_isPointerEvent ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->IsPointerEvent() );
 	return 1;
 }

int MOAITBWidgetEvent::_isKeyEvent ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidgetEvent, "U" )
 	state.Push( self->mEvent->IsKeyEvent() );
 	return 1;
 }


//----------------------------------------------------------------//
MOAITBWidgetEvent::MOAITBWidgetEvent () {
	RTTI_SINGLE ( MOAITBWidgetEvent )
}

MOAITBWidgetEvent::~MOAITBWidgetEvent () {
}


//----------------------------------------------------------------//
void MOAITBWidgetEvent::RegisterLuaClass ( MOAILuaState& state ) {
	//TB EVENT TYPES
	state.SetField ( -1, "EVENT_TYPE_CLICK",         ( u32 ) EVENT_TYPE_CLICK         );
	state.SetField ( -1, "EVENT_TYPE_LONG_CLICK",    ( u32 ) EVENT_TYPE_LONG_CLICK    );
	state.SetField ( -1, "EVENT_TYPE_POINTER_DOWN",  ( u32 ) EVENT_TYPE_POINTER_DOWN  );
	state.SetField ( -1, "EVENT_TYPE_POINTER_UP",    ( u32 ) EVENT_TYPE_POINTER_UP    );
	state.SetField ( -1, "EVENT_TYPE_POINTER_MOVE",  ( u32 ) EVENT_TYPE_POINTER_MOVE  );
	state.SetField ( -1, "EVENT_TYPE_WHEEL",         ( u32 ) EVENT_TYPE_WHEEL         );
	state.SetField ( -1, "EVENT_TYPE_KEY_DOWN",      ( u32 ) EVENT_TYPE_KEY_DOWN      );
	state.SetField ( -1, "EVENT_TYPE_KEY_UP",        ( u32 ) EVENT_TYPE_KEY_UP        );
	state.SetField ( -1, "EVENT_TYPE_SHORTCUT",      ( u32 ) EVENT_TYPE_SHORTCUT      );
	state.SetField ( -1, "EVENT_TYPE_CONTEXT_MENU",  ( u32 ) EVENT_TYPE_CONTEXT_MENU  );
	state.SetField ( -1, "EVENT_TYPE_FILE_DROP",     ( u32 ) EVENT_TYPE_FILE_DROP     );
	state.SetField ( -1, "EVENT_TYPE_CHANGED",       ( u32 ) EVENT_TYPE_CHANGED       );
}

//----------------------------------------------------------------//
void MOAITBWidgetEvent::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ "getType",        _getType        },
		{ "getWidget",      _getWidget      },
		{ "getLoc",         _getLoc         },
		{ "getDelta",       _getDelta       },
		{ "getCount",       _getCount       },
		{ "getKey",         _getKey         },
		{ "getSpecialKey",  _getSpecialKey  },
		{ "getModifiers",   _getModifiers   },
		{ "hasModifiers",   _hasModifiers   },
		{ "getRefID",       _getRefID       },
		{ "isTouch",        _isTouch        },
		{ "isPointerEvent", _isPointerEvent },
		{ "isKeyEvent",     _isKeyEvent     },
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
}



//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAITBWidget* MOAITBWidgetListener::GetMOAITBWidget( TBWidget *widget ) {
	MOAITBWidgetRef* ref = static_cast< MOAITBWidgetRef* >( widget->udata.GetObject() );
	if( ref ) {
		return ref->mOwner;
	}
	return NULL;
}

void MOAITBWidgetListener::OnWidgetDelete( TBWidget *widget ) {
	if( !MOAILuaRuntime::IsValid() ) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_DELETE, state )) {
		MOAITBWidget::PushTBWidgetOrNil( state, widget );
		state.DebugCall ( 2, 0 );
	}
}

bool MOAITBWidgetListener::OnWidgetDying( TBWidget *widget ) {
	if( !MOAILuaRuntime::IsValid() ) return true;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_DYING, state )) {
		MOAITBWidget::PushTBWidgetOrNil( state, widget );
		state.DebugCall ( 2, 0 );
	}
	return true;
}

void MOAITBWidgetListener::OnWidgetAdded( TBWidget *parent, TBWidget *child ) {
	if( !MOAILuaRuntime::IsValid() ) return ;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_ADD, state )) {
		MOAITBWidget::PushTBWidgetOrNil( state, parent );
		MOAITBWidget::PushTBWidgetOrNil( state, child );
		state.DebugCall ( 3, 0 );
	}
}

void MOAITBWidgetListener::OnWidgetRemove( TBWidget *parent, TBWidget *child ) {
	if( !MOAILuaRuntime::IsValid() ) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_REMOVE, state )) {
		MOAITBWidget::PushTBWidgetOrNil( state, parent );
		MOAITBWidget::PushTBWidgetOrNil( state, child );
		state.DebugCall ( 3, 0 );
	}
}

void MOAITBWidgetListener::OnWidgetFocusChanged( TBWidget *widget, bool focused ) {
	if( !MOAILuaRuntime::IsValid() ) return ;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_FOCUS_CHANGE, state )) {
		MOAITBWidget::PushTBWidgetOrNil( state, widget );
		state.Push( focused );
		state.DebugCall ( 3, 0 );
	}
}

bool MOAITBWidgetListener::OnWidgetInvokeEvent( TBWidget *widget, const TBWidgetEvent &ev ) {
	if( !MOAILuaRuntime::IsValid() ) return true;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->mOwner->PushListenerAndSelf ( MOAITBWidget::EVENT_WIDGET_EVENT, state )) {
		MOAITBWidgetEvent* event = new MOAITBWidgetEvent();
		event->mEvent = &ev;
		MOAITBWidget::PushTBWidgetOrNil( state, widget );
		event->PushLuaUserdata( state );
		state.DebugCall ( 3, 0 );
	}
	return true;
}


//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAITBWidgetRef::MOAITBWidgetRef  ( MOAITBWidget* owner )
	:mOwner( owner ) {
}

MOAITBWidgetRef::~MOAITBWidgetRef () {
	//called by TBValue delete
	this->mOwner->OnInternalLost();
}


//----------------------------------------------------------------//
//----------------------------------------------------------------//

int MOAITBWidget::_getTBClassName ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetClassName() );
	return 1;
}

int MOAITBWidget::_isValid ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->IsValid() );
	return 1;
}


int MOAITBWidget::_setRect ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int x0 = state.GetValue < int >( 2, 0 );
	int y0 = state.GetValue < int >( 3, 0 );
	int w  = state.GetValue < int >( 4, 0 );
	int h  = state.GetValue < int >( 5, 0 );
	self->GetInternal()->SetRect( TBRect( x0, -y0, w, h ) );
	return 0;
}

int MOAITBWidget::_getRect ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBRect rect = self->GetInternal()->GetRect();
	state.Push( rect.x );
	state.Push( -rect.y );
	state.Push( rect.w );
	state.Push( rect.h );
	return 4;
}

int MOAITBWidget::_getPaddingRect ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBRect rect = self->GetInternal()->GetPaddingRect();
	state.Push( rect.x );
	state.Push( -rect.y );
	state.Push( rect.w );
	state.Push( rect.h );
	return 4;
}

int MOAITBWidget::_seekLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "U" )

	float delay		= state.GetValue < float >( 4, 0.0f );
	
	if ( delay > 0.0f ) {

		u32 mode = state.GetValue < u32 >( 5, ZLInterpolate::kSmooth );		
		
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		
		TBRect rect = self->GetInternal()->GetRect();
		action->ParseForSeek ( state, 2, self, 2, mode,
			MOAITBWidgetAttr::Pack ( ATTR_X_LOC ), (float)rect.x, 0.0f,
			MOAITBWidgetAttr::Pack ( ATTR_Y_LOC ), -(float)rect.y, 0.0f
		);
		
		action->SetSpan ( delay );
		action->Start ( false );
		action->PushLuaUserdata ( state );

		return 1;
	}

	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->SetPosition( TBPoint( x, -y ) );

	return 0;
}

int MOAITBWidget::_seekSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "U" )

	float delay		= state.GetValue < float >( 4, 0.0f );
	
	if ( delay > 0.0f ) {

		u32 mode = state.GetValue < u32 >( 5, ZLInterpolate::kSmooth );		
		
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		
		TBRect rect = self->GetInternal()->GetRect();
		action->ParseForSeek ( state, 2, self, 2, mode,
			MOAITBWidgetAttr::Pack ( ATTR_X_SIZE ), (float)rect.w, 0.0f,
			MOAITBWidgetAttr::Pack ( ATTR_Y_SIZE ), (float)rect.h, 0.0f
		);
		
		action->SetSpan ( delay );
		action->Start ( false );
		action->PushLuaUserdata ( state );

		return 1;
	}

	int w = state.GetValue < int >( 2, 0 );
	int h = state.GetValue < int >( 3, 0 );
	self->GetInternal()->SetSize( w, h );
	
	return 0;
}

int MOAITBWidget::_getLoc ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBRect rect = self->GetInternal()->GetRect();
	state.Push( rect.x );
	state.Push( -rect.y );
	return 2;
}

int MOAITBWidget::_setLoc ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->SetPosition( TBPoint( x, -y ) );
	return 0;
}


int MOAITBWidget::_getSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBRect rect = self->GetInternal()->GetRect();
	state.Push( rect.w );
	state.Push( rect.h );
	return 2;
}

int MOAITBWidget::_setSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int w = state.GetValue < int >( 2, 0 );
	int h = state.GetValue < int >( 3, 0 );
	self->GetInternal()->SetSize( w, h );
	return 0;
}

int MOAITBWidget::_getMinSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	state.Push( lp0 ? lp0->min_w : TB_INVALID_DIMENSION );
	state.Push( lp0 ? lp0->min_h : TB_INVALID_DIMENSION );
	return 2;
}

int MOAITBWidget::_setMinSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int w = state.GetValue < int >( 2, TB_INVALID_DIMENSION );
	int h = state.GetValue < int >( 3, TB_INVALID_DIMENSION );
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	LayoutParams lp;
	lp.min_w  = w;
	lp.min_h  = h;
	lp.max_w  = lp0 ? lp0->max_w : TB_INVALID_DIMENSION;
	lp.max_h  = lp0 ? lp0->max_h : TB_INVALID_DIMENSION;
	lp.pref_w = lp0 ? lp0->pref_w : TB_INVALID_DIMENSION;
	lp.pref_h = lp0 ? lp0->pref_h : TB_INVALID_DIMENSION;
	self->GetInternal()->SetLayoutParams( lp );
	return 0;
}

int MOAITBWidget::_getMaxSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	state.Push( lp0 ? lp0->max_w : TB_INVALID_DIMENSION );
	state.Push( lp0 ? lp0->max_h : TB_INVALID_DIMENSION );
	return 2;
}

int MOAITBWidget::_setMaxSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int w = state.GetValue < int >( 2, TB_INVALID_DIMENSION );
	int h = state.GetValue < int >( 3, TB_INVALID_DIMENSION );
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	LayoutParams lp;
	lp.min_w  = lp0 ? lp0->min_w : TB_INVALID_DIMENSION;
	lp.min_h  = lp0 ? lp0->min_h : TB_INVALID_DIMENSION;
	lp.max_w  = w;
	lp.max_h  = h;
	lp.pref_w = lp0 ? lp0->pref_w : TB_INVALID_DIMENSION;
	lp.pref_h = lp0 ? lp0->pref_h : TB_INVALID_DIMENSION;
	self->GetInternal()->SetLayoutParams( lp );
	return 0;
}

int MOAITBWidget::_getPreferredSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	state.Push( lp0 ? lp0->pref_w : TB_INVALID_DIMENSION );
	state.Push( lp0 ? lp0->pref_h : TB_INVALID_DIMENSION );
	return 2;
}

int MOAITBWidget::_setPreferredSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int w = state.GetValue < int >( 2, TB_INVALID_DIMENSION );
	int h = state.GetValue < int >( 3, TB_INVALID_DIMENSION );
	const LayoutParams* lp0 = self->GetInternal()->GetLayoutParams();
	LayoutParams lp;
	lp.min_w  = lp0 ? lp0->min_w : TB_INVALID_DIMENSION;
	lp.min_h  = lp0 ? lp0->min_h : TB_INVALID_DIMENSION;
	lp.max_w  = lp0 ? lp0->max_w : TB_INVALID_DIMENSION;
	lp.max_h  = lp0 ? lp0->max_h : TB_INVALID_DIMENSION;
	lp.pref_w = w;
	lp.pref_h = h;
	self->GetInternal()->SetLayoutParams( lp );
	return 0;
}

int MOAITBWidget::_setFixedSize ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int w = state.GetValue < int >( 2, TB_INVALID_DIMENSION );
	int h = state.GetValue < int >( 3, TB_INVALID_DIMENSION );
	LayoutParams lp;
	lp.min_w  = w;
	lp.min_h  = h;
	lp.max_w  = w;
	lp.max_h  = h;
	lp.pref_w = w;
	lp.pref_h = h;
	self->GetInternal()->SetLayoutParams( lp );
	self->GetInternal()->SetSize( w, h );
	return 0;
}


int MOAITBWidget::_invalidate ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )	
	self->GetInternal()->Invalidate();
	return 0;
}

int MOAITBWidget::_invalidateStates ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	self->GetInternal()->InvalidateStates();
	return 0;
}

int MOAITBWidget::_invalidateLayout ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	bool recursive = state.GetValue < bool >( 2, true );
	self->GetInternal()->InvalidateLayout( 
		recursive ? TBWidget::INVALIDATE_LAYOUT_RECURSIVE : TBWidget::INVALIDATE_LAYOUT_TARGET_ONLY
	);
	return 0;
}

int MOAITBWidget::_invalidateSkinStates ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	self->GetInternal()->InvalidateSkinStates();
	return 0;
}


int MOAITBWidget::_die ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	self->GetInternal()->Die();
	return 0;
}

int MOAITBWidget::_isDying ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIsDying() );
	return 1;
}

int MOAITBWidget::_getID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32 id = self->GetInternal()->GetID();
	state.Push( id );
	return 1;
}

int MOAITBWidget::_setID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	self->GetInternal()->SetID( id );
	return 0;
}

int MOAITBWidget::_checkID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	bool equal = id == self->GetInternal()->GetID();
	state.Push( equal );
	return 1;
}

int MOAITBWidget::_getGroupID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32 id = self->GetInternal()->GetGroupID();
	state.Push( id );
	return 1;
}

int MOAITBWidget::_setGroupID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	self->GetInternal()->SetGroupID( id );
	return 0;
}

int MOAITBWidget::_checkGroupID ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	bool equal = id == self->GetInternal()->GetGroupID();
	state.Push( equal );
	return 1;
}

int MOAITBWidget::_getWidgetByID ( lua_State *L ) {
 	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
 	TBWidget* widget = self->GetInternal()->GetWidgetByID( id );
 	PushTBWidgetOrNil( state, widget );
 	return 1;
}

int MOAITBWidget::_getState ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	u32  stateID = state.GetValue < u32 >( 2, 0 );
	bool flag = self->GetInternal()->GetState( (WIDGET_STATE)stateID );
	state.Push( flag );
	return 1;
}

int MOAITBWidget::_setState ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNB" )
	u32  stateID = state.GetValue < u32 > ( 2, 0 );
	bool flag    = state.GetValue < bool >( 3, true );
	self->GetInternal()->SetState( (WIDGET_STATE)stateID, flag );
	return 0;
}

int MOAITBWidget::_getStateRaw ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32  stateRaw = self->GetInternal()->GetStateRaw();
	state.Push( stateRaw );
	return 1;
}

int MOAITBWidget::_setStateRaw ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32  stateRaw = state.GetValue < u32 > ( 2, 0 );
	self->GetInternal()->SetStateRaw( (WIDGET_STATE)stateRaw );
	return 0;
}

int MOAITBWidget::_getAutoState ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32  stateRaw = self->GetInternal()->GetAutoState();
	state.Push( stateRaw );
	return 1;
}

int MOAITBWidget::_getOpacity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	float opacity = self->GetInternal()->GetOpacity();
	state.Push( opacity );
	return 1;
}

int MOAITBWidget::_setOpacity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	float opacity = state.GetValue < float >( 2, 1.0 );
	self->GetInternal()->SetOpacity( opacity );
	return 0;
}

int MOAITBWidget::_seekOpacity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "U" )

	float delay		= state.GetValue < float >( 3, 0.0f );
	
	if ( delay > 0.0f ) {

		u32 mode = state.GetValue < u32 >( 6, ZLInterpolate::kSmooth );		
		
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		
		float opacity = self->GetInternal()->GetOpacity();
		action->ParseForSeek ( state, 2, self, 1, mode,
			MOAITBWidgetAttr::Pack ( ATTR_OPACITY ), opacity, 0.0f
		);
		
		action->SetSpan ( delay );
		action->Start ( false );
		action->PushLuaUserdata ( state );

		return 1;
	}

	float opacity = state.GetValue < float >( 2, 1.0f );
	self->GetInternal()->SetOpacity( opacity );

	return 0;
}

int MOAITBWidget::_isVisible ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetVisibilityCombined() );
	return 1;
}

int MOAITBWidget::_isLocalVisible ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	WIDGET_VISIBILITY visiblity = self->GetInternal()->GetVisibility();
	if( visiblity == WIDGET_VISIBILITY_VISIBLE ) {
		state.Push( true );
	} else if( visiblity == WIDGET_VISIBILITY_INVISIBLE ) {
		state.Push( false );
	} else {
		state.Push();
	}
	return 1;
}

int MOAITBWidget::_setVisible ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	bool visible = state.GetValue < bool >( 2, true );
	WIDGET_VISIBILITY visiblity = visible? WIDGET_VISIBILITY_VISIBLE : WIDGET_VISIBILITY_INVISIBLE;
	self->GetInternal()->SetVisibility( visiblity );
	return 1;
}

int MOAITBWidget::_isDisabled ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	bool disabled = self->GetInternal()->GetState( WIDGET_STATE_DISABLED );
	state.Push( disabled );
	return 1;
}

int MOAITBWidget::_setDisabled ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	bool disabled = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetState( WIDGET_STATE_DISABLED, disabled );
	return 0;
}

int MOAITBWidget::_addChild ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UU" )
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	if( widget ) {
		WIDGET_Z z = GetTBWidgetZ( state, 3 );
		WIDGET_INVOKE_INFO invokeInfo = GetTBInvokeInfo( state, 4 );
		self->GetInternal()->AddChild( widget->GetInternal(), z, invokeInfo );
		widget->PushLuaUserdata( state );
		return 1;
	}
	return 0;
}

int MOAITBWidget::_insertChild ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UUU" )
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	MOAITBWidget* target = state.GetLuaObject < MOAITBWidget >( 3, 0 );
	if( widget && target ) {
		WIDGET_Z_REL z = GetTBWidgetZRel( state, 3 );
		WIDGET_INVOKE_INFO invokeInfo = GetTBInvokeInfo( state, 4 );
		self->GetInternal()->AddChildRelative( widget->GetInternal(), z, target->GetInternal(), invokeInfo );
		widget->PushLuaUserdata( state );
		return 1;
	}
	return 0;
}

int MOAITBWidget::_removeChild ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UU" )
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	if( widget ) {
		WIDGET_INVOKE_INFO invokeInfo = GetTBInvokeInfo( state, 3 );
		self->GetInternal()->RemoveChild( widget->GetInternal(), invokeInfo );
	}
	return 0;
}

int MOAITBWidget::_deleteAllChildren ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	self->GetInternal()->DeleteAllChildren();
	return 0;
}

int MOAITBWidget::_setZ ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	WIDGET_Z z = GetTBWidgetZ( state, 2 );
	self->GetInternal()->SetZ( z );
	return 0;
}

int MOAITBWidget::_setZInflate ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	WIDGET_Z z = GetTBWidgetZ( state, 2 );
	self->GetInternal()->SetZInflate( z );
	return 0;
}

int MOAITBWidget::_getZInflate ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	WIDGET_Z z = self->GetInternal()->GetZInflate();
	state.Push( z == WIDGET_Z_BOTTOM );
	return 1;
}

int MOAITBWidget::_getGravity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32 g = (u32)self->GetInternal()->GetGravity();
	state.Push( g );
	return 1;
}

int MOAITBWidget::_setGravity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	WIDGET_GRAVITY g = GetTBWidgetGravity( state, 2 );
	self->GetInternal()->SetGravity( g );
	return 0;
}

int MOAITBWidget::_getSkin ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	// u32 id = self->GetInternal()->GetSkin();
	// state.Push( id );
	//TODO:
	return 0;
}

int MOAITBWidget::_setSkin ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	//TODO:
	MOAITBSkin* skin = state.GetLuaObject< MOAITBSkin >( 2, true );
	if( skin ) {
		self->GetInternal()->SetSkin( skin->GetInternal() );
	}
	return 0;
}


int MOAITBWidget::_getSkinBg ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32 id = self->GetInternal()->GetSkinBg();
	state.Push( id );
	return 1;
}

int MOAITBWidget::_setSkinBg ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	self->GetInternal()->SetSkinBg( id );
	return 0;
}

int MOAITBWidget::_setGroupRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetIsGroupRoot( flag );
	return 0;
}

int MOAITBWidget::_isGroupRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIsGroupRoot() );
	return 1;
}

int MOAITBWidget::_setFocusable ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetIsFocusable( flag );
	return 0;
}

int MOAITBWidget::_isFocusable ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIsFocusable() );
	return 1;
}

int MOAITBWidget::_setClickableByKey ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetClickByKey( flag );
	return 0;
}

int MOAITBWidget::_isClickableByKey ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetClickByKey() );
	return 1;
}

int MOAITBWidget::_setLongClickWanted ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetWantLongClick( flag );
	return 0;
}

int MOAITBWidget::_isLongClickWanted ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetWantLongClick() );
	return 1;
}

int MOAITBWidget::_setInputIgnored ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UB" )
	bool flag = state.GetValue < bool >( 2, true );
	self->GetInternal()->SetIgnoreInput( flag );
	return 0;
}

int MOAITBWidget::_isInputIgnored ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIgnoreInput() );
	return 1;
}

int MOAITBWidget::_isInteractable ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIsInteractable() );
	return 1;
}

int MOAITBWidget::_setFocus ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	WIDGET_INVOKE_INFO invokeInfo = GetTBInvokeInfo( state, 2 );
	self->GetInternal()->SetFocus( WIDGET_FOCUS_REASON_POINTER, invokeInfo );
	return 0;
}

int MOAITBWidget::_isFocused ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	state.Push( self->GetInternal()->GetIsFocused() );
	return 1;
}

int MOAITBWidget::_setFocusRecursive ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	self->GetInternal()->SetFocusRecursive( WIDGET_FOCUS_REASON_POINTER );
	return 0;
}

int MOAITBWidget::_moveFocus ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	bool forward = state.GetValue < bool >( 2, true );
	self->GetInternal()->MoveFocus( forward );
	return 0;
}

int MOAITBWidget::_getWidgetAt ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	bool includeChild = state.GetValue < bool >( 4, true );
	TBWidget* widget = self->GetInternal()->GetWidgetAt( x, y, includeChild );
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getChildFromIndex ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	u32 idx = state.GetValue < u32 >( 2, 0 );
	TBWidget* widget = self->GetInternal()->GetChildFromIndex( idx );
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getIndexFromChild ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UU" )
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	if( widget ) {
		int idx = self->GetInternal()->GetIndexFromChild( widget->GetInternal() );
		state.Push( idx );
		return 1;
	}
	return 0;
}

int MOAITBWidget::_getContentRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetContentRoot();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_addContent ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UU" )
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	if( widget ) {
		TBWidget* root = self->GetInternal()->GetContentRoot();
		WIDGET_Z z = GetTBWidgetZ( state, 3 );
		WIDGET_INVOKE_INFO invokeInfo = GetTBInvokeInfo( state, 4 );
		root->AddChild( widget->GetInternal(), z, invokeInfo );
		widget->PushLuaUserdata( state );
		return 1;
	}
	return 0;
}

int MOAITBWidget::_getTextByID ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	TBID id = GetTBID( state, 2 );
	TBStr s = self->GetInternal()->GetTextByID( id );
	state.Push( s.CStr() );
	return 1;
}

int MOAITBWidget::_getValueByID ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBID id = GetTBID( state, 2 );
	int value = self->GetInternal()->GetValueByID( id );
	state.Push( value );
	return 1;
}

int MOAITBWidget::_getParentRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetParentRoot();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getParentWindow ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetParentWindow();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getParent ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetParent();
	PushTBWidgetOrNil( state, widget );
	return 1;
}


int MOAITBWidget::_scrollTo ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ScrollTo( x, y );
	return 0;
}

int MOAITBWidget::_scrollToSmooth ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ScrollToSmooth( x, y );
	return 0;
}

int MOAITBWidget::_scrollBy ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int dx = state.GetValue < int >( 2, 0 );
	int dy = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ScrollBy( dx, dy );
	return 0;
}

int MOAITBWidget::_scrollBySmooth ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int dx = state.GetValue < int >( 2, 0 );
	int dy = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ScrollBySmooth( dx, dy );
	return 0;
}


int MOAITBWidget::_setAxis ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	u32 axis = state.GetValue < u32 >( 2, 0 );
	self->GetInternal()->SetAxis( (AXIS)axis );
	return 0;
}

int MOAITBWidget::_getAxis ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	u32 axis = (u32)self->GetInternal()->GetAxis();
	state.Push( axis );
	return 1;
}

int MOAITBWidget::_setValue ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int value = state.GetValue < int >( 2, 0 );
	self->GetInternal()->SetValue( value );
	return 0;
}

int MOAITBWidget::_getValue ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	int v = self->GetInternal()->GetValue();
	state.Push( v );
	return 1;
}

int MOAITBWidget::_setValueDouble ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UN" )
	double value = state.GetValue < double >( 2, 0.0 );
	self->GetInternal()->SetValueDouble( value );
	return 1;
}

int MOAITBWidget::_getValueDouble ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	double v = self->GetInternal()->GetValueDouble();
	state.Push( v );
	return 1;
}

int MOAITBWidget::_setText ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "US" )
	cc8* text = state.GetValue < cc8* >( 2, "" );
	self->GetInternal()->SetText( text );
	return 0;
}

int MOAITBWidget::_getText ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBStr s = self->GetInternal()->GetText();
	state.Push( s.CStr() );
	return 1;
}

int MOAITBWidget::_convertToRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ConvertToRoot( x, y );
	state.Push( x );
	state.Push( y );
	return 2;
}

int MOAITBWidget::_convertFromRoot ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "UNN" )
	int x = state.GetValue < int >( 2, 0 );
	int y = state.GetValue < int >( 3, 0 );
	self->GetInternal()->ConvertFromRoot( x, y );
	state.Push( x );
	state.Push( y );
	return 2;
}


int MOAITBWidget::_getFirstChild ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetFirstChild();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getLastChild ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetLastChild();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getNext ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetNext();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getPrev ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetPrev();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getNextDeep ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	MOAITBWidget* boundingAncestor = state.GetLuaObject < MOAITBWidget >( 2, 0 );
	TBWidget* result;
	if( boundingAncestor ) {
		result = self->GetInternal()->GetNextDeep( boundingAncestor->GetInternal() );
	} else {
		result = self->GetInternal()->GetNextDeep();
	}
	PushTBWidgetOrNil( state, result );
	return 1;
}

int MOAITBWidget::_getPrevDeep ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetPrevDeep();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_getLastLeaf ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBWidget* widget = self->GetInternal()->GetLastLeaf();
	PushTBWidgetOrNil( state, widget );
	return 1;
}

int MOAITBWidget::_createPopupWindow ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	TBPopupWindow* window = new TBPopupWindow( self->GetInternal() );
	PushTBWidgetOrNil( state, window );
	return 1;
}


int MOAITBWidget::_createPopupMenu ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBWidget, "U" )
	//TODO
	return 0;
}

//STATIC
int MOAITBWidget::_TBID ( lua_State *L ) {
	MOAILuaState state ( L );
	TBID id = GetTBID( state, 1 );
	state.Push( (u32) id );
	return 1;
}

int MOAITBWidget::_setAutoFocusState ( lua_State *L ) {
	MOAILuaState state ( L );
	bool flag = state.GetValue < bool >( 1, true );
	TBWidget::SetAutoFocusState( flag );
	return 0;
}


int MOAITBWidget::_getHoveredWidget ( lua_State *L ) {
	MOAILuaState state ( L );
	PushTBWidgetOrNil( state, TBWidget::GetHoveredWidget() );
	return 1;
}

int MOAITBWidget::_getFocusedWidget ( lua_State *L ) {
	MOAILuaState state ( L );
	PushTBWidgetOrNil( state, TBWidget::GetFocusedWidget() );
	return 1;
}

int MOAITBWidget::_getCapturedWidget ( lua_State *L ) {
	MOAILuaState state ( L );
	PushTBWidgetOrNil( state, TBWidget::GetCapturedWidget() );
	return 1;
}

int MOAITBWidget::_sendKeyEvent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "UNB" )
	u32  key      = state.GetValue < u32  >( 2, 0 );
	bool down     = state.GetValue < bool >( 3, true );
	u32 modifiers = state.GetValue < u32 >( 4, TB_MODIFIER_NONE );
	self->GetInternal()->InvokeKey( key, TB_KEY_UNDEFINED, (MODIFIER_KEYS)modifiers, down );
	return 0;
}

int MOAITBWidget::_sendSpecialKeyEvent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "UNB" )
	u32  special  = state.GetValue < u32  >( 2, 0 );
	bool down     = state.GetValue < bool >( 3, true );
	u32 modifiers = state.GetValue < u32 >( 4, TB_MODIFIER_NONE );
	self->GetInternal()->InvokeKey( 0, (SPECIAL_KEY)special, (MODIFIER_KEYS)modifiers, down );
	return 0;
}

int MOAITBWidget::_sendMouseMoveEvent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "UNNNN" )
	float x  = state.GetValue < float >( 2, 0.0f );
	float y  = state.GetValue < float >( 3, 0.0f );
	float dx = state.GetValue < float >( 4, 0.0f );
	float dy = state.GetValue < float >( 5, 0.0f );
	u32 modifiers = state.GetValue < u32 >( 6, TB_MODIFIER_NONE );
	self->GetInternal()->InvokePointerMove( x, y, (MODIFIER_KEYS)modifiers, false );
	self->mPointerLoc.Init( x, y );
	return 0;
}

int MOAITBWidget::_sendMouseButtonEvent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "UNB" )
	u32 button    = state.GetValue < u32 >( 2, 0 );
	bool down     = state.GetValue < bool >( 3, false );
	u32 modifiers = state.GetValue < u32 >( 4, TB_MODIFIER_NONE );
	if( down ) {
		self->GetInternal()->InvokePointerDown( self->mPointerLoc.mX, self->mPointerLoc.mY, 1, (MODIFIER_KEYS)modifiers, false );
	} else {
		self->GetInternal()->InvokePointerUp( self->mPointerLoc.mX, self->mPointerLoc.mY, (MODIFIER_KEYS)modifiers, false );
	}
	return 0;
}

int MOAITBWidget::_sendMouseScrollEvent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITBWidget, "UNN" )
	float x  = state.GetValue < float >( 2, 0.0f );
	float y  = state.GetValue < float >( 3, 0.0f );
	float dx = state.GetValue < float >( 4, 0.0f );
	float dy = state.GetValue < float >( 5, 0.0f );
	u32 modifiers = state.GetValue < u32 >( 6, TB_MODIFIER_NONE );
	self->GetInternal()->InvokeWheel( x, y, dx, dy, (MODIFIER_KEYS)modifiers );
	return 0;
}


//----------------------------------------------------------------//
MOAITBWidget::MOAITBWidget () :
	mInternal( NULL ),
	mWidgetListener( NULL ),
	mRef( NULL )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAINode )
	RTTI_END
}

MOAITBWidget::~MOAITBWidget () {
	TBWidget* internal = this->mInternal;
	this->ClearWidgetListener();
}

void MOAITBWidget::OnInternalLost () {
	if( !this->mInternal ) return;
	this->ClearWidgetListener();
	TBWidget* internal = this->mInternal;
	this->mInternal = NULL;
	this->mRef = NULL; //will get delete by TBValue
	if( MOAITBMgr::IsValid() ) {
		MOAITBMgr::Get().LuaRelease( this );
	}
}

void MOAITBWidget::ClearWidgetListener() {
	if( this->mWidgetListener ) {
		if( this->mInternal ) {
			this->mInternal->RemoveListener( this->mWidgetListener );
		}
		delete this->mWidgetListener;
		this->mWidgetListener = NULL;
	}
}

void MOAITBWidget::SetInternal ( TBWidget* tb ) {
	assert( this->mInternal == NULL );
	this->mInternal = tb;
	this->mRef = new MOAITBWidgetRef( this );
	tb->udata.SetObject( this->mRef );
	MOAITBMgr::Get().LuaRetain( this );
}

//----------------------------------------------------------------//
void MOAITBWidget::AddChild ( MOAITBWidget* widget ) {

}

//----------------------------------------------------------------//
void MOAITBWidget::SetParent ( MOAITBWidget* widget ) {
	
}

//----------------------------------------------------------------//
void MOAITBWidget::AffirmListenerTable ( MOAILuaState& state ) {
	MOAINode::AffirmListenerTable( state );
	this->mWidgetListener = new MOAITBWidgetListener( this );
	this->mInternal->AddListener( this->mWidgetListener );
}


//----------------------------------------------------------------//
bool MOAITBWidget::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	if ( MOAITBWidgetAttr::Check ( attrID )) {
		float x, y, w, h, opacity;
		TBRect rect = this->GetInternal()->GetRect();
		switch ( UNPACK_ATTR ( attrID ) ) {
			case ATTR_X_LOC:
				x = attrOp.Apply ( (float)rect.x, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				this->GetInternal()->SetPosition( TBPoint( (int)x, rect.y ) );
				return true;
			case ATTR_Y_LOC:
				y = attrOp.Apply ( -(float)rect.y, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				this->GetInternal()->SetPosition( TBPoint( rect.x, -(int)y ) );
				return true;
			case ATTR_X_SIZE:
				w = attrOp.Apply ( (float)rect.w, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				this->GetInternal()->SetSize( (int)w, rect.h );
				return true;
			case ATTR_Y_SIZE:
				h = attrOp.Apply ( (float)rect.h, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				this->GetInternal()->SetSize( rect.w, (int)h );
				return true;
			case ATTR_OPACITY:
				opacity = attrOp.Apply ( this->GetInternal()->GetOpacity(), op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				this->GetInternal()->SetOpacity( opacity );
				return true;
		}
	}
	return false;
}

//----------------------------------------------------------------//
void MOAITBWidget::RegisterLuaClass ( MOAILuaState& state ) {
	MOAINode::RegisterLuaClass ( state );
	//Attr
	state.SetField ( -1, "ATTR_X_LOC",			MOAITBWidgetAttr::Pack ( ATTR_X_LOC ));
	state.SetField ( -1, "ATTR_Y_LOC",			MOAITBWidgetAttr::Pack ( ATTR_Y_LOC ));
	state.SetField ( -1, "ATTR_X_SIZE",			MOAITBWidgetAttr::Pack ( ATTR_X_SIZE ));
	state.SetField ( -1, "ATTR_Y_SIZE",			MOAITBWidgetAttr::Pack ( ATTR_Y_SIZE ));
	
	//WIDGET_STATE
	state.SetField ( -1, "WIDGET_STATE_NONE",         ( u32 )WIDGET_STATE_NONE        );
	state.SetField ( -1, "WIDGET_STATE_DISABLED",     ( u32 )WIDGET_STATE_DISABLED    );
	state.SetField ( -1, "WIDGET_STATE_FOCUSED",      ( u32 )WIDGET_STATE_FOCUSED     );
	state.SetField ( -1, "WIDGET_STATE_PRESSED",      ( u32 )WIDGET_STATE_PRESSED     );
	state.SetField ( -1, "WIDGET_STATE_SELECTED",     ( u32 )WIDGET_STATE_SELECTED    );
	state.SetField ( -1, "WIDGET_STATE_HOVERED",      ( u32 )WIDGET_STATE_HOVERED     );

	state.SetField ( -1, "WIDGET_STATE_ALL",          ( u32 )WIDGET_STATE_ALL     );

	//WIDGET_FOCUS_REASON
	state.SetField ( -1, "WIDGET_FOCUS_REASON_NAVIGATION",  ( u32 )WIDGET_FOCUS_REASON_NAVIGATION );
	state.SetField ( -1, "WIDGET_FOCUS_REASON_POINTER",     ( u32 )WIDGET_FOCUS_REASON_POINTER    );
	state.SetField ( -1, "WIDGET_FOCUS_REASON_UNKNOWN",     ( u32 )WIDGET_FOCUS_REASON_UNKNOWN    );

	//MODIFIER KEY
	state.SetField ( -1, "MODIFIER_NONE",  (u32)TB_MODIFIER_NONE );
	state.SetField ( -1, "MODIFIER_CTRL",  (u32)TB_CTRL          );
	state.SetField ( -1, "MODIFIER_SHIFT", (u32)TB_SHIFT         );
	state.SetField ( -1, "MODIFIER_ALT",   (u32)TB_ALT           );
	state.SetField ( -1, "MODIFIER_SUPER", (u32)TB_SUPER         );

	//SPEICIAL KEY
	state.SetField ( -1, "KEY_UNDEFINED",  (u32)TB_KEY_UNDEFINED );
	state.SetField ( -1, "KEY_UP",         (u32)TB_KEY_UP        );
	state.SetField ( -1, "KEY_DOWN",       (u32)TB_KEY_DOWN      );
	state.SetField ( -1, "KEY_LEFT",       (u32)TB_KEY_LEFT      );
	state.SetField ( -1, "KEY_RIGHT",      (u32)TB_KEY_RIGHT     );
	state.SetField ( -1, "KEY_PAGE_UP",    (u32)TB_KEY_PAGE_UP   );
	state.SetField ( -1, "KEY_PAGE_DOWN",  (u32)TB_KEY_PAGE_DOWN );
	state.SetField ( -1, "KEY_HOME",       (u32)TB_KEY_HOME      );
	state.SetField ( -1, "KEY_END",        (u32)TB_KEY_END       );
	state.SetField ( -1, "KEY_TAB",        (u32)TB_KEY_TAB       );
	state.SetField ( -1, "KEY_BACKSPACE",  (u32)TB_KEY_BACKSPACE );
	state.SetField ( -1, "KEY_INSERT",     (u32)TB_KEY_INSERT    );
	state.SetField ( -1, "KEY_DELETE",     (u32)TB_KEY_DELETE    );
	state.SetField ( -1, "KEY_ENTER",      (u32)TB_KEY_ENTER     );
	state.SetField ( -1, "KEY_ESC",        (u32)TB_KEY_ESC       );
	state.SetField ( -1, "KEY_F1",         (u32)TB_KEY_F1        );
	state.SetField ( -1, "KEY_F2",         (u32)TB_KEY_F2        );
	state.SetField ( -1, "KEY_F3",         (u32)TB_KEY_F3        );
	state.SetField ( -1, "KEY_F4",         (u32)TB_KEY_F4        );
	state.SetField ( -1, "KEY_F5",         (u32)TB_KEY_F5        );
	state.SetField ( -1, "KEY_F6",         (u32)TB_KEY_F6        );
	state.SetField ( -1, "KEY_F7",         (u32)TB_KEY_F7        );
	state.SetField ( -1, "KEY_F8",         (u32)TB_KEY_F8        );
	state.SetField ( -1, "KEY_F9",         (u32)TB_KEY_F9        );
	state.SetField ( -1, "KEY_F10",        (u32)TB_KEY_F10       );
	state.SetField ( -1, "KEY_F11",        (u32)TB_KEY_F11       );
	state.SetField ( -1, "KEY_F12",        (u32)TB_KEY_F12       );
	//AXIS
	state.SetField ( -1, "AXIS_X",      ( u32 )AXIS_X     );
	state.SetField ( -1, "AXIS_Y",      ( u32 )AXIS_Y     );

	//WIDGET EVENT
	state.SetField ( -1, "EVENT_WIDGET_DYING",       ( u32 )EVENT_WIDGET_DYING        );
	state.SetField ( -1, "EVENT_WIDGET_ADD",         ( u32 )EVENT_WIDGET_ADD          );
	state.SetField ( -1, "EVENT_WIDGET_REMOVE",      ( u32 )EVENT_WIDGET_REMOVE       );
	state.SetField ( -1, "EVENT_WIDGET_FOCUS_CHANGE",( u32 )EVENT_WIDGET_FOCUS_CHANGE );
	state.SetField ( -1, "EVENT_WIDGET_EVENT",       ( u32 )EVENT_WIDGET_EVENT        );

	//TB ALIGN
	state.SetField ( -1, "ALIGN_LEFT",            ( u32 )TB_ALIGN_LEFT             );
	state.SetField ( -1, "ALIGN_TOP",             ( u32 )TB_ALIGN_TOP              );
	state.SetField ( -1, "ALIGN_RIGHT",           ( u32 )TB_ALIGN_RIGHT            );
	state.SetField ( -1, "ALIGN_BOTTOM",          ( u32 )TB_ALIGN_BOTTOM           );

	//WIDGET_GRAVITY
	state.SetField ( -1, "WIDGET_GRAVITY_NONE",       ( u32 ) WIDGET_GRAVITY_NONE       );
	state.SetField ( -1, "WIDGET_GRAVITY_LEFT",       ( u32 ) WIDGET_GRAVITY_LEFT       );
	state.SetField ( -1, "WIDGET_GRAVITY_RIGHT",      ( u32 ) WIDGET_GRAVITY_RIGHT      );
	state.SetField ( -1, "WIDGET_GRAVITY_TOP",        ( u32 ) WIDGET_GRAVITY_TOP        );
	state.SetField ( -1, "WIDGET_GRAVITY_BOTTOM",     ( u32 ) WIDGET_GRAVITY_BOTTOM     );
	state.SetField ( -1, "WIDGET_GRAVITY_LEFT_RIGHT", ( u32 ) WIDGET_GRAVITY_LEFT_RIGHT );
	state.SetField ( -1, "WIDGET_GRAVITY_TOP_BOTTOM", ( u32 ) WIDGET_GRAVITY_TOP_BOTTOM );
	state.SetField ( -1, "WIDGET_GRAVITY_ALL",        ( u32 ) WIDGET_GRAVITY_ALL        );
	state.SetField ( -1, "WIDGET_GRAVITY_DEFAULT",    ( u32 ) WIDGET_GRAVITY_DEFAULT    );

	luaL_Reg regTable [] = {
		{ "new",               _new },
		{ "setAutoFocusState", _setAutoFocusState  },
		{ "getHoveredWidget",  _getHoveredWidget   },
		{ "getFocusedWidget",  _getFocusedWidget   },
		{ "getCapturedWidget", _getCapturedWidget  },
		{ "TBID",              _TBID },
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBWidget::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAINode::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "getTBClassName",        _getTBClassName       },
		{ "isValid",               _isValid              },

		{ "getRect",               _getRect              },
		{ "setRect",               _setRect              },
		{ "getPaddingRect",        _getPaddingRect       },

		{ "getLoc",                _getLoc               },
		{ "setLoc",                _setLoc               },
		{ "seekLoc",               _seekLoc              },
		{ "getSize",               _getSize              },
		{ "setSize",               _setSize              },
		{ "seekSize",              _seekSize             },

		{ "setMinSize",            _setMinSize           },
		{ "getMinSize",            _getMinSize           },
		{ "setMaxSize",            _setMaxSize           },
		{ "getMaxSize",            _getMaxSize           },
		{ "setPreferredSize",      _setPreferredSize     },
		{ "getPreferredSize",      _getPreferredSize     },
		{ "setFixedSize",          _setFixedSize         },

		{ "invalidate",            _invalidate           },
		{ "invalidateStates",      _invalidateStates     },
		{ "invalidateLayout",      _invalidateLayout     },
		{ "invalidateSkinStates",  _invalidateSkinStates },
		
		{ "die",                   _die                  },
		{ "isDying",               _isDying              },
		
		{ "getID",                 _getID                },
		{ "setID",                 _setID                },
		{ "checkID",               _checkID              },
		{ "getGroupID",            _getGroupID           },
		{ "setGroupID",            _setGroupID           },
		{ "checkGroupID",          _checkGroupID         },
		{ "getWidgetByID",         _getWidgetByID        },

		{ "getState",              _getState             },
		{ "setState",              _setState             },
		{ "getStateRaw",           _getStateRaw          },
		{ "setStateRaw",           _setStateRaw          },
		{ "getAutoState",          _getAutoState         },
		
		{ "getOpacity",            _getOpacity           },
		{ "setOpacity",            _setOpacity           },
		{ "seekOpacity",           _seekOpacity          },
		{ "isVisible",             _isVisible            },
		{ "isLocalVisible",        _isLocalVisible       },
		{ "setVisible",            _setVisible           },
		{ "isDisabled",            _isDisabled           },
		{ "setDisabled",           _setDisabled          },
		
		{ "addChild",              _addChild             },
		{ "insertChild",           _insertChild          },
		{ "removeChild",           _removeChild          },
		{ "deleteAllChildren",     _deleteAllChildren    },

		{ "setZ",                  _setZ                 },
		{ "setZInflate",           _setZInflate          },
		{ "getZInflate",           _getZInflate          },
		
		{ "getGravity",            _getGravity           },
		{ "setGravity",            _setGravity           },

		{ "setSkin",               _setSkin              },
		{ "getSkin",               _getSkin              },

		{ "setSkinBg",             _setSkinBg            },
		{ "getSkinBg",             _getSkinBg            },
		// { "getSkinBgElement",      _getSkinBgElement     }, //TODO

		{ "setGroupRoot",          _setGroupRoot         },
		{ "isGroupRoot",           _isGroupRoot          },
		{ "setFocusable",          _setFocusable         },
		{ "isFocusable",           _isFocusable          },
		{ "setClickableByKey",     _setClickableByKey    },
		{ "isClickableByKey",      _isClickableByKey     },
		{ "setLongClickWanted",    _setLongClickWanted   },
		{ "isLongClickWanted",     _isLongClickWanted    },
		{ "setInputIgnored",       _setInputIgnored      },
		{ "isInputIgnored",        _isInputIgnored       },
		{ "isInteractable",        _isInteractable       },

		{ "setFocus",              _setFocus             },
		{ "isFocused",             _isFocused            },
		{ "setFocusRecursive",     _setFocusRecursive    },
		{ "moveFocus",             _moveFocus            },

		{ "getWidgetAt",           _getWidgetAt          },
		{ "getChildFromIndex",     _getChildFromIndex    },
		{ "getIndexFromChild",     _getIndexFromChild    },
		{ "getContentRoot",        _getContentRoot       },
		{ "addContent",            _addContent           },

		{ "getTextByID",           _getTextByID          },
		{ "getValueByID",          _getValueByID         },

		{ "getParentRoot",         _getParentRoot        },
		{ "getParentWindow",       _getParentWindow      },
		{ "getParent",             _getParent            },

		{ "scrollTo",              _scrollTo             },
		{ "scrollToSmooth",        _scrollToSmooth       },
		{ "scrollBy",              _scrollBy             },
		{ "scrollBySmooth",        _scrollBySmooth       },

		{ "setAxis",               _setAxis              },
		{ "getAxis",               _getAxis              },
		{ "setValue",              _setValue             },
		{ "getValue",              _getValue             },
		{ "setValueDouble",        _setValueDouble       },
		{ "getValueDouble",        _getValueDouble       },
		{ "setText",               _setText              },
		{ "getText",               _getText              },

		{ "convertToRoot",         _convertToRoot        },
		{ "convertFromRoot",       _convertFromRoot      },

		{ "getFirstChild",         _getFirstChild        },
		{ "getLastChild",          _getLastChild         },
		{ "getNext",               _getNext              },
		{ "getPrev",               _getPrev              },
		{ "getNextDeep",           _getNextDeep          },
		{ "getPrevDeep",           _getPrevDeep          },
		{ "getLastLeaf",           _getLastLeaf          },

		{ "createPopupWindow",     _createPopupWindow    },
		{ "createPopupMenu",       _createPopupMenu      },

		{ "sendMouseMoveEvent",    _sendMouseMoveEvent   },
		{ "sendMouseButtonEvent",  _sendMouseButtonEvent },
		{ "sendMouseScrollEvent",  _sendMouseScrollEvent },
		{ "sendKeyEvent",          _sendKeyEvent         },
		{ "sendSpecialKeyEvent",   _sendSpecialKeyEvent  },

		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}