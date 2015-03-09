#ifndef MOAISTEERBEHAVIOURFACE_H
#define MOAISTEERBEHAVIOURFACE_H

#include "moai-steer/MOAISteerBehaviourReachOrientation.h"

class MOAISteerBehaviourFace:
	public MOAISteerBehaviourReachOrientation
{
private:
	static int _setup ( lua_State* L );

protected:
	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAITransformBase > mTarget;

public:

	void SetTarget( MOAITransformBase* target ) {
		this->mTarget.Set( *this, target );
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourFace )

	MOAISteerBehaviourFace();
	~MOAISteerBehaviourFace();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
