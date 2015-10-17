#include "moai-tb/MOAITBMgr.h"
#include "moai-tb/MOAITBFontRenderer.h"
#include "moai-tb/MOAITBNode.h"

#include "moai-sim/pch.h"
#include "moai-sim/MOAITexture.h"
#include "moai-sim/MOAIFont.h"

#include "tb_system.h"
#include "tb_widgets_reader.h"
#include "tb_skin.h"
#include "tb_core.h"
#include "tb_font_renderer.h"
#include "animation/tb_widget_animation.h"


//----------------------------------------------------------------//
int MOAITBMgr::_init ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	if( !tb_core_is_initialized() ) {
		TBWidgetsAnimationManager::Init();
		cc8* lngFile = state.GetValue < cc8* >( 1, "" );
		tb_core_init( mgr.mRenderer, lngFile );
		g_font_manager->AddRenderer( new MOAITBFontRenderer() );
		
	}
	return 0;
}

int MOAITBMgr::_loadSkin( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* skinFile = state.GetValue < cc8* >( 1, "" );
	bool additive = state.GetValue < bool >( 2, false );
	bool reloadBitmap = state.GetValue < bool >( 3, true );
	if ( !additive ) { //destroy old one
		delete g_tb_skin;
		g_tb_skin = new TBSkin();
	}
	state.Push( (bool)g_tb_skin->Load( skinFile, nullptr, reloadBitmap ) );
	return 1;
}

//----------------------------------------------------------------//
int MOAITBMgr::_reloadBitmap( lua_State* L ) {
	MOAILuaState state ( L );
	g_tb_skin->ReloadBitmaps();
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
	cc8* fontName = state.GetValue < cc8* >( 1, "" );
	MOAIFont* font = state.GetLuaObject < MOAIFont > ( 2, 0 );
	mgr.RegisterFont( fontName, font );

	return 0;
}


//----------------------------------------------------------------//
int MOAITBMgr::_getFont ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	cc8* fontName = state.GetValue < cc8* >( 1, "" );
	MOAIFont* font = mgr.GetFont( fontName );
	if( font ) {
		font->PushLuaUserdata( state );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
int MOAITBMgr::_setDefaultFontFace ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	cc8* fontName = state.GetValue < cc8* >( 1, "" );
	float size    = state.GetValue < float >( 2, 0.0f );

	MOAIFont* font = mgr.GetFont( fontName );
	if ( !font ) {
		state.Push( false );
		return 0;
	}
	if( size <= 0.0f ) {
		size = font->GetDefaultSize();
	}
	TBFontDescription fd;
	fd.SetID( TBID(fontName) );
	fd.SetSize( size );
	g_font_manager->SetDefaultFontDescription( fd );

	TBFontFace *fontface = g_font_manager->CreateFontFace(g_font_manager->GetDefaultFontDescription());
	fontface->RenderGlyphs(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~•·åäöÅÄÖ") ;

	state.Push( true );
	return 1;
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
int MOAITBMgr::_loadWidgetsFromNodeTree ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAITBMgr& mgr = MOAITBMgr::Get();
	MOAITBWidget* widget = state.GetLuaObject < MOAITBWidget >( 1, 0 );
	if( widget ) {
		MOAITBNode* node = state.GetLuaObject < MOAITBNode >( 2, true );
		if( node ) {
			g_widgets_reader->LoadNodeTree( widget->GetInternal(), node->GetInternal() );
		}
	}
	return 0;
}

//----------------------------------------------------------------//
int MOAITBMgr::_loadNodeTree ( lua_State* L ) {
	MOAILuaState state ( L );
	cc8* data = state.GetValue < cc8* >( 1, "" );
	MOAITBNode* node = new MOAITBNode();
	node->GetInternal()->ReadData( data );
	node->PushLuaUserdata( state );
	return 1;
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
		{ "getFont",             _registerFont        },
		{ "registerFont",        _registerFont        },
		{ "loadSkin",            _loadSkin            },
		{ "reloadBitmap",        _reloadBitmap        },
		{ "init",                _init                },
		{ "setTextureLoader",    _setTextureLoader    },
		{ "setDefaultFontFace",  _setDefaultFontFace  },

		{ "loadWidgetsFromFile", _loadWidgetsFromFile },
		{ "loadWidgets",         _loadWidgets         },
		{ "loadWidgetsFromNodeTree", _loadWidgetsFromNodeTree },
		{ "loadNodeTree",         _loadNodeTree         },

		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

//----------------------------------------------------------------//
void MOAITBMgr::RegisterLuaFuncs(MOAILuaState& state)
{
	UNUSED(state);
}

void MOAITBMgr::RegisterFont ( STLString faceName, MOAIFont* font ) {
	MOAIFont* oldFont = NULL;
	
	if( this->mFontMap.contains( faceName ) ) { //TODO: remove from tb font registry?
		oldFont = this->mFontMap[ faceName ];
		this->LuaRelease( oldFont );
	}

	if( font ) {
		this->mFontMap[ faceName ] = font;
		this->LuaRetain( font );
	} else if( oldFont ) {
		this->mFontMap.erase( faceName );
	}

	g_font_manager->AddFontInfo( "@MOAI", faceName, font );

}

MOAIFont* MOAITBMgr::GetFont ( STLString faceName ) {
	if( this->mFontMap.contains( faceName ) ) {
		return this->mFontMap[ faceName ];
	} else {
		return NULL;
	}
}


//----------------------------------------------------------------//
//----------------------------------------------------------------//
void TBSystem::RescheduleTimer(double fire_time)
{
	// MOAITBMgr& mgr = MOAITBMgr::Get();
	// mgr.RescheduleTimer();
}



//----------------------------------------------------------------//
MOAITBImageLoader::MOAITBImageLoader():
	mWidth( 0 ),
	mHeight( 0 ),
	mImage( 0 )
{
}

MOAITBImageLoader::~MOAITBImageLoader() {
	if( this->mImage ) {
		delete this->mImage;
	}
}

int MOAITBImageLoader::Width() {
	return this->mWidth;
}

int MOAITBImageLoader::Height() {
	return this->mHeight;
}

bool MOAITBImageLoader::Init( cc8* filename ) {
	MOAIImage* img = new MOAIImage();
	bool succ = img->Load( filename, MOAIImageTransform::TRUECOLOR );

	if( !succ ) {
		delete img;
		this->mImage = NULL;
		return false;

	} else {
		if( img->GetColorFormat() != ZLColor::RGBA_8888 ) {
			MOAIImage* converted = new MOAIImage();
			converted->Convert( *img, ZLColor::RGBA_8888, MOAIImage::TRUECOLOR );
			delete img;
			this->mImage = converted;
		} else {
			this->mImage = img;
		}
		this->mWidth = this->mImage->GetWidth();
		this->mHeight = this->mImage->GetHeight();
		return succ;

	}
}

uint32* MOAITBImageLoader::Data() {
	if( !this->mImage ) return 0;
	return (uint32*)this->mImage->GetBitmap();
}

//----------------------------------------------------------------//
TBImageLoader *TBImageLoader::CreateFromFile(const char *filename)
{
	MOAITBImageLoader* loader = new MOAITBImageLoader();
	if( loader->Init( filename ) ) {
		return loader;
	}
	delete loader;
	return nullptr;
}
