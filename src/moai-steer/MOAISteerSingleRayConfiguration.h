#ifndef MOAISTEERRAYSINGLERAYCONFIGURATION_H
#define MOAISTEERRAYSINGLERAYCONFIGURATION_H

#include "moai-steer/MOAISteerRayCast.h"

//----------------------------------------------------------------//
class MOAISteerSingleRayConfiguration :
	public MOAISteerRayConfiguration
{
private:

	static int _setLength( lua_State* L );
	float mLength;
	
public:

	GET_SET( float, Length, mLength )

	bool UpdateRays( MOAISteerController* owner );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerSingleRayConfiguration )

	MOAISteerSingleRayConfiguration();
	~MOAISteerSingleRayConfiguration();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif