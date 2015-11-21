// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAISTENCILMODE_H
#define MOAISTENCILMODE_H

//================================================================//
// MOAIStencilMode
//================================================================//
class MOAIStencilMode {
public:
	
	int				mFunc;
	int				mFuncRef;
	int				mFuncMask;
	int				mMask;
	
	int				mSFail;
	int				mDPFail;
	int				mDPPass;
	

	void SetStencilFunc ( int func, int ref, int mask ) ;
	void SetStencilMask ( int mask ) ;
	void SetStencilOp ( int sfail, int dpfail, int dppass ) ;

	//----------------------------------------------------------------//
					MOAIStencilMode		();
					~MOAIStencilMode		();
	
	//----------------------------------------------------------------//
	inline bool IsSame ( const MOAIStencilMode& stencilMode ) {
		return (
			( this->mFunc == stencilMode.mFunc ) &&
			( this->mFuncRef == stencilMode.mFuncRef ) &&
			( this->mFuncMask == stencilMode.mFuncMask ) &&
			( this->mMask == stencilMode.mMask ) &&
			( this->mSFail == stencilMode.mSFail ) &&
			( this->mDPFail == stencilMode.mDPFail ) &&
			( this->mDPPass == stencilMode.mDPPass )
		);
	}
};

#endif
