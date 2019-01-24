#include "sound.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <ctype.h> 
#include <errno.h> 
#include <limits.h> 
#include <time.h> 
#include <locale.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <assert.h> 
#include <math.h>
#include <wx/utils.h>
#include "RtAudio.h"


#ifndef PI
#define PI 3.141592653589793
#endif

unsigned int _sps = 0;
int _invfactor = 10;
int _pt = 0;
int _duration = 0;
double _volumeRate = 0.5;
double _angle = 0;
double _delta_angle = 0.0;

RtAudio RtAudioDevice;

int tone_callback( void *outputBuffer, void *inputBuffer,
                                unsigned int nFrames,
                                double streamTime,
                                RtAudioStreamStatus status,
                                void *userData )
{
    
    
    if(_pt<_duration){
		_pt += _invfactor;
		for(unsigned int j = 0;j<nFrames;j++)
        {
            ((short*)outputBuffer)[j] = (short)((0x7fff * _volumeRate) * sin(_angle));
            _angle += _delta_angle;
        }
        
        return 0; //continue;
    }
    else
    {
        return 1; //stop
    }
    
}

bool tone(int frequency,int duration,unsigned int sampleRate, double volumeRate)
{
    //NOTICE; like BEEP, no lower than 37Hz
    if(frequency<37)
    {
        frequency = 37;
    }
    _pt = 0;
    _duration = duration;
    _volumeRate = volumeRate;
       
    RtAudio::StreamParameters sp;
    sp.deviceId  = RtAudioDevice.getDefaultOutputDevice();
    sp.firstChannel = 0;
    sp.nChannels = 1;

    _sps = (sampleRate/(1000.0/ _invfactor));

    _delta_angle = frequency * 2.0 * PI/(1000.0 / _invfactor)/ _sps;
    try{
        RtAudioDevice.openStream(&sp,0,RTAUDIO_SINT16,sampleRate,&_sps,tone_callback);
        if(RtAudioDevice.isStreamOpen()){
            RtAudioDevice.startStream();
            while(RtAudioDevice.isStreamRunning())
            {
                wxMicroSleep(1000);
            }

            RtAudioDevice.closeStream();
        }
    }catch(RtAudioError rte)
    {
        //error occurred, maybe
        return false;
    }

    return true;
}
#ifndef _WINDOWS
#include "CSoundPlayerThread.h"

CSoundPlayerThread Player;

int sndPlaySound(const wchar_t* lpszSound, unsigned int fuSound)
{
    if(Player.getIsPlaying() && ((fuSound & SND_NOSTOP) == SND_NOSTOP))
    {
        return FALSE;
    }
    if(lpszSound == 0)
    {
        //stop playing
        if(Player.getIsPlaying())
        {
            Player.stopAsync();
        }

        return TRUE;        
    }
    else if((fuSound & SND_SYNC) == SND_SYNC)
    {
        Player.stopAsync();
        
        Player.Init(lpszSound, ((fuSound & SND_LOOP)==SND_LOOP));
        return Player.play();
    }    
    else if((fuSound & SND_ASYNC) == SND_ASYNC)
    {
        Player.stopAsync();
        Player.Init(lpszSound, ((fuSound & SND_LOOP)==SND_LOOP));
        Player.playAsync();
        
        return TRUE;
    }
    return FALSE;

}

#endif

