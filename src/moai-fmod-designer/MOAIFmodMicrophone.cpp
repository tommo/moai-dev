// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-fmod-designer/MOAIFmodMicrophone.h>
#include <fmod.hpp>
#include <moai-fmod-designer/Source/EventManager.h>

#ifdef MOAI_OS_IPHONE
	#include <fmodiphone.h>
#endif

#ifdef MOAI_OS_NACL
#include <NaClFileSystem.h>
#include <moai_nacl.h>
#endif

//================================================================//
// MOAIFmodMicrophone
//================================================================//
//----------------------------------------------------------------//
int MOAIFmodMicrophone::_setVectorUp ( lua_State *L ) {
    MOAI_LUA_SETUP( MOAIFmodMicrophone, "UNNN" )
    float x = state.GetValue<float>( 2, 0.0f );
    float y = state.GetValue<float>( 3, 1.0f );
    float z = state.GetValue<float>( 4, 0.0f );
    self->SetVectorUp( ZLVec3D( x, y, z ) );
    return 0;
}

int MOAIFmodMicrophone::_setVectorForward ( lua_State *L ) {
    MOAI_LUA_SETUP( MOAIFmodMicrophone, "UNNN" )
    float x = state.GetValue<float>( 2, 0.0f );
    float y = state.GetValue<float>( 3, 1.0f );
    float z = state.GetValue<float>( 4, 0.0f );
    self->SetVectorForward( ZLVec3D( x, y, z ) );
    return 0;
}

//----------------------------------------------------------------//
MOAIFmodMicrophone::MOAIFmodMicrophone () :
    mVectorForward( 0.0f, 0.0f, 1.0f ),
    mVectorUp(0.f, 1.f, 0.f)
{
    RTTI_BEGIN
        RTTI_EXTEND ( MOAITransform )        
    RTTI_END
}

//----------------------------------------------------------------//
MOAIFmodMicrophone::~MOAIFmodMicrophone () {
}

//----------------------------------------------------------------//
void MOAIFmodMicrophone::RegisterLuaClass ( MOAILuaState& state ) {

    MOAITransform::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIFmodMicrophone::RegisterLuaFuncs ( MOAILuaState& state ) {

    MOAITransform::RegisterLuaFuncs ( state );

    luaL_Reg regTable [] = {
        { "new",              MOAILogMessages::_alertNewIsUnsupported },
        { "setVectorUp",      _setVectorUp },
        { "setVectorForward", _setVectorForward },
        { NULL, NULL }
    };

    luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
bool MOAIFmodMicrophone::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
    
    bool bReturn = MOAITransform::ApplyAttrOp ( attrID, attrOp, op );    

    if ( MOAIFmodMicrophoneAttr::Check ( attrID ) )
    {   
        ZLVec3D vPos = GetLocalToWorldMtx().GetTranslation();
        SetMicLoc ( vPos );
    }

    return bReturn;
}

//----------------------------------------------------------------//
void MOAIFmodMicrophone::OnDepNodeUpdate () {

    MOAITransform::OnDepNodeUpdate ();
    ZLAffine3D mtx = GetLocalToWorldMtx();
    ZLVec3D vPos = mtx.GetTranslation();
    ZLVec3D vUp       = mVectorUp;
    ZLVec3D vForward  = mVectorForward;
    mtx.TransformVec( vUp );
    mtx.TransformVec( vForward );
    vUp.NormSafe();
    vForward.NormSafe();
    FMODDesigner::tEventManager.SetMicrophoneTransform ( vPos, ZLVec3D( 0.0f, 0.0f, 0.0f ), vForward, vUp );
}

//----------------------------------------------------------------//

void MOAIFmodMicrophone::SetMicLoc ( ZLVec3D& vPos )
{    
    FMODDesigner::tEventManager.SetMicrophoneTransform( vPos );
}