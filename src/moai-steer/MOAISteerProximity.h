#ifndef MOAISTEERPROXIMITY_H
#define MOAISTEERPROXIMITY_H

#include "moai-sim/headers.h"

class MOAISteerBehaviour;

class MOAISteerProximity:
	public MOAINode
{
private:

public:

	virtual u32 FindNeighbors( MOAISteerBehaviour* behaviour ) { return 0; };
	
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerProximity )

	MOAISteerProximity();
	~MOAISteerProximity();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif