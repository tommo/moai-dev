#ifndef MOAISTEERRAYPARALLELSIDERAYCONFIGURATION_H
#define MOAISTEERRAYPARALLELSIDERAYCONFIGURATION_H

#include "moai-steer/MOAISteerRayCast.h"

//----------------------------------------------------------------//
class MOAISteerParallelSideRayConfiguration :
	public MOAISteerRayConfiguration
{
private:

	static int _setLength      ( lua_State* L );
	static int _setSideOffset  ( lua_State* L );

	float mLength;
	float mSideOffset;
	
public:

	GET_SET( float, Length,     mLength     )
	GET_SET( float, SideOffset, mSideOffset )

	bool UpdateRays( MOAISteerController* owner );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerParallelSideRayConfiguration )

	MOAISteerParallelSideRayConfiguration();
	~MOAISteerParallelSideRayConfiguration();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif