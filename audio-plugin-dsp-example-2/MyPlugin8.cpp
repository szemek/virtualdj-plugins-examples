#include "MyPlugin8.h"

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
    SongBpm2=0;
    StartPos=0;

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

    SongBpm2 = SongBpm?SongBpm:(SampleRate/2); // by default 120bpm
    StartPos = int(SongPosBeats * SongBpm2);

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
HRESULT VDJ_API CMyPlugin8::OnProcessSamples(float *buffer, int nb)
{
    // ADD YOUR AUDIO TREATMENT CODE HERE USING THE AUDIO BUFFER *buffer OF 2*nb FLOAT SAMPLES (STEREO SIGNAL)

    float out[2], in[2];
    int pos;
    int CurrentPos;
    float xBeat;

    SongBpm2 = SongBpm?SongBpm:(SampleRate/2);
    pos = int(SongPosBeats * SongBpm2);

    // ConvertFloat2Short(bufferShort,buffer,2*nb);

    // we read the 'nb' stereo samples ( = 2 * 'nb' mono samples) from the sound buffer
    for(int i=0;i<nb;i++)
    {
        CurrentPos = pos + i;
        xBeat = (CurrentPos - StartPos)/float(SongBpm2); // 'x' beat(s) from StartPos

        // it's a stereo signal so we have 2 channels.
        for(int ch=0;ch<2;ch++)
        {
            in[ch] = buffer[2*i + ch];

            // for the case of this example,we only keep the left channel (ch==0) and mute the right channel (ch==1)
            if(ch==1) out[ch] = 0;
                else out[ch] = in[ch];

            buffer[2*i + ch] = out[ch];
        }
    }


    // ConvertShort2Float(buffer,bufferShort,2*nb);

    return S_OK;
}
//------------------------------------------------------------------------------------
void CMyPlugin8::ConvertFloat2Short(short *BufferOut,float *BufferIn, int BufferSize)
{
    int v;
    int j;

    for(j=0;j<BufferSize;j++)
    {
        v = round (32768.0f * BufferIn[j]);
        if (v < -32768) v = -32768;
        else if (v > 32767) v = 32767;
        BufferOut[j] = (short) v;
    }
}
//------------------------------------------------------------------------------------
void CMyPlugin8::ConvertShort2Float(float *BufferOut,short *BufferIn,int BufferSize)
{
    int j;

    for(j=0;j<BufferSize;j++)
    {
        BufferOut[j] = (float) BufferIn[j] / 32768.0f;
    }
}
