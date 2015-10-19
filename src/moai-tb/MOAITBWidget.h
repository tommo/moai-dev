#ifndef MOAITBWIDGET_H
#define MOAITBWIDGET_H

#include "moai-sim/headers.h"

#include "tb_widgets.h"
#include "tb_widgets_listener.h"
#include "tb_value.h"

using namespace tb;

class MOAITBWidget;
class MOAITBWidgetRef;
class MOAITBWidgetListener;

//----------------------------------------------------------------//
class MOAITBWidgetRef :
	public TBTypedObject
{
private:
	friend class MOAITBWidget;
	friend class MOAITBWidgetListener;
	MOAITBWidget* mOwner;

public:
	TBOBJECT_SUBCLASS(TBWidget, TBTypedObject);
	MOAITBWidgetRef  ( MOAITBWidget* owner );
	~MOAITBWidgetRef ();

};


//----------------------------------------------------------------//
class MOAITBWidgetListener :
	public TBWidgetListener
{
private:
	MOAITBWidget* mOwner;

public:
	MOAITBWidgetListener( MOAITBWidget* owner ) :mOwner( owner ) {};

	MOAITBWidget* GetMOAITBWidget( TBWidget *widget );

	virtual void OnWidgetDelete       ( TBWidget *widget );
	virtual bool OnWidgetDying        ( TBWidget *widget );
	virtual void OnWidgetAdded        ( TBWidget *parent, TBWidget *child );
	virtual void OnWidgetRemove       ( TBWidget *parent, TBWidget *child );
	virtual void OnWidgetFocusChanged ( TBWidget *widget, bool focused );
	virtual bool OnWidgetInvokeEvent  ( TBWidget *widget, const TBWidgetEvent &ev );

};

//----------------------------------------------------------------//
class MOAITBWidgetEvent:
	public MOAILuaObject
{
private:
	static int _getType         ( lua_State* L );
	static int _getWidget       ( lua_State* L );
	static int _getLoc          ( lua_State* L );
	static int _getDelta        ( lua_State* L );
	static int _getCount        ( lua_State* L );
	static int _getKey          ( lua_State* L );
	static int _getSpecialKey   ( lua_State* L );
	static int _getModifiers    ( lua_State* L );
	static int _hasModifiers    ( lua_State* L );
	static int _getRefID        ( lua_State* L );
	static int _isTouch         ( lua_State* L );
	static int _isPointerEvent  ( lua_State* L );
	static int _isKeyEvent      ( lua_State* L );

public:
	const TBWidgetEvent* mEvent;

	DECL_LUA_FACTORY( MOAITBWidgetEvent )

	MOAITBWidgetEvent();
	~MOAITBWidgetEvent();

	void RegisterLuaClass ( MOAILuaState& state );
	void RegisterLuaFuncs ( MOAILuaState& state );
};


//----------------------------------------------------------------//
class MOAITBWidget:
	public MOAINode
{
private:
	friend class MOAITBWidgetRef;
	friend class MOAITBWidgetListener;


	//----------------------------------------------------------------//
	static int _TBID             ( lua_State* L );

	//----------------------------------------------------------------//
	static int _getTBClassName   ( lua_State* L );
	static int _isValid          ( lua_State* L );

	static int _getRect          ( lua_State* L );
	static int _setRect          ( lua_State* L );
	static int _getLoc           ( lua_State* L );
	static int _setLoc           ( lua_State* L );
	static int _seekLoc          ( lua_State* L );
	static int _getSize          ( lua_State* L );
	static int _setSize          ( lua_State* L );
	static int _seekSize         ( lua_State* L );

	static int _setMinSize       ( lua_State* L );
	static int _getMinSize       ( lua_State* L );
	static int _setMaxSize       ( lua_State* L );
	static int _getMaxSize       ( lua_State* L );
	static int _setPreferredSize ( lua_State* L );
	static int _getPreferredSize ( lua_State* L );
	static int _setFixedSize     ( lua_State* L );

	static int _invalidate       ( lua_State* L );
	static int _invalidateStates ( lua_State* L );
	static int _invalidateSkinStates ( lua_State* L );
	static int _invalidateLayout ( lua_State* L );
	static int _die              ( lua_State* L );
	static int _isDying          ( lua_State* L );

	static int _getID            ( lua_State* L );
	static int _setID            ( lua_State* L );
	static int _checkID          ( lua_State* L );

	static int _getGroupID       ( lua_State* L );
	static int _setGroupID       ( lua_State* L );
	static int _checkGroupID     ( lua_State* L );

	static int _getWidgetByID    ( lua_State* L );

	static int _getState         ( lua_State* L );
	static int _setState         ( lua_State* L );
	static int _getStateRaw      ( lua_State* L );
	static int _setStateRaw      ( lua_State* L );
	static int _getAutoState     ( lua_State* L );
	static int _setAutoFocusState( lua_State* L );

	static int _getOpacity       ( lua_State* L );
	static int _setOpacity       ( lua_State* L );
	static int _seekOpacity      ( lua_State* L );
	static int _isVisible        ( lua_State* L );
	static int _isLocalVisible   ( lua_State* L );
	static int _setVisible       ( lua_State* L );
	static int _isDisabled       ( lua_State* L );
	static int _setDisabled      ( lua_State* L );

	static int _addChild         ( lua_State* L );
	static int _insertChild      ( lua_State* L );
	static int _removeChild      ( lua_State* L );
	static int _deleteAllChildren( lua_State* L );

	static int _setZ             ( lua_State* L );
	static int _setZInflate      ( lua_State* L );
	static int _getZInflate      ( lua_State* L );
	static int _getGravity       ( lua_State* L );
	static int _setGravity       ( lua_State* L );

	static int _setSkin          ( lua_State* L );
	static int _getSkin          ( lua_State* L );

	static int _setSkinBg        ( lua_State* L );
	static int _getSkinBg        ( lua_State* L );

	// static int _getSkinBgElement    ( lua_State* L ); //TODO

	static int _setGroupRoot        ( lua_State* L );
	static int _isGroupRoot         ( lua_State* L );
	static int _setFocusable        ( lua_State* L );
	static int _isFocusable         ( lua_State* L );
	static int _setClickableByKey   ( lua_State* L );
	static int _isClickableByKey    ( lua_State* L );
	static int _setLongClickWanted  ( lua_State* L );
	static int _isLongClickWanted   ( lua_State* L );
	static int _setInputIgnored     ( lua_State* L );
	static int _isInputIgnored      ( lua_State* L );
	static int _isInteractable      ( lua_State* L );

	static int _setFocus            ( lua_State* L );
	static int _isFocused           ( lua_State* L );
	static int _setFocusRecursive   ( lua_State* L );
	static int _moveFocus           ( lua_State* L );

	static int _getWidgetAt         ( lua_State* L );
	static int _getChildFromIndex   ( lua_State* L );
	static int _getIndexFromChild   ( lua_State* L );
	static int _getContentRoot      ( lua_State* L );
	static int _addContent          ( lua_State* L );

	static int _getTextByID         ( lua_State* L );
	static int _getValueByID        ( lua_State* L );

	static int _getParentRoot       ( lua_State* L );
	static int _getParentWindow     ( lua_State* L );
	static int _getParent           ( lua_State* L );

	static int _scrollTo            ( lua_State* L );
	static int _scrollToSmooth      ( lua_State* L );
	static int _scrollBy            ( lua_State* L );
	static int _scrollBySmooth      ( lua_State* L );

	static int _setAxis             ( lua_State* L );
	static int _getAxis             ( lua_State* L );
	static int _setValue            ( lua_State* L );
	static int _getValue            ( lua_State* L );
	static int _setValueDouble      ( lua_State* L );
	static int _getValueDouble      ( lua_State* L );
  static int _setText             ( lua_State* L );
	static int _getText             ( lua_State* L );

	static int _convertToRoot       ( lua_State* L );
	static int _convertFromRoot     ( lua_State* L );

	static int _getFirstChild       ( lua_State* L );
	static int _getLastChild        ( lua_State* L );
	static int _getNext             ( lua_State* L );
	static int _getPrev             ( lua_State* L );
	static int _getNextDeep         ( lua_State* L );
	static int _getPrevDeep         ( lua_State* L );
	static int _getLastLeaf         ( lua_State* L );

	static int _createPopupWindow   ( lua_State* L );
	static int _createPopupMenu     ( lua_State* L );

	//----------------------------------------------------------------//
	void OnInternalLost ();
	void ClearWidgetListener  ();
	void SetInternal( TBWidget* tb );

	virtual TBWidget* CreateInternal() {
		return new TBWidget();
	};

	MOAITBWidgetRef* mRef;


protected:
	TBWidget* mInternal;
	TBWidgetListener* mWidgetListener;
	virtual void	AffirmListenerTable		( MOAILuaState& state );

public:
	enum Events{
		EVENT_WIDGET_DELETE = MOAINode::TOTAL_EVENTS,
		EVENT_WIDGET_DYING,
		EVENT_WIDGET_ADD,
		EVENT_WIDGET_REMOVE,
		EVENT_WIDGET_FOCUS_CHANGE,
		EVENT_WIDGET_EVENT,
		TOTAL_EVENTS,
	};

	GET( TBWidget*, Internal, mInternal )

	bool IsValid () { return mInternal != NULL; }

	MOAITBWidget* Init() {
		return this->Init( this->CreateInternal() );
	}
	
	MOAITBWidget* Init( TBWidget* widget ) {
		this->SetInternal( widget );
		return this;
	}
	//----------------------------------------------------------------//
	void    AddChild   ( MOAITBWidget* widget );
	void    SetParent  ( MOAITBWidget* widget );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAITBWidget )
	DECL_ATTR_HELPER ( MOAITBWidget )

	enum {
		ATTR_X_LOC,
		ATTR_Y_LOC,
		
		ATTR_X_SIZE,
		ATTR_Y_SIZE,
		
		ATTR_OPACITY,

		TOTAL_ATTR,
	};

	MOAITBWidget();
	~MOAITBWidget();

	void RegisterLuaClass ( MOAILuaState& state );
	void RegisterLuaFuncs ( MOAILuaState& state );

public://STATIC
	//----------------------------------------------------------------//
	static TBID GetTBID ( MOAILuaState& state, int idx ) {
		if( state.IsType( idx, LUA_TSTRING ) ) {
			cc8* idStr = state.GetValue < cc8* >( idx, "" );
			return TBID( idStr );
		} else {
			u32 id = state.GetValue < u32 >( idx, 0 );
			return TBID( id );
		}
	}

	static WIDGET_INVOKE_INFO GetTBInvokeInfo( MOAILuaState& state, int idx, bool defaultValue = true ) {
		bool shouldInvoke = state.GetValue< bool >( idx, defaultValue );
		WIDGET_INVOKE_INFO invokeInfo = shouldInvoke ? WIDGET_INVOKE_INFO_NORMAL : WIDGET_INVOKE_INFO_NO_CALLBACKS;
		return invokeInfo;
	}

	static WIDGET_Z GetTBWidgetZ( MOAILuaState& state, int idx, bool defaultValue = true ) {
		bool bottom = state.GetValue< bool >( idx, defaultValue );
		WIDGET_Z z = bottom ? WIDGET_Z_BOTTOM : WIDGET_Z_TOP;
		return z;
	}

	static WIDGET_Z_REL GetTBWidgetZRel( MOAILuaState& state, int idx, bool defaultValue = true ) {
		bool after = state.GetValue< bool >( idx, defaultValue );
		WIDGET_Z_REL z = after ? WIDGET_Z_REL_AFTER : WIDGET_Z_REL_BEFORE;
		return z;
	}

	static WIDGET_GRAVITY GetTBWidgetGravity( MOAILuaState& state, int idx, u32 defaultValue = 0 ) {
		u32 value = state.GetValue < u32 >( idx, defaultValue );
		return ( WIDGET_GRAVITY ) value;
	}
	
	//----------------------------------------------------------------//
	static MOAITBWidget* _TB2MOAI ( TBWidget* widget );
	static bool PushTBWidget      ( MOAILuaState& state, TBWidget* widget );
	static bool PushTBWidgetOrNil ( MOAILuaState& state, TBWidget* widget );

	//----------------------------------------------------------------//
	bool			ApplyAttrOp				( u32 attrID, MOAIAttrOp& attrOp, u32 op );

};


#define MOAI_TB_NEW( ThisClass )\
	static int _new ( lua_State* L ) {\
		MOAILuaState state ( L );\
		ThisClass *widget = new ThisClass();\
		widget->Init();\
		widget->PushLuaUserdata( state );\
		return 1;\
	}	

#define MOAI_TB_GET_INTERNAL( TBClazz )\
	inline TBClazz* GetInternal() { return static_cast< TBClazz* >( this->mInternal ); }

#define MOAI_TB_CREATE_INTERNAL( TBClazz )\
	TBWidget* CreateInternal() { return new TBClazz(); }

#endif