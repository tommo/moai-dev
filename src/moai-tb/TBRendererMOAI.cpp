#include "TBRendererMOAI.h"

//----------------------------------------------------------------//
//BITMAP TEXTURE
//----------------------------------------------------------------//
bool MOAITBBitmapTexture::OnGPUCreate () {
	return true;
}

bool MOAITBBitmapTexture::Init ( u32 width, u32 height, u32* data ) {
	this->mWidth  = width;
	this->mHeight = height;
	this->mWrap   = true;
	this->SetDebugName( "TBBitmapTexture" );
	if( this->SetData( data ) ) {
		return true;
	}
	return false;
}

bool MOAITBBitmapTexture::SetData ( u32* data ) {
	if ( !MOAIGfxDevice::Get ().GetHasContext ()) return false;
	zglBegin();
	MOAIGfxDevice::Get ().ClearErrors ();

	if ( !this->mGLTexID ) {
		this->mGLTexID = zglCreateTexture ();
		if ( !this->mGLTexID ) return false;
	}

	this->mGLInternalFormat = ZGL_PIXEL_FORMAT_RGBA;
	this->mGLPixelType = ZGL_PIXEL_TYPE_UNSIGNED_BYTE;
	zglBindTexture ( this->mGLTexID );
	zglTexImage2D (
		0,
		this->mGLInternalFormat,
		this->mWidth,  
		this->mHeight,  
		this->mGLInternalFormat,
		this->mGLPixelType,  
		data
	);
	
	this->mTextureSize = this->mWidth * this->mHeight * 4;

	if ( MOAIGfxDevice::Get ().LogErrors ()) {
		this->CleanupOnError ();
		zglEnd();
		return false;
	}
	
	MOAIGfxDevice::Get ().ReportTextureAlloc ( this->mDebugName, this->mTextureSize );
	this->mIsDirty = true;
	this->DoCPUAffirm();
	zglEnd();
	return true;
}

//----------------------------------------------------------------//
//BITMAP
//----------------------------------------------------------------//
bool TBBitmapMOAI::Init ( u32 width, u32 height, u32* data ) {
	MOAITBBitmapTexture* tex = new MOAITBBitmapTexture();
	this->mTexture = tex;
	this->mWidth   = width;
	this->mHeight  = height;
	if( !this->mTexture->Init( width, height, data ) ) {
		return false;
	}
	return true;
}

void TBBitmapMOAI::SetData ( u32* data ) {
	this->mTexture->SetData( data );
}

TBBitmapMOAI::TBBitmapMOAI() {
	this->mTexture = NULL;
}

TBBitmapMOAI::~TBBitmapMOAI() {
	delete this->mTexture;
}

//----------------------------------------------------------------//
//RENDERER
//----------------------------------------------------------------//

TBBitmap *TBRendererMOAI::CreateBitmap(int width, int height, uint32 *data)
{
	TBBitmapMOAI *bitmap = new TBBitmapMOAI();
	bitmap->Init( width, height, data );
	return bitmap;
}

void TBRendererMOAI::BeginPaint(int render_target_w, int render_target_h) {
	TBRendererBatcher::BeginPaint( render_target_w, render_target_h );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetVertexPreset  ( MOAIVertexFormatMgr::XYZWUVC );
	gfxDevice.SetShaderPreset  ( MOAIShaderMgr::DECK2D_SHADER );
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
	gfxDevice.SetUVMtxMode     ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );

	gfxDevice.SetPrimType ( ZGL_PRIM_TRIANGLES );

}


void TBRendererMOAI::EndPaint() {
	TBRendererBatcher::EndPaint();
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.Flush();
}

void TBRendererMOAI::RenderBatch(Batch *batch) {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	
	MOAITBBitmapTexture* texture = 
		batch->bitmap? static_cast<TBBitmapMOAI*>( batch->bitmap )->mTexture : NULL;
	gfxDevice.SetTexture( texture );

	u32 triCount = batch->vertex_count/3;
	for( u32 j = 0; j < triCount; j++ ) {
		gfxDevice.BeginPrim();
		for( u32 i = 0; i < 3; i++ ) {
			Vertex& vert = batch->vertex[ j*3 + i ];
			gfxDevice.WriteVtx ( vert.x, vert.y );
			gfxDevice.WriteUV  ( vert.u, vert.v );
			gfxDevice.Write< u32 >( vert.col );
		}
		gfxDevice.EndPrim();
	}

}

void TBRendererMOAI::SetClipRect(const TBRect &rect) {
	ZLRect scRect;
	scRect.Init( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h  );

	MOAIGfxDevice& gfx = MOAIGfxDevice::Get ();
	ZLMatrix4x4 mtx;
	mtx = gfx.GetVertexTransform( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	mtx.Append( gfx.GetWorldToWndMtx() );
	mtx.Transform( scRect );
	gfx.SetScissorRect( scRect );
}
