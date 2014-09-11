// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIImage.h>

SUPPRESS_EMPTY_FILE_WARNING
#if MOAI_WITH_LIBWEBP
#include <webp/decode.h>

#define WEBP_BUFFER_SIZE 1024

//================================================================//
// MOAIImage-webp
//================================================================//

//----------------------------------------------------------------//
void MOAIImage::LoadWebP ( ZLStream& stream, u32 transform ) {

	u8 dataBuf[ WEBP_BUFFER_SIZE ];
	int dataSize;

	VP8StatusCode status;
	WebPDecoderConfig cfg;
	WebPInitDecoderConfig( &cfg );

	//get header
	dataSize = stream.PeekBytes( dataBuf, WEBP_BUFFER_SIZE );
	if( WebPGetFeatures( dataBuf, dataSize, &cfg.input ) != VP8_STATUS_OK ) {
		return;
	}	

	u32 width, height;
	width  = cfg.input.width;
	height = cfg.input.height;
	

	// set the dimensions, and padding (if any )
	bool isPadded = false;
	if ( transform & MOAIImageTransform::POW_TWO ) {
		this->mWidth = this->GetMinPowerOfTwo ( width );
		this->mHeight = this->GetMinPowerOfTwo ( height );
		isPadded = true;
	}
	else {
		this->mWidth = width;
		this->mHeight = height;
	}

	ZLColor::Format imgColorFormat;
	bool quantize = transform & MOAIImageTransform::QUANTIZE;
	bool prealpha = transform & MOAIImageTransform::PREMULTIPLY_ALPHA;
	
	if ( cfg.input.has_alpha ) {
		imgColorFormat = quantize ? ZLColor::RGBA_4444 : ZLColor::RGBA_8888;		
	} else {
		imgColorFormat = quantize ? ZLColor::RGB_565 : ZLColor::RGBA_8888;
	}

	WEBP_CSP_MODE colorSpace;

	switch ( imgColorFormat ) {
		case ZLColor::RGBA_8888:
			colorSpace = prealpha ? MODE_rgbA : MODE_RGBA;			
			break;
		case ZLColor::RGBA_4444:
			colorSpace = prealpha ? MODE_rgbA_4444 : MODE_RGBA_4444;
			break;
		case ZLColor::RGB_888:
			colorSpace = MODE_RGB_565;
			break;
		case ZLColor::RGB_565:
			colorSpace = MODE_RGB_565;
			break;
	}


	// override the image settings
	this->mPixelFormat = ZLPixel::TRUECOLOR;
	this->mColorFormat = imgColorFormat;
	
	this->Alloc ();
	if ( isPadded ) {
		this->ClearBitmap ();
	}
	
	cfg.output.colorspace = colorSpace;
	cfg.output.is_external_memory = 1;
	cfg.output.u.RGBA.rgba   = ( u8* )mData;
	cfg.output.u.RGBA.size   = GetBitmapSize();
	cfg.output.u.RGBA.stride = GetRowSize();
	cfg.output.width  = mWidth;
	cfg.output.height = mHeight;

	WebPIDecoder* idec = WebPIDecode( NULL, 0, &cfg );
	if( idec == NULL ) return;

	bool succ = false;
	while( !stream.IsAtEnd() ) {
		//use data from previous header parsing
		dataSize = stream.ReadBytes( dataBuf, WEBP_BUFFER_SIZE );
		status = WebPIAppend( idec, dataBuf, dataSize );
		if( status == VP8_STATUS_OK ) {
			succ = true;
			break;
		}
		if( status != VP8_STATUS_SUSPENDED ) {
			//error
			succ = false;
			break;
		}
	}

	WebPIDelete( idec );

}

#endif