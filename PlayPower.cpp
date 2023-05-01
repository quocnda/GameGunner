#include "PlayPower.h"

PlayPower::PlayPower() {
   number=0;

}
PlayPower::~PlayPower()
{

}
void PlayPower::Init(SDL_Renderer* screen)
{
    std::cout<<"da vao day"<<'\n';
 LoadImg("image/Playpower.png",screen);
 number=3;
 if(pos_list.size()>0) {
    pos_list.clear();
 }
 Addpos(20);
 Addpos(60);
 Addpos(100);
}
void PlayPower::Addpos(const int x) {
pos_list.push_back(x);
}
void PlayPower::Show(SDL_Renderer* screen)
{
    for(int i=0;i<pos_list.size();i++)
    {
            rect_.x=pos_list.at(i);
            rect_.y=0;
            Render(screen);
    }
}
void PlayPower::Decrease() {
   number--;
   pos_list.pop_back();
}
void PlayPower::Increase()
{
    number++;
    int last_pos=pos_list.back();
    last_pos+=40;
    pos_list.push_back(last_pos);

}
