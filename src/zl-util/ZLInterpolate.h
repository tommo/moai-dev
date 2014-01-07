// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	ZLINTERPOLATE_H
#define	ZLINTERPOLATE_H

//================================================================//
// ZLInterpolate
//================================================================//
namespace ZLInterpolate {
	
	enum {
		kEaseIn,
		kEaseOut,
		kFlat,
		kLinear,
		kSharpEaseIn,
		kSharpEaseOut,
		kSharpSmooth,
		kSmooth,
		kSoftEaseIn,
		kSoftEaseOut,
		kSoftSmooth,
		kBackIn,
		kBackOut,
		kBackSmooth,
		kElasticIn,
		kElasticOut,
		kElasticSmooth,
		kBounceIn,
		kBounceOut,
		kBounceSmooth,
	};
	
	//----------------------------------------------------------------//
	float	Curve			( u32 mode, float t );
	float	Curve			( u32 mode, float t, float w );
	float	Interpolate		( u32 mode, float x0, float x1, float t );
	float	Interpolate		( u32 mode, float x0, float x1, float t, float w );
	
} // namespace ZLDist

#endif
