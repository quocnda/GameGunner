#ifndef BULLET_THREAT_H_
#define BULLET_THREAT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"

#define WIDTHSPHERE 10
#define HEIGHTSPHERE 10
#define FRAME 6

class BulletThreat : public BaseObject
{
public :
    BulletThreat();
    ~BulletThreat();
    bool get_is_move() {return is_move_;}
    void set_is_move(bool is_move) {is_move_=is_move;}
    void setwh(const int &width,const int &height) {rect_.w=width;rect_.h=height;}

    void set_val_bullet(const int & val) {x_val=val;}
    void set_val_bullet_y(const int v) {y_val=v;}
    void SetDir(int x) {Dir=x;}
    int  GetDir() {return Dir;}


    void set_pos(int x,int y) {x_pos=x;y_pos=y;}
    void Show(SDL_Renderer* des, int x, int y);
    void HandleMove(const int& x_border, const int& y_border, Map& map_data);
private:
    int Dir;
    int x_val;
    int y_val;

    bool is_move_;

    float x_pos;
    float y_pos;


};
#endif // BULLET_THREAT_H_
