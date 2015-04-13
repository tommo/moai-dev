#ifndef	MOAITBImageWidget_H
#define	MOAITBImageWidget_H

#include "MOAITBWidget.h"
#include "image/tb_image_widget.h"

//================================================================//
// MOAITBImageWidget
//================================================================//

class MOAITBImageWidget :
	public MOAITBWidget {
private:
	
	static int _setImage          ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBImageWidget )
	MOAI_TB_CREATE_INTERNAL ( TBImageWidget )

public:
	MOAI_TB_GET_INTERNAL    ( TBImageWidget )

  DECL_LUA_FACTORY ( MOAITBImageWidget )
	
	//----------------------------------------------------------------//
						MOAITBImageWidget			();
						~MOAITBImageWidget			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
