


#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "Map.h"

#define WIDTHLASER 35
#define HEIGHTLASER 5
#define WIDTHSPHERE 10
#define HEIGHTSPHERE 10
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
    void handlemoveright(const int x_border,const int y_border);
    void moveleft(const int x_border,const int y_border,int m_x,int m_y);


    int get_type() {return amo_type_;}
    void set_type(int type) {amo_type_=type;}
    bool get_is_move() {return is_move_;}
    void set_is_move(bool is_move) {is_move_=is_move;}
    void setwh(const int &width,const int &height) {rect_.w=width;rect_.h=height;}
    void handlemoverighttoleft();
    void set_val_bullet(const int & val) {x_val=val;}
    void set_val_bullet_y(const int v) {y_val=v;}
    void SetDir(int x) {Dir=x;}
    int  GetDir() {return Dir;}


    void set_pos(int x,int y) {x_pos=x;y_pos=y;}
    void Show(SDL_Renderer* des, int x, int y);
    void HandleMove(const int& x_border, const int& y_border, Map& map_data);
    void HandleMove1(const int& x_border,const int& y_border);
private:
    int x_val;
    int y_val;

    float x_pos;
    float y_pos;

    bool is_move_;
    int amo_type_;



    bool is_daban;
    int Dir;
};

#endif
