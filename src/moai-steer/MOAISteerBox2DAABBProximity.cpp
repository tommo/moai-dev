#include "moai-steer/MOAISteerBox2DAABBProximity.h"
#include "moai-steer/MOAISteerBox2DController.h"

//----------------------------------------------------------------//
//----------------------------------------------------------------//
class MOAISteerBox2DAABBQuery:
	public b2QueryCallback {
public:
	
	MOAISteerBox2DAABBProximity* mOwner;	
	u32 mCount;
	u32 mMask;
	bool mIgnoreSensor;

	bool ReportFixture ( b2Fixture* fixture ){
		if( fixture->IsSensor() && this->mIgnoreSensor ) return true;
		const b2Filter& filter = fixture->GetFilterData();
		if( ( filter.categoryBits & this->mMask ) != 0 ) { //found collision
			b2Body* body = fixture->GetBody(); 
			MOAISteerBox2DControllerMgr& mgr = MOAISteerBox2DControllerMgr::Get();
			MOAISteerController* controller = mgr.Find( body );
			if ( controller && ( controller != this->mOwner->mCurrentController ) ) {
				if ( this->mOwner->AcceptNeighbor( controller ) ) {
					this->mCount ++;
					if( !this->mOwner->ReportNeighbor( controller ) ) return false;
				}
			}
		}
		return true;
	}
};


//----------------------------------------------------------------//
//
//----------------------------------------------------------------//

int MOAISteerBox2DAABBProximity::_setRadius ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DAABBProximity, "UN" )
	float radius = state.GetValue < float >( 2, 0 );
	self->SetRadius( radius );
	return 0;
}

int MOAISteerBox2DAABBProximity::_setCollisionMask ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DAABBProximity, "UN" )
	u32 mask = state.GetValue < u32 >( 2, 0 );
	self->SetCollisionMask( mask );
	return 0;
}

int MOAISteerBox2DAABBProximity::_setIgnoreSensor ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DAABBProximity, "UB" )
	bool ignore = state.GetValue < bool >( 2, true );
	self->mIgnoreSensor = ignore;
	self->mQueryCallback->mIgnoreSensor = ignore;
	return 0;
}

int MOAISteerBox2DAABBProximity::_setWorld ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DAABBProximity, "UU" )
	MOAIBox2DWorld* world = state.GetLuaObject < MOAIBox2DWorld >( 2, 0 );
	self->SetWorld( world );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBox2DAABBProximity::MOAISteerBox2DAABBProximity() :
	mCurrentClient( 0 ),
	mRadius( 10.0f ),
	mCollisionMask( 0xffff )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerProximity )
	RTTI_END
	this->mQueryCallback = new MOAISteerBox2DAABBQuery();
	this->mQueryCallback->mIgnoreSensor = true;
	this->mQueryCallback->mOwner = this;
}

MOAISteerBox2DAABBProximity::~MOAISteerBox2DAABBProximity() {
	delete this->mQueryCallback;
}

//----------------------------------------------------------------//
u32 MOAISteerBox2DAABBProximity::FindNeighbors ( MOAISteerBehaviour* behaviour ) {
	MOAIBox2DWorld* world;
	world = this->mWorld;
	if ( !world ) {
		MOAISteerBox2DController* b2controller = behaviour->GetOwner()->AsType< MOAISteerBox2DController >();		
		if( !b2controller ) return 0;
		MOAIBox2DBody* body = b2controller->GetBody();
		if( !body ) return 0;
		world = body->GetWorld();
	}
	float unitsToMeters = world->GetUnitsToMeters();
	this->mCurrentClient = behaviour;
	this->mCurrentController = behaviour->GetOwner();
	{
		ZLVec3D loc = this->mCurrentController->GetLoc();
		this->mQueryCallback->mCount = 0;
		this->mQueryCallback->mMask = this->mCollisionMask;
		this->mAABB.lowerBound.x = ( loc.mX - this->mRadius ) * unitsToMeters;
		this->mAABB.lowerBound.y = ( loc.mY - this->mRadius ) * unitsToMeters;
		this->mAABB.upperBound.x = ( loc.mX + this->mRadius ) * unitsToMeters;
		this->mAABB.upperBound.y = ( loc.mY + this->mRadius ) * unitsToMeters;
		world->GetWorld()->QueryAABB( this->mQueryCallback, this->mAABB );
	}
	this->mCurrentClient = NULL;
	this->mCurrentController = NULL;
	return this->mQueryCallback->mCount;
}

bool MOAISteerBox2DAABBProximity::ReportNeighbor ( MOAISteerController* neighbor ) {
	return this->mCurrentClient->OnReportNeighbor( neighbor );
}

bool MOAISteerBox2DAABBProximity::AcceptNeighbor ( MOAISteerController* neighbor ) {
	return true;
}

//----------------------------------------------------------------//
void MOAISteerBox2DAABBProximity::RegisterLuaClass ( MOAILuaState& state ) {
	MOAINode::RegisterLuaClass( state );
}

void MOAISteerBox2DAABBProximity::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAINode::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setWorld",         _setWorld         },
		{ "setRadius",        _setRadius        },
		{ "setCollisionMask", _setCollisionMask },
		{ "setIgnoreSensor",  _setIgnoreSensor  },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

