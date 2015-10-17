#include "MOAITBFontRenderer.h"
#include "TBRendererMOAI.h"
//----------------------------------------------------------------//

MOAITBFontFace::MOAITBFontFace ( TBFontGlyphCache *glyph_cache, TBFontRenderer *renderer, const TBFontDescription &font_desc ) 
:TBFontFace( glyph_cache, renderer, font_desc)
{
	MOAITBFontRenderer* moaiFontRenderer = static_cast< MOAITBFontRenderer* >( renderer );
	this->mFont = moaiFontRenderer->mFont;
	this->mSize = moaiFontRenderer->mSize;
	this->mGlyphSet = this->mFont->GetGlyphSet( this->mSize );	
}


MOAITBFontFace::~MOAITBFontFace() {
}

void MOAITBFontFace::DrawGlyph( int x, int y, const TBColor& color, TBFontGlyph *glyph ) {
	this->mFont->AffirmGlyph( this->mSize, glyph->cp );
	this->mFont->ProcessGlyphs(); //TODO: move it into some pre draw batch
	MOAIGlyph* moaiGlyph = this->mGlyphSet->GetGlyph( glyph->cp );
	if ( moaiGlyph ) {
		(( TBRendererMOAI* )g_renderer)->RenderMOAIGlyph( 
			x + glyph->metrics.x, y + glyph->metrics.y + this->GetAscent(), 
			color, this->mFont, moaiGlyph );
		//TODO: kerning...
	}
}

void MOAITBFontFace::DrawString(int x, int y, const TBColor &color, const char *str, int len) {
	//glyph of MOAIFont might come from different texture page
	(( TBRendererMOAI* )g_renderer)->BeginRenderString(); 
	TBFontFace::DrawString( x, y, color, str, len );
	(( TBRendererMOAI* )g_renderer)->EndRenderString(); 
}

// int MOAITBFontFace::GetStringWidth( const char *str, int len ) {
// 	int width = 0;
// 	int i = 0;
// 	while ( str[i] && i < len )
// 	{
// 		UCS4 cp = utf8::decode_next( str, &i, len );
// 		if (cp == 0xFFFF)
// 			continue;
// 		if ( TBFontGlyph *glyph = this->GetGlyph( cp, false ) ) {
// 			width += glyph->metrics.advance;
// 			//TODO: kerning here
// 		}
// 	}
// 	return width;
// }


//----------------------------------------------------------------//
//Renderer
//----------------------------------------------------------------//
MOAITBFontRenderer::MOAITBFontRenderer():
	mFont( 0 ),
	mSize( 0.0f )
{

}

MOAITBFontRenderer::MOAITBFontRenderer( MOAIFont* font, float size ) {
	this->mFont = font;
	this->mSize = size;
	if( this->mFont ) {
		this->mFont->Retain();
		this->mFont->AffirmGlyphSet( size );
		this->mFont->AffirmGlyph( size, 32 ); //trigger font reading, so we can get font metrics
		this->mFont->ProcessGlyphs();
	}
}

MOAITBFontRenderer::~MOAITBFontRenderer()
{
	if( this->mFont )
		this->mFont->Release();
}

TBFontMetrics MOAITBFontRenderer::GetMetrics()
{
	TBFontMetrics metrics;
	MOAIGlyphSet* glyphSet = this->mFont->GetGlyphSet( this->mSize );
	metrics.ascent  = glyphSet->GetAscent();
	metrics.height  = glyphSet->GetHeight();
	metrics.descent = 0; //FIXME: unkown metric...
	return metrics;
}

bool MOAITBFontRenderer::RenderGlyph(TBFontGlyphData *data, UCS4 cp)
{	
	//Glyph rendering is handled by MOAIFont, nothing to do here
	data->w = 0;
	data->h = 0;
	data->stride = 0;
	data->data8 = 0;
	return true;
}

void MOAITBFontRenderer::GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp)
{
	MOAIGlyphSet* glyphSet = this->mFont->GetGlyphSet( this->mSize );
	this->mFont->AffirmGlyph( this->mSize, cp );
	this->mFont->ProcessGlyphs();
	MOAIGlyph* glyph = glyphSet->GetGlyph( cp );

	metrics->advance = (int) ( glyph->GetAdvanceX() );
	metrics->x = 0;
	metrics->y = 0;
}


TBFontFace *MOAITBFontRenderer::Create( TBFontManager *fontMgr, const char *filename, const TBFontDescription &fontDesc )
{
	// printf("create %s\n", filename );
	if( strcmp( filename, "@MOAI" ) != 0 ) return NULL;

	TBFontInfo* info = fontMgr->GetFontInfo( fontDesc.GetID() );

	MOAIFont* font = static_cast< MOAIFont* >( info->GetUserdata() );
	if( !font ) return NULL;

	MOAITBFontRenderer* renderer = new MOAITBFontRenderer( font, fontDesc.GetSize() );
	MOAITBFontFace* face = new MOAITBFontFace( fontMgr->GetGlyphCache(), renderer, fontDesc );
	return face;
}

