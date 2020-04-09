#include "MyPlugin8.h"

#if (defined(VDJ_WIN))
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif
#endif

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
    // ADD YOUR CODE HERE WHEN THE PLUGIN IS CALLED

#if (defined(VDJ_WIN))

    D3DDevice = NULL;
    D3DTexture = NULL;
    D3DSurface = NULL;

#elif (defined(VDJ_MAC))

    GLTexture = 0;

#endif

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetPluginInfo(TVdjPluginInfo8 *infos)
{
    infos->PluginName  = "MyPlugin8";
    infos->Author      = "Atomix Productions";
    infos->Description = "My first VirtualDJ 8 plugin";
    infos->Version     = "1.0";
    infos->Flags       = VDJFLAG_VIDEOTRANSITION_CONTINOUS;
    infos->Bitmap = NULL;

    return S_OK;
}
//---------------------------------------------------------------------------
ULONG VDJ_API CMyPlugin8::Release()
{
    // ADD YOUR CODE HERE WHEN THE PLUGIN IS RELEASED

    delete this;
    return 0;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API  CMyPlugin8::OnDeviceInit()
{
    // ADD YOUR CODE HERE

#if (defined(VDJ_WIN))

    HRESULT hr;

    hr = GetDevice(VdjVideoEngineDirectX9, (void**) &D3DDevice);
    if(hr!=S_OK || D3DDevice == NULL) return S_FALSE;

#endif

    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API  CMyPlugin8::OnDeviceClose()
{
    // ADD YOUR CODE HERE

    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnDraw(float crossfader)
{
    // ADD YOUR CODE HERE
    HRESULT hr;

    int main=(crossfader<=0.5f)?1:2;
    float factor = 1.0f - crossfader/0.5f;
    int alpha;
    TVertex  *vertices;
    DWORD AlphaColor;

#if (defined(VDJ_WIN))

    hr = GetTexture(VdjVideoEngineDirectX9, main, (void **) &D3DTexture);
    hr = D3DTexture->GetSurfaceLevel(0, &D3DSurface);

    SAFE_RELEASE(D3DTexture);
    SAFE_RELEASE(D3DSurface);

#elif (defined(VDJ_MAC))

    hr = GetTexture(VdjVideoEngineOpenGL, GLTexture, (void **) &vertices);

#endif

    if (crossfader<=0.5f) alpha=(int)(factor* 255);
    else alpha=(int)((1.0f- factor)*255);

    vertices = GetVertices(main);

    AlphaColor =  D3DCOLOR_RGBA(255,255,255, alpha);  // see MyPlugin8.h for the declaration on Mac

    vertices[0].color = AlphaColor;
    vertices[1].color = AlphaColor;
    vertices[2].color = AlphaColor;
    vertices[3].color = AlphaColor;

#if (defined(VDJ_WIN))

    // D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

#elif (defined(VDJ_MAC))

    // glColorD3D(AlphaColor);   // see MyPlugin8.h for the declaration

#endif

    hr = DrawDeck(main, vertices);

    return S_OK;
}
