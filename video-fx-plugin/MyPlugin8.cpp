#include "MyPlugin8.h"

#if (defined(VDJ_WIN))
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=NULL; } }
#endif
#endif
//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
    // ADD YOUR CODE HERE WHEN THE PLUGIN IS CALLED
    VideoWidth = 0;
    VideoHeight = 0;
    
#if (defined(VDJ_WIN))
    
    D3DDevice = NULL;
    D3DTexture = NULL;
    D3DSurface = NULL;
    
#elif (defined(VDJ_MAC))
    
    glContext= 0;
    GLTexture = 0;
    
#endif
    
    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetPluginInfo(TVdjPluginInfo8 *infos)
{
    infos->PluginName = "MyPlugin8";
    infos->Author = "Atomix Productions";
    infos->Description = "My first VirtualDJ 8 plugin";
    infos->Version = "1.0";
    infos->Flags = 0x00; // VDJFLAG_PROCESSLAST if you want to ensure that all other effects are processed first
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
HRESULT VDJ_API CMyPlugin8::OnDeviceInit()
{
    // ADD YOUR CODE HERE
#if (defined(VDJ_WIN))

    HRESULT hr;
    
    hr = GetDevice(VdjVideoEngineDirectX9, (void**) &D3DDevice);
    if(hr!=S_OK || D3DDevice == NULL) return S_FALSE;
    
#elif (defined(VDJ_MAC))
    
    glContext = CGLGetCurrentContext();
    
#endif
    
    // Size of the Video Window
    VideoWidth = width;
    VideoHeight = height;
    
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnDeviceClose()
{
    // ADD YOUR CODE HERE
    
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnStart()
{
    // ADD YOUR CODE HERE
    
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnStop()
{
    // ADD YOUR CODE HERE
    
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnDraw()
{
    // ADD YOUR CODE HERE
    HRESULT hr;
    TVertex *vertices;
    
    if(VideoWidth!=width || VideoHeight!=height)
    {
        hr = OnVideoResize(width,height);
    }
    
#if (defined(VDJ_WIN))
    
    hr = GetTexture(VdjVideoEngineDirectX9, (void **) &D3DTexture, &vertices);
    hr = D3DTexture->GetSurfaceLevel(0, &D3DSurface);
    
    SAFE_RELEASE(D3DTexture);
    SAFE_RELEASE(D3DSurface);
    
#elif (defined(VDJ_MAC))
    
    hr = GetTexture(VdjVideoEngineOpenGL, (void **) &GLTexture, &vertices);
    
    // glEnable(GL_TEXTURE_RECTANGLE_EXT);
    // glBindTexture(GL_TEXTURE_RECTANGLE_EXT, GLTexture);
    // glBegin(GL_TRIANGLE_STRIP);
    
    //for(int j=0;j<4;j++)
    //{
    //glColorD3D(vertices[j].color);
    //glTexCoord2f(vertices[j].tu, vertices[j].tv);
    //glVertex3f(vertices[j].position.x, vertices[j].position.y, vertices[j].position.z);
    //}
    
    //glEnd();
#endif
    
    
    hr = DrawDeck();
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT CMyPlugin8::OnVideoResize(int VidWidth, int VidHeight)
{
    // OnDeviceClose();
    // OnDeviceInit();
    return S_OK;
}
