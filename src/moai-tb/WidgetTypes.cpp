#include "WidgetTypes.h"

#define TRY_TB_TO_MOAI( tbType, moaiType, widgetTb ) \
	if( TBSafeCast< TB##tbType >( widgetTb ) ) { \
		MOAITBWidget* widgetMoai = new MOAITB##moaiType();\
		widgetMoai->SetInternal( widgetTb );\
		return widgetMoai;\
	}

MOAITBWidget* MOAITBWidget::_TB2MOAI ( TBWidget* widget ) {
	if( !widget ) return NULL;
	MOAITBWidgetRef* ref = static_cast< MOAITBWidgetRef* >( widget->udata.GetObject() );
	if( ref ) {
		return ref->mOwner;
	}
	TRY_TB_TO_MOAI( Button,           Button,           widget )
	TRY_TB_TO_MOAI( TextField,        TextField,        widget )
	TRY_TB_TO_MOAI( TabLayout,        TabLayout,        widget )
	TRY_TB_TO_MOAI( Layout,           Layout,           widget )
	TRY_TB_TO_MOAI( ScrollBar,        ScrollBar,        widget )
	TRY_TB_TO_MOAI( Slider,           Slider,           widget )
	TRY_TB_TO_MOAI( InlineSelect,     InlineSelect,     widget )
	TRY_TB_TO_MOAI( ClickLabel,       ClickLabel,       widget )
	TRY_TB_TO_MOAI( Container,        Container,        widget )
	TRY_TB_TO_MOAI( ScrollContainer,  ScrollContainer,  widget )
	TRY_TB_TO_MOAI( TabContainer,     TabContainer,     widget )
	TRY_TB_TO_MOAI( ToggleContainer,  ToggleContainer,  widget )
	TRY_TB_TO_MOAI( Section,          Section,          widget )
	TRY_TB_TO_MOAI( SectionHeader,    SectionHeader,    widget )
	TRY_TB_TO_MOAI( CheckBox,         CheckBox,         widget )
	TRY_TB_TO_MOAI( RadioButton,      RadioButton,      widget )
	TRY_TB_TO_MOAI( RadioCheckBox,    RadioCheckBox,    widget )

	TRY_TB_TO_MOAI( PopupWindow,      PopupWindow,      widget )
	TRY_TB_TO_MOAI( Window,           Window,           widget )
	TRY_TB_TO_MOAI( ImageWidget,      ImageWidget,      widget )

	//fallback
	TRY_TB_TO_MOAI( Widget,      Widget,      widget )
	return NULL;
}

bool MOAITBWidget::PushTBWidget( MOAILuaState& state, TBWidget* widget ) {
	MOAITBWidget* converted = _TB2MOAI( widget );
	if( converted ) {
		converted->PushLuaUserdata( state );
		return true;
	}
	return false;
}

bool MOAITBWidget::PushTBWidgetOrNil( MOAILuaState& state, TBWidget* widget ) {
	if( PushTBWidget( state, widget ) ) return true;
	state.Push();
	return false;
}
