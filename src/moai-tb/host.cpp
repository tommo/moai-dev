#include <moai-tb/host.h>
#include <moai-tb/headers.h>

//================================================================//
// aku-turbobadger
//================================================================//

#define REGISTER_MOAI_TB_CLASS( clazz ) REGISTER_LUA_CLASS ( MOAITB##clazz )

//----------------------------------------------------------------//
void AKUTurboBadgerAppFinalize () {
}

//----------------------------------------------------------------//
void AKUTurboBadgerAppInitialize () {
}

//----------------------------------------------------------------//
void AKUTurboBadgerContextInitialize () {

	REGISTER_LUA_CLASS ( MOAITBCanvas )
	REGISTER_LUA_CLASS ( MOAITBMgr )
	REGISTER_LUA_CLASS ( MOAITBNode )
	REGISTER_LUA_CLASS ( MOAITBSkin )

	REGISTER_MOAI_TB_CLASS ( Widget )
	REGISTER_MOAI_TB_CLASS ( WidgetEvent )

	REGISTER_MOAI_TB_CLASS ( Button )
	REGISTER_MOAI_TB_CLASS ( TextField )

	REGISTER_MOAI_TB_CLASS ( ClickLabel )
	REGISTER_MOAI_TB_CLASS ( SkinImage )
	REGISTER_MOAI_TB_CLASS ( Separator )
	REGISTER_MOAI_TB_CLASS ( Mover )
	REGISTER_MOAI_TB_CLASS ( Resizer )
	REGISTER_MOAI_TB_CLASS ( Dimmer )
	REGISTER_MOAI_TB_CLASS ( Container )
	REGISTER_MOAI_TB_CLASS ( Slider )
	REGISTER_MOAI_TB_CLASS ( InlineSelect )

	REGISTER_MOAI_TB_CLASS ( RadioCheckBox )
	REGISTER_MOAI_TB_CLASS ( CheckBox )
	REGISTER_MOAI_TB_CLASS ( RadioButton )

	REGISTER_MOAI_TB_CLASS ( Layout )
	REGISTER_MOAI_TB_CLASS ( TabLayout )

	REGISTER_MOAI_TB_CLASS ( ScrollBar )
	REGISTER_MOAI_TB_CLASS ( ScrollContainer )
	REGISTER_MOAI_TB_CLASS ( TabContainer )
	REGISTER_MOAI_TB_CLASS ( ToggleContainer )
	REGISTER_MOAI_TB_CLASS ( Section )
	REGISTER_MOAI_TB_CLASS ( SectionHeader )
	
	REGISTER_MOAI_TB_CLASS ( EditField )
	
	REGISTER_MOAI_TB_CLASS ( Window )
	REGISTER_MOAI_TB_CLASS ( PopupWindow )
	REGISTER_MOAI_TB_CLASS ( ImageWidget )
	REGISTER_MOAI_TB_CLASS ( PropContainer )

	MOAITBMgr::Affirm();
}

