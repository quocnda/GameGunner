#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    x_val = rand() % 20;
    y_val = rand() % 20;
    x_pos = 448;
    y_pos = 448;
    frame_1=0;
    frame_=0;

    Threat_width=0;
    Threat_height=0;
    status_=0;
    Dir=(rand()%4)+1;
    is_alive_=true;
    bi_ban=3;
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret) {
         Threat_width=rect_.w/5;
         Threat_height=rect_.h/2;
    }
    //std::cout<<Main_width<<" "<<Main_height<<'\n';
    return ret;
}

void ThreatObject::Show(SDL_Renderer* screen)
{

   if(Dir==1) {
        frame_++;
       }
    else if(Dir==2) {
        frame_1++;
       }
    else {
        frame_1++;
        frame_++;
       }

       if(frame_1>=5) {frame_1=0;}
       if(frame_>=5) {frame_=0;}

      rect_.x=x_pos-map_x;
      rect_.y=y_pos-map_y;

      SDL_Rect *current_clip=NULL;
   if(Dir==1) {

        current_clip=&clip_left[frame_];

    }
    else if (Dir==2) {
           current_clip=&clip_right[frame_1];

    }
    else {
         current_clip=&clip_left[frame_];

    }


    SDL_Rect renderquad={rect_.x,rect_.y,Threat_width,Threat_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
}
void ThreatObject::SetClip()
{
    for(int i=0;i<=4;i++) {
        clip_right[i].x=i*Threat_width;
        clip_right[i].y=0;
        clip_right[i].w=Threat_width;
        clip_right[i].h=Threat_height;
    }
    for(int j=0;j<=4;j++) {
        clip_left[j].x=j*Threat_width;
        clip_left[j].y=Threat_height;
        clip_left[j].w=Threat_width;
        clip_left[j].h=Threat_height;
    }


}

void ThreatObject::DoPlayer(Map& map_data)
{
    if(Dir==2){
        x_val = 1;
        y_val = 0;
    }
    else if(Dir==1){
        x_val = -1;
        y_val = 0;
    }
    else if(Dir==3) {
        y_val=1;
        x_val=0;
    }
    else if(Dir==4) {
        y_val=-1;
        x_val=0;
    }
    CheckToMap(map_data);
}

void ThreatObject::CheckToMap(Map& map_data)
{


    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;


    int height_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;

    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + FRAME - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y){
        if(x_val > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if((val1!=1) || (val2!=1)){
                x_pos=x2*TILE_SIZE;
                x_pos-=Threat_width+1;
                x_val=0;
                Dir=(rand()%4)+1;

            }
        }
        else if(x_val < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if((val1!=1) || (val2!=1)){
                 x_pos=(x1+1)*TILE_SIZE;
                x_val=0;
                Dir=(rand()%4)+1;
            }
        }
    }

    //check vertical
    int width_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min - 1) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + FRAME - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y){
        if(y_val > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1!=1) || val2!=1){
                    y_pos=y2*TILE_SIZE;
                y_pos-=(Threat_height+1);
                y_val=0;
                Dir=(rand()%4)+1;
            }
        }
        else if(y_val < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1!=1 || val2!=1){
                    y_pos=(y1+1)*TILE_SIZE;
                y_val=0;
                Dir=(rand()%4)+1;

            }
        }
    }
    x_pos += x_val;
    y_pos += y_val;
     if(x_pos<0) {
        x_pos=0;
        Dir=(rand()%4)+1;
    }
    else if(x_pos+Threat_width>map_data.max_x_) {
        x_pos=map_data.max_x_-Threat_width-1;
        Dir=(rand()%4)+1;

    }

}

bool ThreatObject::CheckToBullet(MainObject& p)
{
    bool is_ban=false;
    std::vector<Bullet*> bullet = p.Getamo();
    SDL_Rect mainRect = this->rect_;
    mainRect.w=mainRect.w/5;

    mainRect.h=mainRect.h/2;
    SDL_Rect subRect = p.GetRect();
    subRect.w=subRect.w/6;
    subRect.h=subRect.h/5;
    if(checkCollision(mainRect, subRect))  {
    p.set_alive(false);
    is_alive_=false;
    }
    for(int i = 0; i < bullet.size(); i++){
        SDL_Rect tmpRect = bullet[i]->GetRect();
        if(checkCollision(mainRect, tmpRect)){
                is_ban=true;
                if(bullet[i]->get_type()==2)
                {
                    bi_ban=bi_ban-p.get_damage_shuriken();
                }
                else {
                    bi_ban=bi_ban-p.get_damage_rasengan();
                }

            bullet.erase(bullet.begin() + i);
            p.Setamolist(bullet);
        }
    }
    if(bi_ban<=0)
    {
       is_alive_=false;
    }
    return is_ban;
}

