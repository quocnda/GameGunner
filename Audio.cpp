#include "Audio.h"

Audio::Audio()
{
    music_total=NULL;
   for(int i=0;i<3;i++)
    {
        music_event[i]=NULL;
    }
}
Audio::~Audio()
{

    Mix_FreeMusic(music_total);
    music_total=NULL;
    for(int i=0;i<3;i++)
    {
        Mix_FreeChunk(music_event[i]);
        music_event[i]=NULL;
    }
}
bool Audio::LoadMusicTotal(std::string name)
{
    music_total=Mix_LoadMUS(name.c_str());
    if(music_total==NULL)
    {
        std::cout<<"music_total==NULL"<<'\n';
        return 0;
    }
    return 1;
}
void Audio::PlayMusicTotal()
{
    Mix_PlayMusic(music_total,0);
}
void Audio::SetUpMusicEvent()
{
    music_event[0]=Mix_LoadWAV("sound/0.wav");
    music_event[1]=Mix_LoadWAV("sound/1.wav");
    music_event[2]=Mix_LoadWAV("sound/2.wav");
    music_event[3]=Mix_LoadWAV("sound/3.wav");
    music_event[4]=Mix_LoadWAV("sound/bullet_boss.wav");
    music_event[5]=Mix_LoadWAV("sound/game_device.wav");
    music_event[6]=Mix_LoadWAV("sound/hurt.wav");
    music_event[7]=Mix_LoadWAV("sound/ouch.wav");
}
void Audio::playSound(int id)
{
    Mix_PlayChannel(-1,music_event[id],0);
}
