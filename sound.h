#ifndef __SOUND_H__
#define __SOUND_H__

#include <wx/string.h>
// 0:	Synchronous does not stop until completed.
// 1:	Asynchronous returns immediately while sound is still playing.
// 2:	Don't use the default sound if the specified one cannot be found.
// 4:	In memory sound (not supported).
// 8:	Continue to loop the sound until another PLAYWAVE instruction is run.
//16:	Don't stop an already playing sound.

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
