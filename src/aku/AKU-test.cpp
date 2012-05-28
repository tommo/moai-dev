// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <aku/AKU-test.h>
#include <moaiext-test/MOAITestMgr.h>

#include <moaiext-test/MOAITest_sample.h>

//================================================================//
// AKU-test
//================================================================//

//----------------------------------------------------------------//
void AKUTestInit () {

	MOAITestMgr::Affirm ();
	
	REGISTER_LUA_CLASS ( MOAITestMgr )
	
	REGISTER_MOAI_TEST ( MOAITest_sample )
}

//----------------------------------------------------------------//
void AKUTestRunScript ( const char* filename ) {
	MOAITestMgr::Get ().RunScript ( filename );
}

//----------------------------------------------------------------//
void AKUTestRunTest ( const char* testname ) {
	MOAITestMgr::Get ().RunTest ( testname );
}

//----------------------------------------------------------------//
void AKUTestSetResultsFile ( const char* filename ) {
	MOAITestMgr::Get ().SetResultsFile ( filename );
}

//----------------------------------------------------------------//
void AKUTestSetStaging () {
	MOAITestMgr::Get ().SetStaging ();
}
