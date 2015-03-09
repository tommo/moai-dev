#ifndef MOAISTEERBEHAVIOURPATHFOLLOW_H
#define MOAISTEERBEHAVIOURPATHFOLLOW_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourPathFollow:
	public MOAISteerBehaviour
{
private:
	static int _setup             ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );

	float mPathOffset;
	float mArrivalTolerance;
  float mDecelerationRadius;
	float mTimeToTarget;

	bool  mArriveEnabled;

	MOAILuaSharedPtr < MOAISteerPath > mPath;

public:

	GET_SET( float, PathOffset,          mPathOffset         )
	GET_SET( float, ArrivalTolerance,    mArrivalTolerance   )
	GET_SET( float, DecelerationRadius,  mDecelerationRadius )
	GET_SET( float, TimeToTarget,        mTimeToTarget       )

	void SetPath( MOAISteerPath* path ) {
		this->mPath.Set( *this, path );		
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourPathFollow )

	MOAISteerBehaviourPathFollow();
	~MOAISteerBehaviourPathFollow();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif