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

    is_alive=true;
    bi_ban=10;
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
    }
    A.SetUpMusicEvent();
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
    for(int i=0;i<p_bullet_list.size();i++) {
        p_bullet_list[i]->HandleMove(SCREEN_WIDTH-10,SCREEN_HEIGHT-10,map_data,map_x,map_y);
        if(p_bullet_list[i]->get_col_wall()!=0)
        {
            count_bullet_col_wall++;
        }
        p_bullet_list[i]->Show(screen,map_x,map_y);
    }
    if(count_bullet_col_wall>=15)
    {

        count_bullet_col_wall=0;
        for(int i=0;i<16;i++)
        {
            p_bullet_list[i]->set_col_wall();
            p_bullet_list[i]->set_is_move(true);
           if(i<8) { p_bullet_list[i]->set_pos(x_pos,y_pos);}
           else {p_bullet_list[i]->set_pos(x_pos-10,y_pos+10);}
        }
    }

}
bool BossObject::CheckToBullet(MainObject& p)
{
     bool is_ban=false;
    std::vector<Bullet*> bullet = p.Getamo();
    SDL_Rect mainRect = this->rect_;
    mainRect.w=mainRect.w/24;
    mainRect.h=mainRect.h-2;
    SDL_Rect subRect = p.GetRect();
    subRect.w=subRect.w/6;
    subRect.x+=4;
    subRect.h=subRect.h/5;
    subRect.y=subRect.y+5;
    for(int i=0;i<p_bullet_list.size();i++)
    {
        SDL_Rect tmp_rect=p_bullet_list[i]->GetRect();
        if(checkCollision(subRect,tmp_rect))
        {
            std::cout<<i<<'\n';
           p.set_alive(false);
            p_bullet_list.erase(p_bullet_list.begin()+i);
        }

    }
    for(int i = 0; i < bullet.size(); i++){
        SDL_Rect tmpRect = bullet[i]->GetRect();
        if(checkCollision(mainRect, tmpRect)){
                is_ban=true;
                if(bullet[i]->get_type()==2)
                {
                    A.playSound(7);
                    bi_ban=bi_ban-p.get_damage_shuriken();
                }
                else {
                        A.playSound(7);
                    bi_ban=bi_ban-p.get_damage_rasengan();
                }

            bullet.erase(bullet.begin() + i);
            p.Setamolist(bullet);
        }
    }
    if(bi_ban<=0)
    {
       is_alive=false;
    }
    return is_ban;
}
