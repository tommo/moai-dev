// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIStencilMode.h>

//================================================================//
// MOAIStencilMode
//================================================================//

//----------------------------------------------------------------//
void MOAIStencilMode::SetStencilFunc ( int func, int ref, int mask ) {
	this->mFunc = func;
	this->mFuncRef = ref;
	this->mFuncMask = mask;
}

//----------------------------------------------------------------//
void MOAIStencilMode::SetStencilMask ( int mask ) {
	this->mMask = mask;
}

//----------------------------------------------------------------//
void MOAIStencilMode::SetStencilOp ( int sfail, int dpfail, int dppass ) {
	// ZGL_STENCIL_OP_DECR
	// ZGL_STENCIL_OP_DECR_WRAP
	// ZGL_STENCIL_OP_INCR
	// ZGL_STENCIL_OP_INCR_WRAP
	// ZGL_STENCIL_OP_INVERT
	// ZGL_STENCIL_OP_KEEP
	// ZGL_STENCIL_OP_REPLACE
	// ZGL_STENCIL_OP_ZERO
	this->mSFail = sfail;
	this->mDPFail = dpfail;
	this->mDPPass = dppass;
}

//----------------------------------------------------------------//
MOAIStencilMode::MOAIStencilMode () :
	mFunc ( 0 ),
	mFuncRef ( 0 ),
	mFuncMask ( 0xff ),
	mSFail ( ZGL_STENCIL_OP_KEEP ),
	mDPFail ( ZGL_STENCIL_OP_KEEP ),
	mDPPass ( ZGL_STENCIL_OP_REPLACE ),
	mMask ( 0xff ) {

}

//----------------------------------------------------------------//
MOAIStencilMode::~MOAIStencilMode () {
}
