#include "moai-steer/MOAISteerController.h"


int MOAISteerController::_getRoot ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	self->AffirmRoot()->PushLuaUserdata( state );
	return 1;
}

int MOAISteerController::_getLimiter ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	self->AffirmLimiter()->PushLuaUserdata( state );
	return 1;
}

int MOAISteerController::_setLimiter ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	MOAISteerLimiter* limiter = state.GetLuaObject < MOAISteerLimiter >( 2, 0 );
	if( limiter ){ 
		if( self->mLimiter ) {
			self->LuaRelease( self->mLimiter );
		}
		self->mLimiter = limiter;
		self->LuaRetain( limiter );
	}
	return 0;
}

int MOAISteerController::_pushBehaviour ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "UU" )
	MOAISteerBehaviour* behaviour = state.GetLuaObject < MOAISteerBehaviour >( 2, 0 );
	if( behaviour ) {
		self->PushBehaviour( behaviour, state.GetValue< float >( 3, behaviour->GetWeight() ) );
	}
	return 0;
}

int MOAISteerController::_removeBehaviour ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "UU" )
	MOAISteerBehaviour* behaviour = state.GetLuaObject < MOAISteerBehaviour >( 2, 0 );
	if( behaviour ) {
		self->RemoveBehaviour( behaviour );
	}
	return 0;
}

int MOAISteerController::_clearBehaviours ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	self->ClearBehaviours();
	return 0;
}


int MOAISteerController::_getLoc ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetLoc() );
	return 3;
}

int MOAISteerController::_getRot ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetRot() );
	return 3;
}

int MOAISteerController::_getRadius ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetRadius() );
	return 1;
}

int MOAISteerController::_setRadius ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "UN" )
	self->SetRadius( state.GetValue < float >( 2, 10.0f ) );
	return 0;
}


int MOAISteerController::_getLinearVelocity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetLinearVelocity() );
	return 3;
}

int MOAISteerController::_getAngularVelocity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetAngularVelocity() );
	return 3;
}

int MOAISteerController::_getLinearSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetLinearSpeed() );
	return 1;
}

int MOAISteerController::_getAngularSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetAngularSpeed() );
	return 1;
}

int MOAISteerController::_getLinearAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetLinearAcceleration() );
	return 3;
}


int MOAISteerController::_getAngularAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerController, "U" )
	state.Push( self->GetAngularAcceleration() );
	return 3;
}


//----------------------------------------------------------------//
MOAISteerController::MOAISteerController() :
	mElapsed( 0.0f ),
	mRootBehaviour( 0 ),
	mLimiter( 0 ),
	mRadius( 1.0f )
 {
	RTTI_BEGIN
		RTTI_EXTEND( MOAIAction )
	RTTI_END

}

MOAISteerController::~MOAISteerController() {
	if( this->mRootBehaviour ){
		this->mRootBehaviour->ClearBehaviours();
		this->LuaRelease( this->mRootBehaviour );
		this->mRootBehaviour->mOwner = NULL;
	}
	if( this->mLimiter ){
		this->LuaRelease( this->mLimiter );
	}
}

//----------------------------------------------------------------//
MOAISteerBehaviourRoot* MOAISteerController::AffirmRoot () {
	if( !this->mRootBehaviour ) {
		this->mRootBehaviour = new MOAISteerBehaviourRoot();
		this->mRootBehaviour->mOwner = this;
		this->LuaRetain( this->mRootBehaviour );
	}
	return this->mRootBehaviour;
}

//----------------------------------------------------------------//
MOAISteerLimiter* MOAISteerController::AffirmLimiter () {
	if( !this->mLimiter ) {
		this->mLimiter = new MOAISteerLimiter();
		this->LuaRetain( this->mLimiter );
	}
	return this->mLimiter;
}

//----------------------------------------------------------------//

//----------------------------------------------------------------//
bool MOAISteerController::IsDone() {
	return false;
}

void MOAISteerController::OnUpdate( double step ) {
	this->mElapsed += step;
	if( !this->mRootBehaviour ) return ;

	MOAISteerAcceleration acc;
	acc.Reset();
	this->AffirmLimiter();
	if( this->mRootBehaviour->OnCalculate( acc, this->mElapsed, step ) ) {
		this->ApplySteerAcceleration( acc, this->mElapsed, step );
	}
	this->mAcceleration.Init( acc );
}

void MOAISteerController::PushBehaviour ( MOAISteerBehaviour* behaviour, float weight ) {
	this->PushBehaviour( behaviour );
	if( behaviour ) {
		behaviour->SetWeight( weight );
	}
}

void MOAISteerController::PushBehaviour ( MOAISteerBehaviour* behaviour ) {
	this->AffirmRoot()->PushBehaviour( behaviour );
}

void MOAISteerController::RemoveBehaviour ( MOAISteerBehaviour* behaviour ) {
	this->AffirmRoot()->RemoveBehaviour( behaviour );	
}

void MOAISteerController::ClearBehaviours () {
	this->AffirmRoot()->ClearBehaviours();
}

//----------------------------------------------------------------//
void MOAISteerController::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaClass( state );
}

void MOAISteerController::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaFuncs( state );

	luaL_Reg regTable [] = {
    { "getRoot",                _getRoot                },
    { "getLimiter",             _getLimiter             },
    { "setLimiter",             _setLimiter             },
    { "pushBehaviour",          _pushBehaviour          },
    { "removeBehaviour",        _removeBehaviour        },
    { "clearBehaviours",        _clearBehaviours        },
    { "getRadius",              _getRadius              },
    { "setRadius",              _setRadius              },
		{ "getLoc",                 _getLoc                 },
		{ "getRot",                 _getRot                 },
		{ "getAngularVelocity",     _getAngularVelocity     },
		{ "getLinearVelocity",      _getLinearVelocity      },
		{ "getAngularSpeed",        _getAngularSpeed        },
		{ "getLinearSpeed",         _getLinearSpeed         },
		{ "getAngularAcceleration", _getAngularAcceleration },
		{ "getLinearAcceleration",  _getLinearAcceleration  },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
