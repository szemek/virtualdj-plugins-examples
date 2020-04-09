#include "MyPlugin8.h"

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetPluginInfo(TVdjPluginInfo8 *infos)
{
    infos->PluginName = "MyPlugin8";
    infos->Author = "Atomix Productions";
    infos->Description = "My first VirtualDJ 8 plugin";
    infos->Version = "1.0";
    infos->Flags = 0x00; // you could also use VDJFLAG_PROCESSAFTERSTOP if you want to process sound when the deck is stopped
    infos->Bitmap = NULL;

    return S_OK;
}
//---------------------------------------------------------------------------
ULONG VDJ_API CMyPlugin8::Release()
{
    delete this;
    return 0;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnStart()
{
    // ADD YOUR CODE HERE WHEN THE AUDIO PLUGIN IS STARTED

    Bpm = SongBpm?SongBpm:(SampleRate/2); // by default 120bpm
    StartPos = int(SongPosBeats * Bpm);

    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnStop()
{
    // ADD YOUR CODE HERE WHEN THE AUDIO PLUGIN IS STOPPED

    StartPos = 0;

    return S_OK;
}
//---------------------------------------------------------------------------
short * VDJ_API CMyPlugin8::OnGetSongBuffer(int pos, int nb)
{
    // ADD YOUR AUDIO TREATMENT CODE HERE USING THE AUDIO BUFFER *buffer OF 2*nb SHORT SAMPLES (STEREO SIGNAL)
    HRESULT hr;

    short *buffer;
    hr = GetSongBuffer(pos, nb, (short **) &buffer);


    return buffer;
}
