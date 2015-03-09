#ifndef MOAISTEERBEHAVIOURWANDER_H
#define MOAISTEERBEHAVIOURWANDER_H

#include "moai-steer/MOAISteerBehaviourReachOrientation.h"

class MOAISteerBehaviourWander:
	public MOAISteerBehaviourReachOrientation
{
private:
	static int _setup                ( lua_State* L );
	static int _setupFace            ( lua_State* L );
	static int _setWanderOrientation ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	float mWanderOrientation;

protected:
	float mWanderOffset;
	float mWanderRadius;
	float mWanderRate;
	bool  mFaceEnabled;

public:

	GET_SET( float, WanderOffset,      mWanderOffset      )
	GET_SET( float, WanderRadius,      mWanderRadius      )
	GET_SET( float, WanderRate,        mWanderRate        )
	GET_SET( float, WanderOrientation, mWanderOrientation )
	GET_SET( bool,  FaceEnabled,       mFaceEnabled       )

	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourWander )

	MOAISteerBehaviourWander();
	~MOAISteerBehaviourWander();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
