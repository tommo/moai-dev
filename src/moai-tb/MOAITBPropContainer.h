#ifndef MOAITBPropContainer_H
#define MOAITBPropContainer_H

#include "MOAITBWidget.h"

class TBPropContainer :
	public TBWidget {

private:
	MOAIGraphicsProp* mProp;

public:
	virtual void OnPaint(const PaintProps &paint_props);

	TBPropContainer();
	~TBPropContainer();

	void	SetProp( MOAIGraphicsProp* prop );
};


class MOAITBPropContainer :
	public MOAITBWidget {

private:		
	static int _setProp    ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBPropContainer )
	MOAI_TB_CREATE_INTERNAL ( TBPropContainer )

public:
	MOAI_TB_GET_INTERNAL    ( TBPropContainer )

  DECL_LUA_FACTORY ( MOAITBPropContainer )
	
	//----------------------------------------------------------------//
						MOAITBPropContainer			();
						~MOAITBPropContainer			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


#endif