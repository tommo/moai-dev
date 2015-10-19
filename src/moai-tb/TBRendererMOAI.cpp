#include "TBRendererMOAI.h"


//----------------------------------------------------------------//
//BITMAP
//----------------------------------------------------------------//
bool TBBitmapMOAI::Init ( u32 width, u32 height, u32* data ) {
	MOAIImageTexture* tex = new MOAIImageTexture();
	tex->Init( data, width, height, ZLColor::RGBA_8888 );
	tex->SetWrap( true );
	this->mTexture = tex;
	this->mWidth   = width;
	this->mHeight  = height;
	return tex->IsOK();
}

void TBBitmapMOAI::SetData ( u32* data ) {
	this->mTexture->Init( data, this->mWidth, this->mHeight, ZLColor::RGBA_8888 );
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
	this->mRenderTargetWidth  = render_target_w;
	this->mRenderTargetHeight = render_target_h;
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
	
	MOAIImageTexture* texture = 
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

void TBRendererMOAI::RenderMOAIProp( MOAIGraphicsProp* prop ) {
	this->EndPaint();
	prop->Render();
	MOAITBCanvas* currentCanvas = this->mCanvasStack.Top();
	currentCanvas->RestoreRender ();	
	this->BeginPaint( this->mRenderTargetWidth, this->mRenderTargetHeight );
}

void TBRendererMOAI::BeginRenderString() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	this->FlushAllInternal();
	gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );
	// gfxDevice.SetShaderPreset ( MOAIShaderMgr::FONT_SHADER );
}

void TBRendererMOAI::EndRenderString() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );
}

void TBRendererMOAI::RenderMOAIGlyph( int x, int y, const TBColor& color, MOAIFont* font, MOAIGlyph *glyph ) {
	ZLRect padding;
	padding.Init( 0.0f, 0.0f, 0.0f, 0.0f );
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	// Draw the current moaiGlyph
	MOAITextureBase* glyphTexture = font->GetGlyphTexture ( *glyph );
	if ( glyphTexture ) {
		gfxDevice.SetPenColor ( ZLColor::PackRGBA( color.r, color.g, color.b, color.a ) );
		glyph->Draw( *glyphTexture, 
			(float)x+m_translation_x, (float)y+m_translation_y, 
			1.0f, 1.0f, padding );
	}

}


void TBRendererMOAI::PushCanvas( MOAITBCanvas* canvas ) {
	this->mCanvasStack.Push( canvas );
}

void TBRendererMOAI::PopCanvas( MOAITBCanvas* canvas ) {
	MOAITBCanvas* canvas0 = this->mCanvasStack.Pop();
	assert( canvas == canvas0 );
}

