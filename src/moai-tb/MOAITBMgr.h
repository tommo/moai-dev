#ifndef MOAI_TB_MGR_H
#define MOAI_TB_MGR_H

#include <moai-core/headers.h>
#include <moai-sim/headers.h>

#include "moai-tb/TBRendererMOAI.h"
#include "moai-tb/MOAITBWidget.h"
#include "moai-tb/MOAITBFontRenderer.h"

using namespace tb;

class MOAITBMgr :
	public MOAIGlobalClass< MOAITBMgr, MOAILuaObject > {
private:

	static int _init                   ( lua_State* L );
	static int _addSkin                ( lua_State* L );
	static int _loadSkin               ( lua_State* L );
	static int _reloadBitmap           ( lua_State* L );
	static int _setLookupCallback      ( lua_State* L );
	static int _registerFont           ( lua_State* L );
	static int _getFont                ( lua_State* L );

	static int _loadWidgets            ( lua_State* L );
	static int _loadWidgetsFromFile    ( lua_State* L );
	static int _loadWidgetsFromNodeTree( lua_State* L );
	static int _loadNodeTree           ( lua_State* L );

	// static int		_getDefaultFontFace     ( lua_State* L );
	static int _setDefaultFontFace     ( lua_State* L );

	// static int    _addWidgetFactory       ( lua_State* L );
	// static int    _removeWidgetFactory    ( lua_State* L );


	//----------------------------------------------------------------//
	MOAILuaStrongRef mLookupCallback;
	TBRendererMOAI* mRenderer;
	
	typedef STLMap < STLString, MOAIFont* >::iterator FontMapIt;
  STLMap< STLString, MOAIFont* >  mFontMap;


public:

	TBRenderer*     GetRenderer() { return this->mRenderer; };
	TBImageLoader*  CreateImageLoader( cc8* filename );

	void        RegisterFont   ( STLString faceName, MOAIFont* font );
	MOAIFont*   GetFont        ( STLString faceName );

	DECL_LUA_SINGLETON ( MOAITBMgr )

					MOAITBMgr			();
					~MOAITBMgr		();
	void			RegisterLuaClass	(MOAILuaState& state);
	void			RegisterLuaFuncs	(MOAILuaState& state);
};



//----------------------------------------------------------------//
class MOAITBImageLoader:
	public TBImageLoader
{
private:
	u32 mWidth, mHeight;	
	MOAIImage* mImage;

public:
	bool	Init( cc8* filename );

	MOAITBImageLoader();
	~MOAITBImageLoader();

	virtual int Width();
	virtual int Height();
	virtual uint32 *Data();

	/* data */
};
#endif
