#ifndef MOAISTEERBOX2DRAYCAST_H
#define MOAISTEERBOX2DRAYCAST_H

#include "moai-steer/headers.h"

class MOAISteerBox2DRayCast:
	public MOAISteerRayCast
{
private:
	static int _setWorld         ( lua_State* L );
	static int _setCollisionMask ( lua_State* L );

	u32 mCollisionMask;
	MOAILuaSharedPtr < MOAIBox2DWorld > mWorld;

public:

	virtual bool FindCollision ( MOAISteerRayCastResult& result, MOAISteerController* client, const MOAISteerRay& ray );
	
	void SetWorld ( MOAIBox2DWorld* world ) { this->mWorld.Set( *this, world ); };
	GET_SET( u32, CollisionMask, mCollisionMask )

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBox2DRayCast )

	MOAISteerBox2DRayCast();
	~MOAISteerBox2DRayCast();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
