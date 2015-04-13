#ifndef MOAITBCANVAS_H
#define MOAITBCANVAS_H

#include <moai-sim/headers.h>
// #include "TBRendererMOAI.h"
#include "tb_widgets.h"

#include "MOAITBWidget.h"

using namespace tb;

class MOAITBCanvas :
	public MOAIGraphicsProp,
	public MOAIAction {
private:
	
	static int    _getRootWidget           ( lua_State* L );
	static int    _setSize                 ( lua_State* L );
	static int    _sendKeyEvent            ( lua_State* L );
	static int    _sendMouseWheelEvent     ( lua_State* L );
	static int    _sendMouseMoveEvent      ( lua_State* L );
	static int    _sendMouseButtonEvent    ( lua_State* L );

	//----------------------------------------------------------------//
	u32						OnGetModelBounds		( ZLBox& bounds );
	void					OnUpdate				( double step );

	TBWidget* mRootWidget;
	float     mWidth;
	float     mHeight;

	ZLVec2D   mPointerLoc;
	
	virtual void BuildLocalToWorldMtx ( ZLAffine3D& localToWorldMtx );

public:
	void			Draw					( int subPrimID, float lod );
	bool			IsDone					();

	void      SetSize  ( float w, float );

	DECL_LUA_FACTORY ( MOAITBCanvas )
	MOAITBCanvas();
	~MOAITBCanvas();

	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	
	/* data */
};

#endif
