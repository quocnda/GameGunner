#include "BossObject.h"

BossObject::BossObject()
{
    x_pos=0;
    y_pos=0;
    x_val=0;
    y_val=0;
    Boss_width=0;
    Boss_height=0;
    map_x=0;
    map_y=0;
    frame=0;

    count_bullet_col_wall=0;
}
BossObject::~BossObject()
{

}
bool BossObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret) {
         Boss_width=rect_.w/24+1;
         Boss_height=rect_.h-1;
         std::cout<<Boss_width<<" "<<Boss_height<<'\n';
    }
    //std::cout<<Main_width<<" "<<Main_height<<'\n';
    return ret;
}
void BossObject::SetClip()
{
    for(int i=0;i<24;i++){
        clip_boss[i].x=i*Boss_width;
        clip_boss[i].y=0;
        clip_boss[i].w=Boss_width;
        clip_boss[i].h=Boss_height;
    }
}
void BossObject::Show(SDL_Renderer* screen)
{
    frame++;
    if(frame>=24) {frame=0;}
    rect_.x=x_pos-map_x;
    rect_.y=y_pos-map_y;
    SDL_Rect *current_clip=NULL;
    current_clip=&clip_boss[frame];
    SDL_Rect renderquad={rect_.x,rect_.y,Boss_width,Boss_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BossObject::MakeBullet(Map& map_data,SDL_Renderer* screen)
{
     /*p_bullet_list[0]->HandleMove(0,0,map_data);
        if(p_bullet_list[0]->get_col_wall()!=0)
        {
            std::cout<<count_bullet_col_wall<<" ";
            count_bullet_col_wall++;
        }
       p_bullet_list[0]->Show(screen,map_x,map_y);

    */
    for(int i=0;i<16;i++) {
           // std::cout<<p_bullet_list[i]->toa_do_x()<<" "<<p_bullet_list[i]->toa_do_y()<<'\n';
        p_bullet_list[i]->HandleMove(SCREEN_WIDTH-10,SCREEN_HEIGHT-10,map_data);
        if(p_bullet_list[i]->get_col_wall()!=0)
        {
            count_bullet_col_wall++;
        }
        p_bullet_list[i]->Show(screen,map_x,map_y);
    }
    if(count_bullet_col_wall>=15)
    {
        for(int i=0;i<16;i++)
        {
            p_bullet_list[i]->set_col_wall();
            count_bullet_col_wall=0;
            p_bullet_list[i]->set_is_move(true);
            p_bullet_list[i]->set_pos(x_pos,y_pos);
        }
    }
}
