#include "CSoundPlayerThread.h"
#include <stdio.h>
#include <wx/utils.h>
#include "RtAudio.h"

int CSoundPlayerThread::CSoundPlayerThread::PlayerCallback(
    void* outputBuffer, void* inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status, void* userData)
{
    if(userData!=0)
    {
        CSoundPlayerThread* player = static_cast<CSoundPlayerThread*>(userData);
        return player->OnCallback(outputBuffer,inputBuffer,nFrames,streamTime,status);
    }
    else
    {
        return 0;
    }
}


CSoundPlayerThread::CSoundPlayerThread(RtAudio* device)
    :device(device)
    ,filename()
    ,loop()
    ,isPlaying(false)
    ,isStopping(false)
    ,fd(0)
    ,written(0)
    ,count(0)
    ,sampleByes(1)
{
    if(device == 0)
        throw RtAudioError("null device pointer");
}
CSoundPlayerThread::~CSoundPlayerThread()
{
    this->stopAsync();
}

void CSoundPlayerThread::Init(const wxString& filename, bool loop)
{
    this->filename = filename;
    this->loop = loop;
}
void CSoundPlayerThread::run()
{
    this->play();
}
bool CSoundPlayerThread::getIsPlaying()
{
    return this->isPlaying;
}

void CSoundPlayerThread::playAsync()
{
    if(!this->getIsRunning()){
        this->isStopping = false;
        this->start();
    }
}

void CSoundPlayerThread::stopAsync(){
    if(this->getIsRunning())
    {
        this->isStopping = true;
        this->join();
    }
}


int CSoundPlayerThread::OnCallback(void* outputBuffer, void* inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status)
{
    if (outputBuffer!=0 && !isStopping) 
    { 
        size_t total = this->sampleByes*nFrames;
        size_t ret = fread(outputBuffer,1,total,this->fd);

        if(ret == total)
        {
            return 0;
        }
        else{
            return 1;
        }
    } 

    return 2;
}


int CSoundPlayerThread::play()
{
    if(this->device == 0) return FALSE;
    
    WAVContainer_t wav = {{0}}; 

    FILE* fd = fopen(filename, "rb"); 
    if (fd == 0) { 
        return FALSE; 
    }
    if (WAV_ReadHeader(fd, &wav) < 0) { 
       return FALSE;
    } 
    
    if(wav.format.format == WAV_FMT_PCM || wav.format.format == WAV_FMT_IEEE_FLOAT)
    {    
        //OK, we can process this
    }
    else
    {
        return FALSE;
    }
    
    RtAudioFormat rtf = 0;
    
    if(wav.format.format == WAV_FMT_IEEE_FLOAT)
    {
         switch(wav.format.sample_length)
         {
             case 32:
                rtf = RTAUDIO_FLOAT32;
                this->sampleByes = 4 * wav.format.channels;
                break;
             case 64:
                rtf = RTAUDIO_FLOAT64;
                this->sampleByes = 8 * wav.format.channels;
                break;
         }
    }
    else 
    {
        switch(wav.format.sample_length)
        {
            case 8:
                rtf = RTAUDIO_SINT8;
                this->sampleByes = 1*wav.format.channels;
                break;
            case 16:
                rtf = RTAUDIO_SINT16;
                this->sampleByes = 2*wav.format.channels;
                break;
            case 24:
                rtf = RTAUDIO_SINT24;
                this->sampleByes = 3*wav.format.channels;
                break;
            case 32:
                rtf = RTAUDIO_SINT32;                
                this->sampleByes = 4*wav.format.channels;
                break;
        }
    }
    
    if(rtf == 0)
    {
        return FALSE;
    }
    

    RtAudio::StreamParameters sp;
    sp.deviceId  = this->device->getDefaultOutputDevice();
    sp.firstChannel = 0;
    sp.nChannels =wav.format.channels;
    try{
        unsigned int _sps = 0;
        
        this->device->openStream(&sp,0,rtf,wav.format.sample_rate,&_sps,PlayerCallback);

        while(this->loop && !this->isStopping)
        {
            fseek(fd,sizeof(WAVContainer_t),SEEK_SET);

            this->written = 0;
            this->count = LE_INT(wav.chunk.length);

            if(this->device->isStreamOpen()){
                this->device->startStream();
                this->isPlaying = true;
                while(this->device->isStreamRunning())
                {
                    wxMicroSleep(1000);
                }
                this->isPlaying = false;
            }
        }
        
        this->device->closeStream();
    }
    catch(RtAudioError rte)
    {
            //Exception occurred
        fclose(fd);
        return FALSE;
    }
    fclose(fd); 

    return TRUE; 
}

