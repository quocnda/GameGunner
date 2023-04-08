


#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "Map.h"

#define WIDTHLASER 20

#define HEIGHTLASER 20

#define WIDTHSPHERE 35
#define HEIGHTSPHERE 35
#define FRAME 6


class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet() {free();}
    enum {
       NONE=0,
       LASER=1,
       SPHERE=2
    };

    int get_type() {return amo_type_;}
    void set_type(int type) {amo_type_=type;}
    bool get_is_move() {return is_move_;}
    void set_is_move(bool is_move) {is_move_=is_move;}
    void setwh(const int &width,const int &height) {rect_.w=width;rect_.h=height;}

    void set_val_bullet(const int & val) {x_val=val;}
    void set_val_bullet_y(const int v) {y_val=v;}
    void SetDir(int x) {Dir=x;}
    int  GetDir() {return Dir;}

    void SetMapXY(int x,int y) {map_x=x;map_y=y;}
    void Checktomap(Map& map_data);
    void Show1(SDL_Renderer* screen);


    void set_col_wall() {col_wall=0;}
    int get_col_wall() {return col_wall;}
    void HandleMove(const int& x_border, const int& y_border, Map& map_data,int x,int y);
    void set_pos(int x,int y) {x_pos=x;y_pos=y;}
    void Show(SDL_Renderer* des, int x, int y);

private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    bool is_move_;
    int amo_type_;

    int map_x;
    int map_y;

    int col_wall;

    bool is_daban;
    int Dir;
};

#endif
