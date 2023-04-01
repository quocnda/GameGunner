#include "Audio.h"

 Audio::Audio() {
  wav=NULL;
  music=NULL;
 }
Audio::~Audio()
{
    Mix_FreeChunk(wav);
    wav=NULL;
    Mix_FreeMusic(music);
    music=NULL;
}
bool Audio::LoadMusic(std::string name)
{
    music=Mix_LoadMUS(name.c_str());
    if(music==NULL)
    {
        return false;
    }
    return true;
}
bool Audio::LoadWav(std::string name_wav)
{
    wav=Mix_LoadWAV(name_wav.c_str());
    if(wav==NULL)
    {
        return false;
    }
    return true;
}
void Audio::playMusic()
{
    Mix_PlayMusic(music,0);

}
void Audio::playWav()
{
    Mix_PlayChannel(-1,wav,0);
}
void Audio::free()
{
    Mix_FreeChunk(wav);
    wav=NULL;
    Mix_FreeMusic(music);
    music=NULL;
}
