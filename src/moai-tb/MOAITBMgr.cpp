#include "moai-tb/MOAITBMgr.h"
// #include "moai-tb/MOAITBRenderer.h"
#include "moai-sim/pch.h"
#include "moai-sim/MOAITexture.h"
#include "moai-sim/MOAIFont.h"

#include "tb_system.h"
#include "tb_widgets_reader.h"
#include "tb_skin.h"
#include "tb_core.h"
#include "tb_font_renderer.h"
#include "animation/tb_widget_animation.h"

void register_tbbf_font_renderer();

//----------------------------------------------------------------//
int MOAITBMgr::_init ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	if( !tb_core_is_initialized() ) {
		TBWidgetsAnimationManager::Init();
		cc8* lngFile = state.GetValue < cc8* >( 1, "" );
		tb_core_init( mgr.mRenderer, lngFile );
		register_tbbf_font_renderer();

		g_font_manager->AddFontInfo("resources/default_font/segoe_white_with_shadow.tb.txt", "Segoe");
		TBFontDescription fd;
		fd.SetID(TBIDC("Segoe"));
		fd.SetSize( 20 );
		g_font_manager->SetDefaultFontDescription(fd);

		TBFontFace *font = g_font_manager->CreateFontFace(g_font_manager->GetDefaultFontDescription());
		font->RenderGlyphs(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~•·åäöÅÄÖ") ;
	}
	return 0;
}

int MOAITBMgr::_loadSkin( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	cc8* skinFile = state.GetValue < cc8* >( 1, "" );
	cc8* overFile = state.GetValue < cc8* >( 2, 0 );
	g_tb_skin->Load( skinFile, overFile );
	return 0;
}

//----------------------------------------------------------------//
int MOAITBMgr::_setTextureLoader ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	if( state.IsType( 1, LUA_TFUNCTION ) && state.IsType( 2, LUA_TFUNCTION ) ){
		mgr.mOnLoadTexture.SetRef ( state, 1 );
		mgr.mOnUnloadTexture.SetRef ( state, 2 );
	} else {
		mgr.mOnLoadTexture.Clear();
		mgr.mOnUnloadTexture.Clear();
	}
	return 0;
}

//----------------------------------------------------------------//

int MOAITBMgr::_registerFont ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	cc8* faceName = state.GetValue < cc8* >( 1, "" );
	MOAIFont* font = state.GetLuaObject < MOAIFont > ( 2, 0 );
	mgr.RegisterFont( faceName, font );

	return 0;
}


//----------------------------------------------------------------//

int MOAITBMgr::_loadWidgets ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 1, 0 );
	if( widget ) {
		cc8* data = state.GetValue < cc8* >( 2, "" );
		g_widgets_reader->LoadData( widget->GetInternal(), data );
	}
	return 0;
}

//----------------------------------------------------------------//

int MOAITBMgr::_loadWidgetsFromFile ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 1, 0 );
	if( widget ) {
		cc8* fileName = state.GetValue < cc8* >( 2, "" );
		g_widgets_reader->LoadFile( widget->GetInternal(), fileName );
	}
	return 0;
}

//----------------------------------------------------------------//
MOAITBMgr::MOAITBMgr ()
{
	RTTI_SINGLE ( MOAILuaObject )
	this->mRenderer = new TBRendererMOAI();
}

//----------------------------------------------------------------//
MOAITBMgr::~MOAITBMgr ()
{
	FontMapIt fontMapIt = this->mFontMap.begin ();
	for ( ; fontMapIt != this->mFontMap.end (); ++fontMapIt ) {
		MOAIFont* font = fontMapIt->second;
		this->LuaRelease( font );
	}
	if( tb_core_is_initialized() ) { 
		TBWidgetsAnimationManager::Shutdown();
		tb_core_shutdown();
	}
}

//----------------------------------------------------------------//
void MOAITBMgr::RegisterLuaClass(MOAILuaState& state)
{
	luaL_Reg regTable[] = {
		{ "setTextureLoader",    _setTextureLoader },
		{ "registerFont",        _registerFont },
		{ "loadSkin",            _loadSkin },
		{ "init",                _init },

		{ "loadWidgetsFromFile", _loadWidgetsFromFile },
		{ "loadWidgets",         _loadWidgets },

		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

//----------------------------------------------------------------//
void MOAITBMgr::RegisterLuaFuncs(MOAILuaState& state)
{
	UNUSED(state);
}


// void MOAITBMgr::LoadTexture( TB::Texture* texture ) {
// 	//TODO: lua callback support
// 	if( this->mOnLoadTexture ) {
// 		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
// 		if ( this->mOnLoadTexture.PushRef ( state )) {
// 			lua_pushstring( state, texture->name.Get().c_str() );
// 			state.DebugCall ( 1, 1 );
// 			MOAITextureBase* tex = state.GetLuaObject < MOAITextureBase >( -1, 0 );
// 			tex->Bind();
// 			texture->data = tex;
// 			texture->width = tex->GetWidth();
// 			texture->height = tex->GetHeight();
// 		}
// 	} else {
// 		//default loader
// 		zglBegin();
// 		MOAIImageTexture* tex = new MOAIImageTexture();
// 		tex->Load( texture->name.c_str(), MOAIImageTransform::TRUECOLOR | MOAIImageTransform::PREMULTIPLY_ALPHA );
// 		tex->Bind();
// 		texture->data = tex;
// 		texture->width = ((MOAIImage *)tex)->GetWidth();
// 		texture->height = ((MOAIImage *)tex)->GetHeight();
// 		// printf("loading texture %s\n", texture->name.c_str() );
// 		// printf("%d,%d\n", tex->GetWidth(), tex->GetHeight() );
// 		tex->Retain();
// 		zglEnd();
// 	}
// }

// void MOAITBMgr::ReleaseTexture( TB::Texture* texture ) {
// 	//TODO
// 	if( texture->data ) {
// 		MOAITexture* tex = static_cast< MOAITexture* >( texture->data );
// 		tex->Release();
// 	}
// }

void MOAITBMgr::RegisterFont ( STLString faceName, MOAIFont* font ) {
	MOAIFont* oldFont = NULL;
	
	if( this->mFontMap.contains( faceName ) ) {
		oldFont = this->mFontMap[ faceName ];
		this->LuaRelease( oldFont );
	}

	if( font ) {
		this->mFontMap[ faceName ] = font;
		this->LuaRetain( font );
	} else if( oldFont ) {
		this->mFontMap.erase( faceName );
	}

}

MOAIFont* MOAITBMgr::FindFont ( STLString faceName, float size ) {
	UNUSED( size ); //TODO: font size adapting
	if( this->mFontMap.contains( faceName ) ) {
		return this->mFontMap[ faceName ];
	} else {
		return NULL;
	}
}

// MOAIFont* MOAITBMgr::FindFont ( TB::Font* font ) {
// 	return this->FindFont( font->facename.c_str(), font->size );
// }


//----------------------------------------------------------------//
//----------------------------------------------------------------//
void TBSystem::RescheduleTimer(double fire_time)
{
	// MOAITBMgr& mgr = MOAITBMgr::Get();
	// mgr.RescheduleTimer();
}