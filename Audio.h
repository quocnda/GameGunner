#ifndef AUDIO_H_
#define AUDIO_H_
#include "CommonFunc.h"
class Audio{
public:
    Audio();
    ~Audio();
    bool LoadMusic(std::string name);
    bool LoadWav(std::string name_wav);
    void playMusic();
    void playWav();
    void stopMusic() {;}
    void stopWav() {;}
    void free();
private:
     Mix_Chunk* wav;
     Mix_Music* music;
};
#endif // AUDIO_H_
