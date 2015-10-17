#ifndef MOAITBImageLoader_H
#define MOAITBImageLoader_H

#include <moai-sim/headers.h>

#include "moai-tb/MOAITBMgr.h"
#include "moai-tb/TBRendererMOAI.h"

#include "tb_font_renderer.h"
#include "tb_renderer.h"
#include "tb_system.h"

using namespace tb;


// //directly use glyph cache from MOAIFont
// class MOAITBFontGlyphCache : public TBFontGlyphCache
// {
// private:
// 	MOAIGlyphSet* mGlyphSet;

// public:
// 	MOAITBFontGlyphCache();
// 	~MOAITBFontGlyphCache();

// 	virtual TBBitmapFragment *CreateFragment(TBFontGlyph *glyph, int w, int h, int stride, uint32 *data);

// 	/* data */
// };


//----------------------------------------------------------------//
class MOAITBFontFace :
	public TBFontFace
{
private:
	MOAIFont*     mFont;
	MOAIGlyphSet* mGlyphSet;
	float         mSize;

protected:
	virtual void DrawGlyph( int x, int y, const TBColor& color, TBFontGlyph* glyph );

public:
	// int GetStringWidth( const char *str, int len );
	virtual void DrawString( int x, int y, const TBColor &color, const char *str, int len = TB_ALL_TO_TERMINATION );

	MOAITBFontFace( TBFontGlyphCache *glyph_cache, TBFontRenderer *renderer, const TBFontDescription &font_desc );
	~MOAITBFontFace();


};

//----------------------------------------------------------------//
//Actual code is inside MOAITBFontFace

class MOAITBFontRenderer : public TBFontRenderer
{
private:
	MOAIFont* mFont;
	float     mSize;

public:
	friend class MOAITBFontFace;

	MOAITBFontRenderer();
	MOAITBFontRenderer( MOAIFont* font, float size );
	~MOAITBFontRenderer();

	virtual TBFontFace *Create(TBFontManager *font_manager, const char *filename,
								const TBFontDescription &font_desc);

	virtual TBFontMetrics GetMetrics();
	virtual bool RenderGlyph(TBFontGlyphData *dst_bitmap, UCS4 cp);
	virtual void GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp);

};

#endif
