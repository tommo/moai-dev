#ifndef MOAI_TB_MGR_H
#define MOAI_TB_MGR_H

#define MACOSX

#include <moai-core/headers.h>
#include <moai-sim/headers.h>

#include "moai-tb/TBRendererMOAI.h"
#include "moai-tb/MOAITBWidget.h"

using namespace tb;

class MOAITBMgr :
	public MOAIGlobalClass< MOAITBMgr, MOAILuaObject > {
private:

	static int		_init                   ( lua_State* L );
	static int		_loadSkin               ( lua_State* L );
	static int		_setTextureLoader       ( lua_State* L );
	static int		_registerFont           ( lua_State* L );

	static int    _loadWidgets            ( lua_State* L );
	static int    _loadWidgetsFromFile    ( lua_State* L );

	// static int    _addWidgetFactory       ( lua_State* L );
	// static int    _removeWidgetFactory    ( lua_State* L );


	//----------------------------------------------------------------//
	MOAILuaStrongRef mOnLoadTexture;
	MOAILuaStrongRef mOnUnloadTexture;

	MOAILuaStrongRef mOnLoadFont;
	MOAILuaStrongRef mOnUnloadFont;

	TBRendererMOAI* mRenderer;
	
	typedef STLMap < STLString, MOAIFont* >::iterator FontMapIt;
  STLMap< STLString, MOAIFont* >  mFontMap;


public:

	TBRenderer*     GetRenderer() { return this->mRenderer; };

	// void LoadTexture         ( TB::Texture* texture );
	// void ReleaseTexture      ( TB::Texture* texture );

	void RegisterFont        ( STLString faceName, MOAIFont* font );
	MOAIFont* FindFont       ( STLString faceName, float size = 10.0f );
	// MOAIFont* FindFont       ( TB::Font* font );

	DECL_LUA_SINGLETON ( MOAITBMgr )

					MOAITBMgr			();
					~MOAITBMgr		();
	void			RegisterLuaClass	(MOAILuaState& state);
	void			RegisterLuaFuncs	(MOAILuaState& state);
};

#endif
