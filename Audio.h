#ifndef AUDIO_H_
#define AUDIO_H_
#include "CommonFunc.h"
class Audio{
public:
    Audio();
    ~Audio();
   bool LoadMusicTotal(std::string name);
   void PlayMusicTotal();
   void SetUpMusicEvent();
   void playSound(int id);

private:

     Mix_Music* music_total;
     Mix_Chunk* music_event[8];

};
#endif // AUDIO_H_
