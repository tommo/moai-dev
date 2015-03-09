#ifndef MOAISTEERBOX2DAABBPROXIMITY_H
#define MOAISTEERBOX2DAABBPROXIMITY_H

#include "moai-steer/MOAISteerProximity.h"
#include "moai-steer/MOAISteerController.h"
#include "moai-box2d/headers.h"

class MOAISteerBox2DAABBQuery;

//----------------------------------------------------------------//
class MOAISteerBox2DAABBProximity:
	public MOAISteerProximity
{
private:
	friend class MOAISteerBox2DAABBQuery;

	static int _setWorld          ( lua_State* L );
	static int _setRadius         ( lua_State* L );
	static int _setCollisionMask  ( lua_State* L );

	MOAISteerBox2DAABBQuery* mQueryCallback;

protected:

	MOAILuaSharedPtr < MOAIBox2DWorld > mWorld;

	MOAISteerController* mCurrentController;
	MOAISteerBehaviour* mCurrentClient;
	u32    mCollisionMask;
	b2AABB mAABB;
	float  mRadius;

	
	bool ReportNeighbor( MOAISteerController* neighbor );
	virtual bool AcceptNeighbor( MOAISteerController* neighbor );
	//----------------------------------------------------------------//	

public:


	void SetWorld ( MOAIBox2DWorld* world ) { this->mWorld.Set( *this, world ); };
	GET_SET( u32,   CollisionMask, mCollisionMask )
	GET_SET( float, Radius,        mRadius        )

	virtual u32 FindNeighbors ( MOAISteerBehaviour* behaviour );
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBox2DAABBProximity )

	MOAISteerBox2DAABBProximity();
	~MOAISteerBox2DAABBProximity();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};




#endif