#include "moai-steer/MOAISteerBox2DRayCast.h"
#include "moai-steer/MOAISteerBox2DController.h"
#include "moai-box2d/headers.h"

//----------------------------------------------------------------//
//----------------------------------------------------------------//
class MOAISteerBox2DRayCastCallback :
	public b2RayCastCallback {
public:
	b2Fixture*		m_fixture;
	b2Vec2			m_point;
	b2Vec2			m_normal;

	u32 mCollisionMask;
	bool mIgnoreSensor;

	//----------------------------------------------------------------//
	MOAISteerBox2DRayCastCallback () {
		mIgnoreSensor = true;
		m_fixture = NULL;
		m_point.SetZero();
		m_normal.SetZero();
	}

	//----------------------------------------------------------------//
	float32 ReportFixture ( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction ) {
		if( this->mIgnoreSensor && fixture->IsSensor() ) return -1.0f;

		const b2Filter& filter = fixture->GetFilterData();
		if( ( filter.categoryBits & this->mCollisionMask ) == 0 ) return -1.0f;

		m_fixture = fixture;
		m_point   = point;
		m_normal  = normal;

		return fraction;		
	}
};



//----------------------------------------------------------------//
//RayCast
//----------------------------------------------------------------//
int MOAISteerBox2DRayCast::_setCollisionMask ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DRayCast, "UN" )
	u32 mask = state.GetValue < u32 >( 2, 0 );
	self->SetCollisionMask( mask );
	return 0;
}

int MOAISteerBox2DRayCast::_setIgnoreSensor ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DRayCast, "UB" )
	bool ignore = state.GetValue < bool >( 2, true );
	self->mIgnoreSensor = ignore;
	return 0;
}

int MOAISteerBox2DRayCast::_setWorld ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DRayCast, "UU" )
	MOAIBox2DWorld* world = state.GetLuaObject < MOAIBox2DWorld >( 2, 0 );
	self->SetWorld( world );
	return 0;
}



//----------------------------------------------------------------//
MOAISteerBox2DRayCast::MOAISteerBox2DRayCast() :
	mCollisionMask( 0xffff )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerRayCast )
	RTTI_END
}

MOAISteerBox2DRayCast::~MOAISteerBox2DRayCast() {
	this->mWorld.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBox2DRayCast::FindCollision ( MOAISteerRayCastResult& result, MOAISteerController* client, const MOAISteerRay& ray ) {
	MOAISteerBox2DController* b2Client = client->AsType< MOAISteerBox2DController >();
	if( !b2Client ) return false;
	MOAIBox2DBody* body = b2Client->GetBody();
	if( !body ) return false;
	if( ray.mLength == 0.0f ) return false;
	float unitsToMeters = body->GetUnitsToMeters();
	
	float p1x = ray.mStart.mX * unitsToMeters;
	float p1y = ray.mStart.mY * unitsToMeters;
	float p2x = ray.mEnd.mX   * unitsToMeters;
	float p2y = ray.mEnd.mY   * unitsToMeters;
 
	b2Vec2 p1(p1x,p1y);
	b2Vec2 p2(p2x,p2y);

  MOAIBox2DWorld* world;
  if( this->mWorld ) {
  	world = this->mWorld;
  } else {
	  world = body->GetWorld();
	}
	MOAISteerBox2DRayCastCallback callback;

	callback.mIgnoreSensor = this->mIgnoreSensor;
	callback.mCollisionMask = this->mCollisionMask;
	world->GetWorld()->RayCast( &callback, p1, p2 );
 
	if ( NULL != callback.m_fixture ) {
		b2Vec2 hitpoint = callback.m_point;
		result.mPoint.Init( 
			callback.m_point.x / unitsToMeters,
			callback.m_point.y / unitsToMeters,
			0.0f
		);

		result.mNormal.Init( 
			callback.m_normal.x,
			callback.m_normal.y,
			0.0f
		);

		return true;

	} else {

		return false;

	}
}

//----------------------------------------------------------------//
void MOAISteerBox2DRayCast::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerRayCast::RegisterLuaClass( state );
}

void MOAISteerBox2DRayCast::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerRayCast::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setCollisionMask",    _setCollisionMask },
		{ "setIgnoreSensor",     _setIgnoreSensor  },
		{ "setWorld",            _setWorld         },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
