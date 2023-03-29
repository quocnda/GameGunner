
#include "MainObject.h"

MainObject::MainObject() {
    frame_1=0;
 frame_=0;
frame_0=0;
frame_banphai=0;
frame_banphai=0;
da_ban=false;

so_dan=20;
so_rasengan=20;
  Dir=4;
 x_pos_=0;
 y_pos_=128;
 y_val_=0;
 x_val_=0;
 Main_width=0;
 Main_height=0;
 status_=0;
 input_type.left=0;
 input_type.right=0;
 input_type.down=0;
 input_type.up=0;

 damage_dan=1;
 damage_rasengan=3;

 is_alive=true;

 toc_do=0;
 map_x=0;
 map_y=0;
}
MainObject::~MainObject() {
     free();
}
bool MainObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret) {
         Main_width=rect_.w/6;
         Main_height=rect_.h/5;
    }
    //std::cout<<Main_width<<" "<<Main_height<<'\n';
    return ret;
}
void MainObject::Show(SDL_Renderer* screen)
{
    if(status_==0&&da_ban)
    {
        if(Dir==3) {
            frame_bantrai++;
        }
        else if (Dir==4) {
            frame_banphai++;
        }
    }
    else {
    if(input_type.right==1||input_type.up==1||input_type.down==1||input_type.left==1)
     {
       if(status_==3) {
            frame_++;
       }
       else if(status_==4) {
                  frame_1++;
       }
     else  if(status_==0)
    {
        frame_0++;
    }
       else {
        frame_1++;
        frame_++;
       }
       if(frame_1>=6) {frame_1=0;}
       if(frame_>=6) {frame_=0;}

     }
    }
    if(frame_banphai>=7) {frame_banphai=0;da_ban=false;}
       if(frame_bantrai>=7) {frame_bantrai=0;da_ban=false;}
    rect_.x=x_pos_-map_x;
	rect_.y = y_pos_-map_y;
    SDL_Rect *current_clip=NULL;
    if(status_==0&&!da_ban)
    {
        current_clip=&clip_dungyen[frame_0];
    }
    else
    {
        if(status_==0&&da_ban)
        {
            if(Dir==4) {
                current_clip=&clip_bandanphai[frame_banphai];
            }
            else if (Dir==3) {
                current_clip=&clip_bandantrai[frame_bantrai];
            }

        }
        else {
          if(Dir==4) {
        if(status_==4||status_==2||status_==1)  {
                current_clip=&clip_right[frame_1];
         }
    }
    else if (Dir==3) {
             if(status_==3||status_==1||status_==2) {
             current_clip=&clip_left[frame_];
            }
          }
        }
    }


    SDL_Rect renderquad={rect_.x,rect_.y,Main_width,Main_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void MainObject::handle(SDL_Event &e,SDL_Renderer* screen)
{
     if(e.type==SDL_KEYDOWN &&e.key.repeat==0)
    {
         switch( e.key.keysym.sym )
        {
            case SDLK_w: status_=1;input_type.up=1;input_type.down=0;input_type.left=0;input_type.right=0; break;
            case SDLK_s: status_=2;input_type.up=0;input_type.down=1;input_type.left=0;input_type.right=0; break;
            case SDLK_a: status_=3;input_type.up=0;input_type.down=0;input_type.left=1;input_type.right=0;Dir=3; break;
            case SDLK_d: status_=4;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=1;Dir=4; break;

           // case SDLK_e: bomb.SetBomno(true);dat_bom=false;break;
        }
    }
     else if (e.type==SDL_KEYUP&&e.key.repeat==0)
    {
         switch( e.key.keysym.sym )
        {
           case SDLK_w: status_=0;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0; break;
            case SDLK_s: status_=0;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0; break;
            case SDLK_a: status_=0;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0;Dir=3; break;
            case SDLK_d: status_=0;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0;Dir=4; break;

            //case SDLK_e: bomb.SetBomno(false);dat_bom=false;break;
        }
    }
    else if (e.type==SDL_MOUSEBUTTONDOWN)
     {
         da_ban=true;
         Bullet* p_amo=new Bullet();
         if(e.button.button==SDL_BUTTON_LEFT)
         {
             so_dan--;
             if(so_dan>=0)
             {
                 p_amo->setwh(WIDTHLASER,HEIGHTLASER);
             p_amo->LoadImg("laser.png",screen);
             p_amo->set_type(Bullet::LASER);
             p_amo->SetDir(Dir);
        }
         else {so_dan=-1;}
          // std::cout<<"da duoc";
         }
         else if (e.button.button==SDL_BUTTON_RIGHT)
         {
             so_rasengan--;
             if(so_rasengan>=0)
             {
                 p_amo->setwh(WIDTHSPHERE,HEIGHTSPHERE);
             p_amo->LoadImg("sphere.png",screen);
             p_amo->set_type(Bullet::SPHERE);
             p_amo->SetDir(Dir);
             }
             else {so_rasengan=-1;}


         }
        // p_amo->SetRect(this->rect_.x+this->rect_.w/5-5,this->rect_.y+this->rect_.h*0.25);
        if(so_dan>=0||so_rasengan>=0)
        {
            p_amo->set_pos(x_pos_, y_pos_);
         if(p_amo->get_type()==2) {
             if(p_amo->GetDir()==3) {
            p_amo->set_val_bullet(-2);
             }
         else {
            p_amo->set_val_bullet(2);
           }
         }
         else
         {
              if(p_amo->GetDir()==3) {
            p_amo->set_val_bullet(-10);
           }
           else {
            p_amo->set_val_bullet(10);
         }
         }
         p_amo->set_is_move(true);
         p_amo_list.push_back(p_amo);
        }
            std::cout<<"so dan "<<so_dan<<" so rasengan "<<so_rasengan<<'\n';
     }
}
void MainObject::SetClip()
{
    for(int i=0;i<=5;i++) {
        clip_dungyen[i].x=i*Main_width;
        clip_dungyen[i].y=0;
        clip_dungyen[i].w=Main_width;
        clip_dungyen[i].h=Main_height;
    }
    for(int j=0;j<=5;j++) {
        clip_bandantrai[j].x=j*Main_width;
        clip_bandantrai[j].y=Main_height;
        clip_bandantrai[j].w=Main_width;
        clip_bandantrai[j].h=Main_height;
    }
    for(int i=0;i<=5;i++)
    {
        clip_bandanphai[i].x=i*Main_width;
        clip_bandanphai[i].y=2*Main_height;
        clip_bandanphai[i].w=Main_width;
        clip_bandanphai[i].h=Main_height;
    }
    for(int i=0;i<=5;i++)
    {
        clip_left[i].x=i*Main_width;
        clip_left[i].y=3*Main_height;
        clip_left[i].w=Main_width;
        clip_left[i].h=Main_height;
    }
    for(int i=0;i<=5;i++)
    {
        clip_right[i].x=i*Main_width;
        clip_right[i].y=4*Main_height;
        clip_right[i].w=Main_width;
        clip_right[i].h=Main_height;
    }

}



void MainObject::DoPlayer(Map& map_data)
{
  if(input_type.left==1) {
    x_val_=-toc_do;
    y_val_=0;
  }
  else if(input_type.right==1) {
    x_val_=toc_do;
    y_val_=0;
  }
  else if(input_type.up==1) {
    y_val_=-toc_do;
    x_val_=0;
  }
  else if(input_type.down==1) {
    y_val_=toc_do;
    x_val_=0;
  }
  else {
    x_val_=0;
    y_val_=0;
  }

  checktomap(map_data);
  Camera(map_data);


}
void MainObject::checktomap(Map & map_data) {
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    int height_min=Main_height < TILE_SIZE ? Main_height : TILE_SIZE;
    x1=(x_pos_+x_val_)/TILE_SIZE;
    x2=(x_pos_+x_val_+Main_width-1)/TILE_SIZE;

    y1=(y_pos_)/TILE_SIZE;
    y2=(y_pos_+height_min-1)/TILE_SIZE;

    if(x1>=0&&x2<MAP_X&&y1>=0&&y2<MAP_Y)
    {
        int val1=map_data.tile[y1][x2];
        int val2=map_data.tile[y2][x2];
        if(val1==2||val2==2)
        {
            so_dan+=10;
            so_rasengan+=10;
            map_data.tile[y1][x2]=1;
            map_data.tile[y2][x2]=1;
        }
         if(val1==4||val2==4) {
             map_data.tile[y1][x2]=1;
            map_data.tile[y2][x2]=1;
         }
          if(val1==3||val2==3)
        {
            damage_dan+=1;
            damage_rasengan+=1;
            map_data.tile[y1][x2]=1;
            map_data.tile[y2][x2]=1;
        }
        if(x_val_>0) {
            if(map_data.tile[y1][x2]!=1||map_data.tile[y2][x2]!=1) {
                x_pos_=x2*TILE_SIZE;
                x_pos_-=Main_width+1;
                x_val_=0;
            }

        }
        val1=map_data.tile[y1][x1];
        val2=map_data.tile[y2][x1];
        if(val1==2||val2==2) {
                so_dan+=10;
            so_rasengan+=10;
            map_data.tile[y1][x1]=1;
            map_data.tile[y2][x1]=1;
        }
        if(val1==3||val2==3) {
            damage_dan+=1;
            damage_rasengan+=1;
            map_data.tile[y1][x1]=1;
            map_data.tile[y2][x1]=1;
        }
                 if(val1==4||val2==4) {
             map_data.tile[y1][x2]=1;
            map_data.tile[y2][x2]=1;
         }

        if(x_val_<0) {
            if(map_data.tile[y1][x1]!=1||map_data.tile[y2][x1]!=1) {
                x_pos_=(x1+1)*TILE_SIZE;
                x_val_=0;
            }
        }
    }


    int width_min=Main_width<TILE_SIZE ? Main_width : TILE_SIZE;
    x1=(x_pos_)/TILE_SIZE;
    x2=(x_pos_+width_min)/TILE_SIZE;

    y1=(y_pos_+y_val_)/TILE_SIZE;
    y2=(y_pos_+y_val_+Main_height-1)/TILE_SIZE;

    if(x1>=0&&x2<MAP_X&&y1>=0&&y2<MAP_Y)
    {
        int val_1=map_data.tile[y2][x1];
        int val_2=map_data.tile[y2][x2];
        if(y_val_>0) {
                if(val_1==2||val_2==2)
            {
                so_dan+=10;
            so_rasengan+=10;
            map_data.tile[y2][x1]=1;
            map_data.tile[y2][x2]=1;
           }
           if(val_1==3||val_2==3) {
            damage_dan+=1;
            damage_rasengan+=1;
            map_data.tile[y2][x1]=1;
            map_data.tile[y2][x2]=1;
           }
           if(val_1==4||val_2==4)
            {
            map_data.tile[y2][x1]=1;
            map_data.tile[y2][x2]=1;
           }
            if(map_data.tile[y2][x1]!=1||map_data.tile[y2][x2]!=1) {
                y_pos_=y2*TILE_SIZE;
                y_pos_-=(Main_height+1);
                y_val_=0;
            }
        }

        if(y_val_<0) {
                 val_1=map_data.tile[y1][x1];
             val_2=map_data.tile[y1][x2];
        if(val_2==2||val_1==2)
        {
            so_dan+=10;
            so_rasengan+=10;
            map_data.tile[y1][x1]=1;
            map_data.tile[y1][x2]=1;
        }
        if(val_1==3||val_2==3) {
            damage_dan+=1;
            damage_rasengan+=1;
            map_data.tile[y2][x1]=1;
            map_data.tile[y2][x2]=1;
        }
        if(val_1==4||val_2==4)
            {
            map_data.tile[y2][x1]=1;
            map_data.tile[y2][x2]=1;
           }
            if(map_data.tile[y1][x1]!=1||map_data.tile[y1][x2]!=1){
                y_pos_=(y1+1)*TILE_SIZE;
                y_val_=0;

            }
        }
    }
    x_pos_+=x_val_;
    y_pos_+=y_val_;
    if(x_pos_<0) {
        x_pos_=0;
    }
    else if(x_pos_+Main_width>map_data.max_x_) {
        x_pos_=map_data.max_x_-Main_width-1;

    }

}
void MainObject::Camera(Map& map_data) {
   map_data.start_x_=x_pos_-(SCREEN_WIDTH/2);
   if(map_data.start_x_<0) {
    map_data.start_x_=0;
   }
   else if(map_data.start_x_+SCREEN_WIDTH>=map_data.max_x_)
   {
       map_data.start_x_=map_data.max_x_-SCREEN_WIDTH;
   }
   map_data.start_y_=y_pos_-(SCREEN_HEIGHT/2);
   if(map_data.start_y_<0) {
    map_data.start_y_=0;
   }
   else if (map_data.start_y_+SCREEN_HEIGHT>=map_data.max_y_) {
    map_data.start_y_=map_data.max_y_-SCREEN_HEIGHT;
   }
}

void MainObject::RemoveBullet(const int &idx)
{

        for(int i=0;i<p_amo_list.size();i++) {
                if(idx<p_amo_list.size())
                {
                     Bullet* p_amo=p_amo_list.at(idx);
        p_amo_list.erase(p_amo_list.begin()+idx);
        if(p_amo!=NULL)
        {
            delete p_amo;
            p_amo=NULL;
        }
                }

    }
}

void MainObject::HandleBullet(SDL_Renderer* screen,Map& map_data)
{
    for(int i = 0; i < p_amo_list.size(); i++)
    {

        if(p_amo_list[i] != NULL)
        {
            if(p_amo_list[i]->get_is_move() == true)
            {

                p_amo_list[i]->HandleMove(SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10, map_data);
                p_amo_list[i]->Show(screen, map_x, map_y);
            }
            else
            {
                //std::cout << p_bullet_list_.size() << std::endl;
               p_amo_list.erase(p_amo_list.begin() + i);
                /*if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }*/
            }
        }
    }
}
