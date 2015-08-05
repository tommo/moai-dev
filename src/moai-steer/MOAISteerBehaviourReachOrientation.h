#ifndef MOAISTEERBEHAVIOURREACHORIENTATION_H
#define MOAISTEERBEHAVIOURREACHORIENTATION_H

#include "moai-steer/MOAISteerBehaviour.h"

class MOAISteerBehaviourReachOrientation:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );
	static int _setTargetOrientation ( lua_State* L );

	//----------------------------------------------------------------//
protected:

	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );

	float mTargetOrientation;
	float mAlignTolerance;
	float mTimeToTarget;
	float mDecelerationRadius;

public:

	GET_SET( float, AlignTolerance,      mAlignTolerance     )
	GET_SET( float, DecelerationRadius,  mDecelerationRadius )
	GET_SET( float, TimeToTarget,        mTimeToTarget       )
	GET_SET( float, TargetOrientation,   mTargetOrientation  )
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourReachOrientation )

	MOAISteerBehaviourReachOrientation();
	~MOAISteerBehaviourReachOrientation();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
