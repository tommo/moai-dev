#ifndef MOAISTEERBOX2DRADIUSPROXIMITY_H
#define MOAISTEERBOX2DRADIUSPROXIMITY_H

#include "moai-steer/MOAISteerBox2DAABBProximity.h"

//----------------------------------------------------------------//
class MOAISteerBox2DRadiusProximity:
	public MOAISteerBox2DAABBProximity
{
protected:

	virtual bool AcceptNeighbor( MOAISteerController* neighbor );
	//----------------------------------------------------------------//	

public:

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBox2DRadiusProximity )

	MOAISteerBox2DRadiusProximity();
	~MOAISteerBox2DRadiusProximity();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};




#endif