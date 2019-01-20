#include "CSoundPlayerThread.h"


CSoundPlayerThread::CSoundPlayerThread()
    :filename()
    ,loop()
    ,isPlaying(false)
    ,isStopping(false)
{
}
CSoundPlayerThread::~CSoundPlayerThread()
{
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

ssize_t CSoundPlayerThread::SNDWAV_P_SaveRead(int fd, void *buf, size_t count) 
{ 
    ssize_t result = 0, res=0; 
 
    while (count > 0) { 
        if ((res = read(fd, buf, count)) == 0) 
            break; 
        if (res < 0) 
            return result > 0 ? result : res; 
        count -= res; 
        result += res; 
        buf = (char *)buf + res; 
    } 
    return result; 
} 
 
int CSoundPlayerThread::SNDWAV_Play(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd) 
{ 
restart:
    
    int load = 0, ret= 0; 
    off64_t written = 0; 
    off64_t c = 0; 
    off64_t count = LE_INT(wav->chunk.length);  
    load = 0; 
    while (written < count && !isStopping) { 
        /* Must read [chunk_bytes] bytes data enough. */ 
        do { 
            c = count - written; 
            if ((unsigned)c > sndpcm->chunk_bytes) 
                c = sndpcm->chunk_bytes; 
            c -= load; 
 
            if (c == 0) 
                break; 
            ret = SNDWAV_P_SaveRead(fd, sndpcm->data_buf + load, c); 
            if (ret < 0) { 
                //fprintf(stderr, "Error safe_read/n"); 
                return ret; 
            } 
            if (ret == 0) 
                break; 
            load += ret; 
        } while ((size_t)load < sndpcm->chunk_bytes); 
 
        /* Transfer to size frame */ 
        load = load * 8 / sndpcm->bits_per_frame; 
        ret = SNDWAV_WritePcm(sndpcm, load); 
        if (ret != load) 
            break; 
         
        ret = ret * sndpcm->bits_per_frame / 8; 
        written += ret; 
        load = 0; 
    } 
    if(loop && !isStopping)
    {
        lseek64(fd,0LL,SEEK_SET);
        WAVContainer_t wav = {{0}}; 
        WAV_ReadHeader(fd,&wav);
            
        goto restart;
    }
    isStopping = false;
    return 0;
} 


int CSoundPlayerThread::play()
{
    WAVContainer_t wav = {{0}}; 
    SNDPCMContainer_t playback= {0};

    int fd = open(filename, O_RDONLY); 
    if (fd < 0) { 
        return FALSE; 
    }
     
    if (WAV_ReadHeader(fd, &wav) < 0) { 
        goto Err; 
    } 
 
    if (snd_output_stdio_attach(&playback.log, stderr, 0) < 0) {
        goto Err; 
    } 
 
    if (snd_pcm_open(&playback.handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) { 
        goto Err; 
    } 
 
    if (SNDWAV_SetParams(&playback, &wav) < 0) { 
        goto Err; 
    } 
    
    isPlaying = true;

    snd_pcm_dump(playback.handle, playback.log); 
 
    SNDWAV_Play(&playback, &wav, fd); 
 
    snd_pcm_drain(playback.handle);
    
    isPlaying = false;
 
    close(fd); 
    free(playback.data_buf); 
    snd_output_close(playback.log); 
    snd_pcm_close(playback.handle); 
    return TRUE; 
 
Err: 
    close(fd); 
    if (playback.data_buf) free(playback.data_buf); 
    if (playback.log) snd_output_close(playback.log); 
    if (playback.handle) snd_pcm_close(playback.handle); 

    return FALSE;    
}

