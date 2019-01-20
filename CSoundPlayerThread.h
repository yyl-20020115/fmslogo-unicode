#ifndef __CSHOUNDPLAYERTHREAD_H__
#define __CSHOUNDPLAYERTHREAD_H__
#include "CUThread.h"
#include "wx/string.h"
#include "wav_parser.h" 
#include "sndwav_common.h" 
class CSoundPlayerThread : public CUThread
{
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
    
    ssize_t SNDWAV_P_SaveRead(int fd, void *buf, size_t count) ;
    int SNDWAV_Play(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd);
protected:
    
    wxString filename;
    bool loop;    
    bool isPlaying;
    bool isStopping;
};

#endif
