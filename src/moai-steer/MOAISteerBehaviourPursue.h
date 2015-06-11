#ifndef MOAISTEERBEHAVIOURPURSUE_H
#define MOAISTEERBEHAVIOURPURSUE_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourPursue:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerController > mTarget;
	MOAILuaSharedPtr < MOAITransformBase > mTransformTarget;

	float mPredictionTime;

public:

	void SetTarget( MOAISteerController* target ) {
		this->mTarget.Set( *this, target );
	}

	void SetTarget( MOAITransformBase* target ) {
		this->mTransformTarget.Set( *this, target );
	}

	GET_SET( float, PredictionTime, mPredictionTime )
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourPursue )

	MOAISteerBehaviourPursue();
	~MOAISteerBehaviourPursue();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
