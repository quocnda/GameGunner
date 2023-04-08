#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunc.h"
#include "BulletObject.h"
#include "Map.h"
#include "MainObject.h"


class BossObject:public BaseObject
{
public :
    BossObject();
    ~BossObject();
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetMapXY(int x,int y) {map_x=x;map_y=y;}
    void SetClip();

    void Set_pos(int x,int y) {x_pos=x;y_pos=y;}

    void set_alive(bool t) {is_alive=t;}
    bool get_alive() {return is_alive;}

    bool CheckToBullet(MainObject &p);

    void Set_p_bullet_du_phong(std::vector<Bullet*> bullet_) {p_bullet_du_phong=bullet_;}
    void MakeBullet(Map& map_data,SDL_Renderer* screen);
    void Set_amo_list(std::vector<Bullet*> p_bullet_list_) {p_bullet_list=p_bullet_list_;}
    void Reset_amo_list() {p_bullet_list=p_bullet_du_phong;}

private:
    float x_pos;
    float y_pos;

    int x_val;
    int y_val;

    int map_x;
    int map_y;

    int frame;

    int count_bullet_col_wall;

    int bi_ban;
    int Boss_width;
    int Boss_height;
    SDL_Rect clip_boss[24];
    bool is_alive;
    Audio A;

    std::vector<Bullet*> p_bullet_list;
    std::vector<Bullet*> p_bullet_du_phong;
};

#endif // BOSS_OBJECT_H_
