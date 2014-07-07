// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-util/MOAITaskThread.h>

//----------------------------------------------------------------//
int MOAITaskThread::_stop ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITaskThread, "U" );
	self->mThread.Stop ();
	return 0;
}

//================================================================//
// MOAITaskThread main
//================================================================//

//----------------------------------------------------------------//
void MOAITaskThread::_main ( void* param, MOAIThreadState& threadState ) {

	MOAITaskThread* taskThread = ( MOAITaskThread* )param;
	
	while ( threadState.IsRunning ()) {
		taskThread->Process ();
		MOAIThread::Sleep ();
	}
}

//================================================================//
// MOAITaskThread
//================================================================//

//----------------------------------------------------------------//
MOAITaskThread::MOAITaskThread () {

	RTTI_SINGLE ( MOAITaskQueue )
}

//----------------------------------------------------------------//
MOAITaskThread::~MOAITaskThread () {

	this->Stop ();
}

//----------------------------------------------------------------//
void MOAITaskThread::PushTask ( MOAITask& task ) {

	MOAITaskQueue::PushTask ( task );
	this->mThread.Start ( _main, this, 0 );
}

//----------------------------------------------------------------//
void MOAITaskThread::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITaskQueue::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAITaskThread::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITaskQueue::RegisterLuaFuncs ( state );
	luaL_Reg regTable [] = {
		{ "stop",		_stop },
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITaskThread::Stop () {

	this->mThread.Stop ();
	this->mThread.Join ();
}
