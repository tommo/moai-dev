#include "moai-steer/MOAISteerBehaviourGroup.h"

int MOAISteerBehaviourGroup::_setGroupType ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourGroup, "UN" )
	u32 gtype = state.GetValue < u32 >( 2, GROUP_TYPE_BLEND );
	self->SetGroupType( gtype );
	return 0;
}

int MOAISteerBehaviourGroup::_setEpsilon ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourGroup, "UF" )
	float epsilon = state.GetValue < float >( 2, 0.1f );
	self->SetEpsilon( epsilon );
	return 0;
}

int MOAISteerBehaviourGroup::_pushBehaviour ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourGroup, "UU" )
	MOAISteerBehaviour* behaviour = state.GetLuaObject < MOAISteerBehaviour >( 2, 0 );
	if( behaviour ) {
		self->PushBehaviour( behaviour, state.GetValue< float >( 3, behaviour->GetWeight() ) );
	}
	return 0;
}

int MOAISteerBehaviourGroup::_removeBehaviour ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourGroup, "UU" )
	MOAISteerBehaviour* behaviour = state.GetLuaObject < MOAISteerBehaviour >( 2, 0 );
	if( behaviour ) {
		self->RemoveBehaviour( behaviour );
	}
	return 0;
}

int MOAISteerBehaviourGroup::_clearBehaviours ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourGroup, "U" )
	self->ClearBehaviours();
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourGroup::MOAISteerBehaviourGroup() :
	mEpsilon   ( 0.1f ),
	mGroupType ( GROUP_TYPE_BLEND )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourGroup::~MOAISteerBehaviourGroup() {

}

//----------------------------------------------------------------//

bool MOAISteerBehaviourGroup::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	switch( this->mGroupType ) {
		case GROUP_TYPE_BLEND: 
		{
			return this->CalculateBlend( acc, elapsed, delta );
		}
		case GROUP_TYPE_PRIORITY:
		{
			return this->CalculatePriority( acc, elapsed, delta );
		}
		default:
			return false;
	}	
}

bool MOAISteerBehaviourGroup::CalculateBlend ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	float totalWeight = 0.0f;
	MOAISteerAcceleration tmpAcc;

	for( behaviourIt iter = this->mBehaviourList.begin(); iter != this->mBehaviourList.end(); ++iter ) {
		MOAISteerBehaviour* behaviour = ( *iter );
		if( !behaviour->IsEnabled() ) continue;
		tmpAcc.Reset();
		if( behaviour->OnCalculate( tmpAcc, elapsed, delta ) ) {
			float weight = behaviour->GetWeight();
			acc.Add( tmpAcc, weight );
			totalWeight += weight;
		}
	}

	if( totalWeight > 0.0f ) {
		acc.Scale( 1.0f/totalWeight );
		return true;
	}

	return false;
}


bool MOAISteerBehaviourGroup::CalculatePriority ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	for( behaviourIt iter = this->mBehaviourList.begin(); iter != this->mBehaviourList.end(); ++iter ) {
		MOAISteerBehaviour* behaviour = ( *iter );
		if( !behaviour->IsEnabled() ) continue;
		acc.Reset();
		if( behaviour->OnCalculate( acc, elapsed, delta ) ) {
			if( acc.Length() > this->mEpsilon ) return true;
		}
	}
	return false;
}


void MOAISteerBehaviourGroup::PushBehaviour ( MOAISteerBehaviour* behaviour, float weight ) {
	this->PushBehaviour( behaviour );
	if( behaviour ) {
		behaviour->SetWeight( weight );
	}
}

void MOAISteerBehaviourGroup::PushBehaviour ( MOAISteerBehaviour* behaviour ) {
	MOAISteerBehaviour* oldParent = behaviour->GetParent();
	if( oldParent ) {
		//TODO:WARN?
		return;
	}
	this->mBehaviourList.push_back( behaviour );
	this->LuaRetain( behaviour );
	behaviour->mParent = this;
	behaviour->LuaRetain( this );

}

void MOAISteerBehaviourGroup::RemoveBehaviour ( MOAISteerBehaviour* behaviour ) {
	for( behaviourIt iter = this->mBehaviourList.begin(); iter != this->mBehaviourList.end(); ++iter ) {
		if(( *iter ) == behaviour ) {
			this->LuaRelease( behaviour );
			this->mBehaviourList.erase ( iter );
			//todo: remove from proximity database
			behaviour->LuaRelease( this );
			return;
		}
	}
}

void MOAISteerBehaviourGroup::ClearBehaviours () {
	for( behaviourIt iter = this->mBehaviourList.begin(); iter != this->mBehaviourList.end(); ++iter ) {
		MOAISteerBehaviour* behaviour = ( *iter );
		behaviour->LuaRelease( this );
		behaviour->mParent = 0;
		this->LuaRelease( behaviour );
	}
	this->mBehaviourList.clear();
}



//----------------------------------------------------------------//
void MOAISteerBehaviourGroup::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );

	state.SetField ( -1, "GROUP_TYPE_PRIORITY",   ( u32 )GROUP_TYPE_PRIORITY );
	state.SetField ( -1, "GROUP_TYPE_BLEND",      ( u32 )GROUP_TYPE_BLEND    );

}

void MOAISteerBehaviourGroup::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );

	luaL_Reg regTable [] = {
    { "setEpsilon",      _setEpsilon      },
    { "setGroupType",    _setGroupType    },
    { "pushBehaviour",   _pushBehaviour   },
    { "removeBehaviour", _removeBehaviour },
    { "clearBehaviours", _clearBehaviours },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}



//----------------------------------------------------------------//
//ROOT GROUP
//----------------------------------------------------------------//

MOAISteerBehaviourRoot::MOAISteerBehaviourRoot() {
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviourGroup )
	RTTI_END
}

MOAISteerBehaviourRoot::~MOAISteerBehaviourRoot() {
}

void  MOAISteerBehaviourRoot::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviourGroup::RegisterLuaClass( state );
}

void  MOAISteerBehaviourRoot::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviourGroup::RegisterLuaFuncs( state );
}
