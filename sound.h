#ifndef __SOUND_H__
#define __SOUND_H__

#include <wx/string.h>

#define SND_SYNC        0x0000
#define SND_ASYNC       0x0001
//NODEFAULT is ignored
#define SND_NODEFAULT   0x0002
//MEMORY is ignored
#define SND_MEMORY      0x0004
#define SND_LOOP        0x0008
#define SND_NOSTOP      0x0010

extern bool tone(int frequency,int duration, unsigned int sampleRate = 44100, double volumeRate = 0.5);
#ifndef _WINDOWS
extern int sndPlaySound(const wchar_t* lpszSound, unsigned int fuSound);
#endif
#endif
