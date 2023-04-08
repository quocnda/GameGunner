
#include "BulletObject.h"

Bullet::Bullet()
{
    Dir=0;
    x_val=-3;
    y_val=0;
    col_wall=0;
   // rect_.x=0;
   // rect_.y=0;
    x_pos=rect_.x;
    y_pos=rect_.y;
    is_move_=false;
    amo_type_=NONE;
    is_daban=false;
    map_x=0;
    map_y=0;
}


void Bullet::HandleMove(const int& x_border, const int& y_border, Map& map_data,int x,int y)
{


    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    //check horizontal
    int height_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    //o thu bao nhieu
    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + FRAME -1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min -1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y){
        if(x_val > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if(val1 ==0 || val2 ==0)
            {
                is_move_ = false;
            }
        }
        else if(x_val < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(val1 ==0 || val2 ==0)
            {
               is_move_ = false;
            }

        }
    }

    int width_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min - 1) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + FRAME - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y){
        if(y_val > 0)   //main object dang di chuyen ve xuong
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1!=1) || val2!=1){
                    is_move_=false;
            }
        }
        else if(y_val < 0)   //main object dang di chuyen ve ben phai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1!=1 || val2!=1){
                   is_move_=false;
            }
        }
    }



    x_pos += x_val;
    y_pos += y_val;

    if(rect_.y > y_border) {is_move_ = false;}
    else if(rect_.y < 0)  {is_move_ = false;}
    if(rect_.x > x_border)  {is_move_ = false;}
    else if(rect_.x < 0)  {is_move_ = false;}


    if(abs(x_pos-x)+abs(y_pos-y)>=1500) {col_wall++;is_move_=false;}

}

void Bullet::Show(SDL_Renderer* des, int x, int y)
{

    rect_.x = x_pos - x;
    rect_.y = y_pos - y;

    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);

}

void Bullet::Checktomap(Map& map_data)
{



    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    //check horizontal
    int height_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    //o thu bao nhieu
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
                is_move_=false;
            }
        }
        else if(x_val < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if((val1!=1) || (val2!=1)){
                  is_move_=false;
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
                   is_move_=false;
            }
        }
        else if(y_val < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1!=1 || val2!=1){
                   is_move_=false;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;
     if(x_pos<0) {
        x_pos=0;
    }

}
void Bullet::Show1(SDL_Renderer* screen)
{
    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(screen, p_object_, NULL, &renderQuad);
}
