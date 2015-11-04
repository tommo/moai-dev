 #ifndef MOAICOLORRAMP_H
#define MOAICOLORRAMP_H

#include "moai-sim/MOAIAnimCurveColor.h"
#include "moai-sim/MOAIEaseDriver.h"
#include "moai-sim/MOAIColor.h"
#include "moai-sim/MOAIImage.h"

//================================================================//
// MOAIColorRamp
//================================================================//

// TODO: doxygen
class MOAIColorRamp :
	public virtual MOAIColor{
private:
		//----------------------------------------------------------------//
		static int _reserveColorStops ( lua_State* L );
		static int _setColorStop      ( lua_State* L );
		static int _getColorAtPos     ( lua_State* L );
		static int _getCursor         ( lua_State* L );
		static int _setCursor         ( lua_State* L );
		static int _seekCursor        ( lua_State* L );
		static int _createImage       ( lua_State* L );

		MOAIAnimCurveColor mColorCurve;
		bool  mDirty;
		float mCursor;

public:
	
	DECL_LUA_FACTORY ( MOAIColorRamp )
	DECL_ATTR_HELPER ( MOAIColorRamp )

	enum {
		ATTR_CURSOR,
		TOTAL_ATTR
	};

	GET( float, Cursor, mCursor );

	void       ReserveColorStops ( u32 count );
	void       SetColorStop      ( u32 idx, float pos, float r, float g, float b, float a );
	void       SetCursor         ( float cursor );
	ZLColorVec CaculateColor     ( float pos );

	MOAIImage* CreateImage       ( u32 width, u32 height );

	void       OnDepNodeUpdate ();
	bool       ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op );

	//----------------------------------------------------------------//
					MOAIColorRamp			();
					~MOAIColorRamp			();
	void    RegisterLuaClass ( MOAILuaState& state );
	void    RegisterLuaFuncs ( MOAILuaState& state );
};

#endif
