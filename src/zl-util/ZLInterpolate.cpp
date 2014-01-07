// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <math.h>
#include <zl-util/ZLTrig.h>
#include <zl-util/ZLInterpolate.h>

#ifndef PI
#define PI 3.1415926545
#endif

//================================================================//
// ZLInterpolate
//================================================================//

inline float _ABS( float a ) {
	if( a >= 0.0f ) return a;
	return -a;
}

//----------------------------------------------------------------//
float ZLInterpolate::Curve ( u32 mode, float t ) {
	float t2;
	switch ( mode ) {
		
		case kEaseIn:
		
			t = t - 1.0f;
			return 1.0f - ( t * t * t * t );
		
		case kEaseOut:
		
			return t * t * t * t;
			
		case kFlat:
		
			return ( t < 1.0f ) ? 0.0f : 1.0f;
		
		case kLinear:
		
			return t;
		
		case kSharpEaseIn:
		
			t = t - 1.0f;
			return 1.0f - ( t * t * t * t * t * t * t * t );
			
		case kSharpEaseOut:
		
			return t * t * t * t * t * t;
		
		case kSharpSmooth:
		
			if ( t < 0.5f ) {
				t = t * 2.0f;
				return ( t * t * t * t * t * t ) * 0.5f;
			}
			t = ( t * 2.0f ) - 2.0f;
			return ( 2.0f - ( t * t * t * t * t * t )) * 0.5f;
		
		case kSmooth:
		
			if ( t < 0.5f ) {
				t = t * 2.0f;
				return ( t * t * t * t ) * 0.5f;
			}
			t = ( t * 2.0f ) - 2.0f;
			return ( 2.0f - ( t * t * t * t )) * 0.5f;
		
		case kSoftEaseIn:
		
			t = t - 1.0f;
			return 1.0f - ( t * t );
			
		case kSoftEaseOut:
		
			return t * t;
		
		case kSoftSmooth:
		
			if ( t < 0.5f ) {
				t = t * 2.0f;
				return ( t * t ) * 0.5f;
			}
			t = ( t * 2.0f ) - 2.0f;
			return ( 2.0f - ( t * t )) * 0.5f;

		case kBackIn:
			return t * t * (2.70158 * t - 1.70158);

		case kBackOut:
			return 1 + (--t) * t * (2.70158 * t + 1.70158);
			
		case kBackSmooth:
			if( t < 0.5 ) {
				return t * t * (7 * t - 2.5) * 2;
			} else {
				return 1 + (--t) * t * 2 * (7 * t + 2.5);
			}

		case kElasticIn:			 
	    return t * t * t * t * sin( t * PI * 4.5 );
			
		case kElasticOut:
			t = t - 1.0f;
			return 1 - t * t * t * t * cos( t * PI * 4.5 );
		
		case kElasticSmooth:			
			if( t < 0.45 ) {
				t2 = t * t;
				return 8 * t2 * t2 * sin( t * PI * 9 );
			} else if( t < 0.55 ) {
				return 0.5 + 0.75 * sin( t * PI * 4 );
			} else {
				t2 = (t - 1) * (t - 1);
				return 1 - 8 * t2 * t2 * sin( t * PI * 9 );
			}

		case kBounceIn:
			return pow( 2, 6 * (t - 1) ) * _ABS( sin( t * PI * 3.5 ) );
			
		case kBounceOut:
			return 1 - pow( 2, -6 * t ) * _ABS( cos( t * PI * 3.5 ) );
		
		case kBounceSmooth:
			if( t < 0.5 ) {
				return 8 * pow( 2, 8 * (t - 1) ) * _ABS( sin( t * PI * 7 ) );
			} else {
				return 1 - 8 * pow( 2, -8 * t ) * _ABS( sin( t * PI * 7 ) );
			}		
			
	}
	return 0.0f;
}

//----------------------------------------------------------------//
float ZLInterpolate::Curve ( u32 mode, float t, float w ) {

	float v0 = Curve ( kLinear, t );
	float v1 = Curve ( mode, t );
	
	return Interpolate ( kLinear, v0, v1, w );
}

//----------------------------------------------------------------//
float ZLInterpolate::Interpolate ( u32 mode, float x0, float x1, float t ) {

	if ( mode == kFlat ) {
		return ( t < 1.0f ) ? x0 : x1;
	}
	float s = Curve ( mode, t );
	return x0 + (( x1 - x0 ) * s );
}


//----------------------------------------------------------------//
float ZLInterpolate::Interpolate ( u32 mode, float x0, float x1, float t, float w ) {
	
	float s = Curve ( mode, t, w );
	return x0 + (( x1 - x0 ) * s );
}
