// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <math.h>
#include <zl-util/ZLTrig.h>
#include <zl-util/ZLInterpolate.h>

//================================================================//
// ZLInterpolate
//================================================================//

//----------------------------------------------------------------//
float ZLInterpolate::Curve ( u32 mode, float t ) {

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

		case kElastic:
			return -pow( 2.0f, 10.0f*( t-1 ) ) * sin( ((t-1) - 0.3/4.0) * 2 * 3.14159265/4.0 );

		case kBounce:
			if( 1.0-t < 1.0/2.75 ) return 1.0 - pow( 7.5625 * ( 1.0 - t ), 2.0 );
			if( 1.0-t < 2.0/2.75 ) return 1.0 - ( 7.5625 * pow( 1.0 - t - 1.5/2.75, 2.0 ) + 0.75 );
			if( 1.0-t < 2.5/2.75 ) return 1.0 - ( 7.5625 * pow( 1.0 - t - 2.25/2.75, 2.0 ) + 0.9375 );
			return 1.0 - ( 7.5625 * pow( 1.0 - t - 2.625/2.75, 2 ) +0.984375 );
			

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
