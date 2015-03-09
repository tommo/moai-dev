#ifndef MOAISTEERBEHAVIOURGROUP_H
#define MOAISTEERBEHAVIOURGROUP_H

#include "moai-core/headers.h"
#include "MOAISteerBehaviour.h"

class MOAISteerBehaviourGroup:
	public MOAISteerBehaviour
{
private:
	friend class MOAISteerController;

	static int _setEpsilon         ( lua_State* L );
	static int _setGroupType       ( lua_State* L );
	static int _pushBehaviour      ( lua_State* L );
	static int _removeBehaviour    ( lua_State* L );
	static int _clearBehaviours    ( lua_State* L );

	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	bool CalculateBlend      ( MOAISteerAcceleration& acc, double elapsed, double delta );
	bool CalculatePriority   ( MOAISteerAcceleration& acc, double elapsed, double delta );
		
	u32 mGroupType;
	float mEpsilon;

	//----------------------------------------------------------------//
	typedef STLList < MOAISteerBehaviour* >::iterator behaviourIt;
	STLList < MOAISteerBehaviour* > mBehaviourList;
	
public:
	void PushBehaviour ( MOAISteerBehaviour* behaviour );
	void PushBehaviour ( MOAISteerBehaviour* behaviour, float weight );
	void RemoveBehaviour ( MOAISteerBehaviour* behaviour );
	void ClearBehaviours ();

	enum{
		GROUP_TYPE_BLEND,
		GROUP_TYPE_PRIORITY
	};

	GET_SET ( u32, GroupType, mGroupType )
	GET_SET ( float, Epsilon, mEpsilon )

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourGroup )

	MOAISteerBehaviourGroup();
	~MOAISteerBehaviourGroup();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};




//----------------------------------------------------------------//
//ROOT GROUP
//----------------------------------------------------------------//
class MOAISteerBehaviourRoot:
	public MOAISteerBehaviourGroup
{
private:
	friend class MOAISteerController;
	MOAISteerController* mOwner;

public:
	MOAISteerController* GetOwner(){ return this->mOwner; };

	DECL_LUA_FACTORY ( MOAISteerBehaviourRoot )

	MOAISteerBehaviourRoot();
	~MOAISteerBehaviourRoot();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );

};


#endif