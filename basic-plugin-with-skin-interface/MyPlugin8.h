#pragma once

#include "vdjPlugin8.h"


#include <stdio.h>

#if (defined(VDJ_WIN))
#include "resource.h"
#elif (defined(VDJ_MAC))
#include <string>
#include <fstream>
#define sprintf_s snprintf
#endif

class CMyPlugin8 : public IVdjPlugin8
{
public:
    HRESULT VDJ_API OnLoad();
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *infos);
    ULONG VDJ_API Release();
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface);
    HRESULT VDJ_API OnParameter(int id);
    HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize);

protected:
    typedef enum _ID_Interface
    {
        ID_SLIDER_1
    } ID_Interface;

    typedef struct _TRESOURCEREF
    {
#if (defined(VDJ_WIN))
        int id;
        char *type;
#elif (defined(VDJ_MAC))
        std::string name;
#endif
    } TRESOURCEREF;


private:
    //VDJ_WINDOW hWndParent;
    float m_Dry;
    float m_Wet;

    HRESULT LoadFileFromResource(TRESOURCEREF ref, DWORD& size, void*& data);
};
