#ifndef MOAITBRENDERER_H
#define MOAITBRENDERER_H

#include "moai-sim/headers.h"

#include "tb_renderer.h"
#include "renderers/tb_renderer_batcher.h"


using namespace tb;

class MOAITBBitmapTexture:
	public MOAITextureBase
{
public:
	bool OnGPUCreate ();
	bool Init    ( u32 width, u32 height, u32* data );
	bool SetData ( u32* data );
};


//----------------------------------------------------------------//
class TBBitmapMOAI:
	public TBBitmap
{
private:
	friend class TBRendererMOAI;
	MOAITBBitmapTexture* mTexture;
	int mWidth;
	int mHeight;
public:
	/** Note: Implementations for batched renderers should call TBRenderer::FlushBitmap
		to make sure any active batch is being flushed before the bitmap is deleted. */
	TBBitmapMOAI();
	~TBBitmapMOAI();
	
	virtual int Width() { return this->mWidth; };
	virtual int Height() { return this->mHeight; };
	virtual void SetData(uint32 *data);

	bool Init    ( u32 width, u32 height, u32* data );

};


//----------------------------------------------------------------//
class TBRendererMOAI:
	public TBRendererBatcher
{
public:
	
	// == TBRenderer ====================================================================

	virtual void BeginPaint(int render_target_w, int render_target_h);
	virtual void EndPaint();

	virtual TBBitmap *CreateBitmap(int width, int height, uint32 *data);

	// == TBRendererBatcher ===============================================================

	virtual void RenderBatch(Batch *batch);
	virtual void SetClipRect(const TBRect &rect);

};
#endif