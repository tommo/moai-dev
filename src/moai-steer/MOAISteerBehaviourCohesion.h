#ifndef MOAISTEERBEHAVIOURCOHESION_H
#define MOAISTEERBEHAVIOURCOHESION_H

#include "moai-steer/MOAISteerProximity.h"
#include "moai-steer/MOAISteerBehaviour.h"

class MOAISteerBehaviourCohesion:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerProximity > mProximity;
	ZLVec3D mCenterOfMass;

public:

	void SetProximity( MOAISteerProximity* proximity ) {
		this->mProximity.Set( *this, proximity );
	}

	bool OnReportNeighbor( MOAISteerController* neighbor );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourCohesion )

	MOAISteerBehaviourCohesion();
	~MOAISteerBehaviourCohesion();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
