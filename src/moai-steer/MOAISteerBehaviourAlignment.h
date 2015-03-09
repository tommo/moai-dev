#ifndef MOAISTEERBEHAVIOURALIGNMENT_H
#define MOAISTEERBEHAVIOURALIGNMENT_H

#include "moai-steer/MOAISteerProximity.h"
#include "moai-steer/MOAISteerBehaviour.h"

class MOAISteerBehaviourAlignment:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerProximity > mProximity;
	MOAISteerAcceleration* mCurrentAcceleration;

public:

	void SetProximity( MOAISteerProximity* proximity ) {
		this->mProximity.Set( *this, proximity );
	}

	bool OnReportNeighbor( MOAISteerController* neighbor );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourAlignment )

	MOAISteerBehaviourAlignment();
	~MOAISteerBehaviourAlignment();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
