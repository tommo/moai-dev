#ifndef MOAISTEERRAYCAST_H
#define MOAISTEERRAYCAST_H

#include "moai-core/headers.h"

class MOAISteerController;

//----------------------------------------------------------------//
class MOAISteerRay {
public:
	ZLVec3D mStart;
	ZLVec3D mEnd;
	float   mLength;
};

//----------------------------------------------------------------//
class MOAISteerRayCastResult {
public:
	ZLVec3D mPoint;
	ZLVec3D mNormal;
	void*   mUserdata;
};

//----------------------------------------------------------------//
class MOAISteerRayConfiguration :
	public MOAILuaObject
{
private:

protected:
	ZLLeanArray < MOAISteerRay > mRays;
	
public:

	virtual bool UpdateRays( MOAISteerController* owner ) { return false; } ;

	ZLLeanArray< MOAISteerRay >& GetRays(){ return this->mRays; };

	DECL_LUA_FACTORY ( MOAISteerRayConfiguration )
	
	MOAISteerRayConfiguration();
	~MOAISteerRayConfiguration();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


//----------------------------------------------------------------//
//MOAISteerRayCast
//----------------------------------------------------------------//
class MOAISteerRayCast:
	public MOAILuaObject
{
private:
	
public:
	virtual bool FindCollision ( MOAISteerRayCastResult& result, MOAISteerController* client, const MOAISteerRay& ray ) { return false; };
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerRayCast )

	MOAISteerRayCast();
	~MOAISteerRayCast();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif