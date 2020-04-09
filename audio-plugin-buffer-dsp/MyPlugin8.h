#ifndef MYPLUGIN8_H
#define MYPLUGIN8_H

#include "vdjDsp8.h"

class CMyPlugin8 : public IVdjPluginBufferDsp8
{
public:
    HRESULT VDJ_API OnLoad();
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *infos);
    ULONG VDJ_API Release();
    HRESULT VDJ_API OnStart();
    HRESULT VDJ_API OnStop();
    short * VDJ_API OnGetSongBuffer(int pos, int nb);

private:
    int Bpm;
    int StartPos;
};

#endif
