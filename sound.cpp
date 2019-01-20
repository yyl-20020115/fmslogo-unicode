#include "sound.h"

#include <stdio.h> 
#include <malloc.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <getopt.h> 
#include <fcntl.h> 
#include <ctype.h> 
#include <errno.h> 
#include <limits.h> 
#include <time.h> 
#include <locale.h> 
#include <sys/unistd.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <alsa/asoundlib.h> 
#include <assert.h> 
#include <math.h>
#include "CSoundPlayerThread.h"

#ifndef PI
#define PI 3.141592653589793
#endif

bool tone(int frequency,int duration,unsigned int sampleRate, double volumeRate)
{
    int err = 0;

    if(sampleRate<8000)
    {
        sampleRate = 8000;
    }
    
    int sps = 0;
    int dir = 0;
    double angle = 0;
    double all_angles_per_ms = 0.0;
    double delta_angle = 0.0;
    snd_pcm_t *playback_handle = 0;
    snd_pcm_hw_params_t *hw_params = 0;
    short* buffer = 0;


    if ((err = snd_pcm_open (&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        goto ExitMe;
    }
        
    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        goto ExitMe;
    }
                
    if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0) {
        goto ExitMe;
    }

    if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        goto ExitMe;     
    }

    if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        goto ExitMe;   
    }

    if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &sampleRate,&dir)) < 0) {
        goto ExitMe;     
    }
    
    sps = (sampleRate/1000.0);
    all_angles_per_ms = frequency * 2.0 * PI/1000.0;
    delta_angle = all_angles_per_ms / sps;
    
    buffer = (short*) malloc(sizeof(short)*sps);
    
    if(buffer == 0){
        err = -1;
        goto ExitMe;
    }


    if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, 1)) < 0) {
        goto ExitMe; 
    }

    if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0) {
        goto ExitMe;   
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (playback_handle)) < 0) {
        goto ExitMe; 
    }

  
    for (int i = 0; i < duration; ++i) {
        for(int j = 0;j<sps;j++)
        {
            buffer[j] = (short)((0x7fff * volumeRate) * sin(angle));
            angle += delta_angle;
        }
        
        int cnt = 0;
        if ((cnt = snd_pcm_writei (playback_handle, buffer, 128)) != sps) {
            err = -1;
            goto ExitMe;
        }
    }

ExitMe:
    if(playback_handle!=0){        
        snd_pcm_close (playback_handle);
        playback_handle = 0;
    }
    if(buffer!=0){
        free(buffer);
        buffer = 0;
    }
    return err == 0;
}
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


