#include "moai-steer/MOAISteerBehaviour.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviour::_getOwner ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "U" )
	MOAISteerController* owner = self->GetOwner();
	if( owner ) {
		owner->PushLuaUserdata( state );
		return 1;
	} else {
		state.Push();
		return 1;
	}	
}

int MOAISteerBehaviour::_getParent ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "U" )
	if( self->mParent ) {
		self->mParent->PushLuaUserdata( state );
		return 1;
	} else {
		state.Push();
		return 1;
	}
}

int MOAISteerBehaviour::_getWeight ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "U" )
	state.Push( self->GetWeight() );
	return 1;
}


int MOAISteerBehaviour::_setWeight ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "UN" )
	self->SetWeight( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

int MOAISteerBehaviour::_isEnabled ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "UB" )
	state.Push( self->IsEnabled() );
	return 1;
}

int MOAISteerBehaviour::_setEnabled ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "UB" )
	self->SetEnabled( state.GetValue < bool >( 2, 1.0f ) );
	return 0;
}

int MOAISteerBehaviour::_getLimiter ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "U" )
	MOAISteerLimiter* limiter = self->mLimiter;
	if( limiter ) {
		limiter->PushLuaUserdata( state );
		return 1;
	} else {
		state.Push();
		return 1;
	}	
}

int MOAISteerBehaviour::_setLimiter ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviour, "UU" )
	MOAISteerLimiter* limiter = state.GetLuaObject < MOAISteerLimiter >( 2, 0 );
	self->SetLimiter( limiter );
	return 0;
}


MOAISteerBehaviour::MOAISteerBehaviour() :
	mParent  ( 0 ),
	mEnabled ( true ),
	mWeight  ( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAINode )
	RTTI_END
}

MOAISteerBehaviour::~MOAISteerBehaviour() {
	this->mLimiter.Set( *this, 0 );
}
//----------------------------------------------------------------//
MOAISteerLimiter* MOAISteerBehaviour::GetActualLimiter() {
	if( this->mLimiter ) return this->mLimiter;
	return this->GetOwner()->AffirmLimiter();
}

//----------------------------------------------------------------//
void MOAISteerBehaviour::SetLimiter( MOAISteerLimiter* limiter ) {
	this->mLimiter.Set( *this, limiter );
}

//----------------------------------------------------------------//
void MOAISteerBehaviour::RegisterLuaClass ( MOAILuaState& state ) {
	MOAINode::RegisterLuaClass( state );	
}

void MOAISteerBehaviour::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAINode::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "getOwner",      _getOwner   },
		{ "getParent",     _getParent  },
		{ "setWeight",     _setWeight  },
		{ "isEnabled",     _isEnabled  },
		{ "setEnabled",    _setEnabled },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
