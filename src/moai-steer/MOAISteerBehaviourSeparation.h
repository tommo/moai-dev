#ifndef MOAISTEERBEHAVIOURSEPARATION_H
#define MOAISTEERBEHAVIOURSEPARATION_H

#include "moai-steer/MOAISteerProximity.h"
#include "moai-steer/MOAISteerBehaviour.h"

class MOAISteerBehaviourSeparation:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerProximity > mProximity;
	float mDecayCoefficient;

	MOAISteerAcceleration* mCurrentAcceleration;

public:

	void SetProximity( MOAISteerProximity* proximity ) {
		this->mProximity.Set( *this, proximity );
	}

	bool OnReportNeighbor( MOAISteerController* neighbor );

	GET_SET( float, DecayCoefficient, mDecayCoefficient )
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourSeparation )

	MOAISteerBehaviourSeparation();
	~MOAISteerBehaviourSeparation();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
