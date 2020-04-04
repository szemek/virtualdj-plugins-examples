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
    infos->Flags = 0x00;
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

    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnStop()
{
    // ADD YOUR CODE HERE WHEN THE AUDIO PLUGIN IS STOPPED

    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnProcessSamples(float *buffer, int nb)
{
    // ADD YOUR AUDIO TREATMENT CODE HERE USING THE AUDIO BUFFER *buffer OF 2*nb FLOAT SAMPLES (STEREO SIGNAL)
    // A FLOAT SAMPLE HAS A VALUE BETWEEN -1.0f AND 1.0f

    float SampleOut_Left, SampleOut_Right;
    float SampleIn_Left, SampleIn_Right;
    int i;

    // we read the 'nb' stereo samples ( = 2 * 'nb' mono samples) from the sound buffer
    // read left samples : buffer[0], buffer[2], ... , buffer[2*nb-2]
    // read right samples : buffer[1], buffer[3], ... , buffer[2*nb-1]

    for(i=0;i<nb;i++)
    {
        SampleIn_Left = buffer[2*i];
        SampleIn_Right = buffer[2*i+1];

        // ADD YOUR AUDIO TREATMENT CODE HERE.
        // For the purpose of this example, we mute the left channel and keep (copy) the right channel
        float WetDry = 0.0f; // we want to force the sample to 0 (no volume)

        SampleOut_Left = WetDry * SampleIn_Left ;
        SampleOut_Right = SampleIn_Right;

        buffer[2*i] = SampleOut_Left;
        buffer[2*i+1] = SampleOut_Right;
    }

    return S_OK;
}
