#ifndef __CSHOUNDPLAYERTHREAD_H__
#define __CSHOUNDPLAYERTHREAD_H__
#include "CUThread.h"
#include "wx/string.h"
#include "wav_parser.h" 
#include "RtAudio.h"

class CSoundPlayerThread : public CUThread
{
protected:
    static int PlayerCallback( void *outputBuffer, void *inputBuffer,
                                unsigned int nFrames,
                                double streamTime,
                                RtAudioStreamStatus status,
                                void *userData );
public:
    CSoundPlayerThread();
    ~CSoundPlayerThread();
    
public:
    void Init(const wxString& filename, bool loop);
    
    virtual void run();
    
    int play();
    void playAsync();
    
    void stopAsync();
    
public:
    bool getIsPlaying();
    
protected:

    virtual int OnCallback( void *outputBuffer, void *inputBuffer,
                                unsigned int nFrames,
                                double streamTime,
                                RtAudioStreamStatus status);

protected:
    
    wxString filename;
    bool loop;    
    bool isPlaying;
    bool isStopping;
    
    FILE* fd;
    
    off64_t written; 
    off64_t c; 
    off64_t count; 
    
    unsigned int sampleByes;
    
};

#endif
