
#include "MainObject.h"

MainObject::MainObject() {
    frame_1=0;
 frame_=0;

  Dir=4;
 x_pos_=0;
 y_pos_=0;
 y_val_=0;
 x_val_=0;
 Main_width=0;
 Main_height=0;
 status_=4;
 input_type.left=0;
 input_type.right=0;
 input_type.down=0;
 input_type.up=0;

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
         Main_width=rect_.w/5;
         Main_height=rect_.h/2;
    }
    //std::cout<<Main_width<<" "<<Main_height<<'\n';
    return ret;
}
void MainObject::Show(SDL_Renderer* screen)
{
     if(input_type.right==1||input_type.up==1||input_type.down==1||input_type.left==1)
     {
       if(status_==3) {
        frame_++;
       }
       else if(status_==4) {
        frame_1++;
       }
       else {
        frame_1++;
        frame_++;
       }
       if(frame_1>=5) {frame_1=0;}
       if(frame_>=5) {frame_=0;}
     }

    rect_.x=x_pos_-map_x;
	rect_.y = y_pos_-map_y;

    SDL_Rect *current_clip=NULL;
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
           case SDLK_w: status_=1;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0; break;
            case SDLK_s: status_=2;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0; break;
            case SDLK_a: status_=3;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0;Dir=3; break;
            case SDLK_d: status_=4;input_type.up=0;input_type.down=0;input_type.left=0;input_type.right=0;Dir=4; break;

            //case SDLK_e: bomb.SetBomno(false);dat_bom=false;break;
        }
    }
    else if (e.type==SDL_MOUSEBUTTONDOWN)
     {
         Bullet* p_amo=new Bullet();
         if(e.button.button==SDL_BUTTON_LEFT)
         {
             p_amo->setwh(WIDTHLASER,HEIGHTLASER);
             p_amo->LoadImg("laser.png",screen);
             p_amo->set_type(Bullet::LASER);
             p_amo->SetDir(Dir);
          // std::cout<<"da duoc";
         }
         else if (e.button.button==SDL_BUTTON_RIGHT)
         {
             p_amo->setwh(WIDTHSPHERE,HEIGHTSPHERE);
             p_amo->LoadImg("sphere.png",screen);
             p_amo->set_type(Bullet::SPHERE);
             p_amo->SetDir(Dir);
         }
        // p_amo->SetRect(this->rect_.x+this->rect_.w/5-5,this->rect_.y+this->rect_.h*0.25);

            p_amo->set_pos(x_pos_, y_pos_+this->rect_.h*0.25);



         if(p_amo->GetDir()==3) {
            p_amo->set_val_bullet(-10);
         }
         else {
            p_amo->set_val_bullet(10);
         }
         p_amo->set_is_move(true);
         p_amo_list.push_back(p_amo);
     }
}
void MainObject::SetClip()
{
    for(int i=0;i<=4;i++) {
        clip_right[i].x=i*Main_width;
        clip_right[i].y=0;
        clip_right[i].w=Main_width;
        clip_right[i].h=Main_height;
    }
    for(int j=0;j<=4;j++) {
        clip_left[j].x=j*Main_width;
        clip_left[j].y=Main_height;
        clip_left[j].w=Main_width;
        clip_left[j].h=Main_height;
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
        if(x_val_>0) {
            if(map_data.tile[y1][x2]!=1||map_data.tile[y2][x2]!=1) {
                x_pos_=x2*TILE_SIZE;
                x_pos_-=Main_width+1;
                x_val_=0;
            }

        }
        else if(x_val_<0) {
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
        if(y_val_>0) {
            if(map_data.tile[y2][x1]!=1||map_data.tile[y2][x2]!=1) {
                y_pos_=y2*TILE_SIZE;
                y_pos_-=(Main_height+1);
                y_val_=0;
            }
        }
        else if(y_val_<0) {
            if(map_data.tile[y1][x1]!=1||map_data.tile[y1][x2]!=1) {
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
