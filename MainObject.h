#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "Audio.h"


class MainObject:public BaseObject
{
public:
   MainObject();
   ~MainObject() ;
   bool LoadImg(std::string path,SDL_Renderer* screen);
   void Show(SDL_Renderer* screen);
   void handle(SDL_Event &e,SDL_Renderer* screen);
   void SetClip();

   void Set_sound_die() {A.playSound(6);}

    void DoPlayer (Map& map_data);
    void checktomap(Map& map_data);

    bool get_a_live() {return is_alive;}
    void set_alive(bool t) {is_alive=t;}

   void settocdo(int x) {toc_do=x;}
   int gettocdo() {return toc_do;}
   void set_rasengan(int x) {so_rasengan=x;}
   void set_shuriken(int x) {so_shuriken=x;}

   int get_damage_rasengan() {return damage_rasengan;}
   int get_damage_shuriken() {return damage_shuriken;}
   int get_sorasengan() {return so_rasengan;}
   int get_soshuriken() {return so_shuriken;}

   void Camera(Map& map_data);
   void SetmapXY(const int x,const int y) {map_x=x;map_y=y;}

   void Setamolist (std::vector<Bullet*> amo_list) {p_amo_list=amo_list;}
   std::vector<Bullet*>  Getamo() {return p_amo_list;}
   void RemoveBullet(const int &idx);
   void HandleBullet(SDL_Renderer* screen, Map& map_data);

   void Set_blood_main(int x) {blood_main=x;}
   int Get_blood_main() {return blood_main;}


   bool ban_rasengan_() {return ban_rasengan;}
   bool ban_shuriken_() {return ban_shuriken;}
   bool is_move_() {return is_move;}
   void set_ban_rasengan(bool t) {ban_rasengan=t;}
   void set_ban_shuriken(bool t) {ban_shuriken=t;}
   void set_is_move(bool t) {is_move=t;}
   bool is_win_() {return is_win;}

   void set_x_pos(int x) {x_pos_=x;}
   void set_y_pos(int y) {y_pos_=y;}

   void set_x_val(int x) {x_val_=x;}
   void set_y_val(int y) {y_val_=y;}

   void set_input_type(int x) {input_type.down=0;input_type.up=0;input_type.left=0;input_type.right=0;}

   void set_is_win(bool t ) {is_win=t;}

   int GetDir() {return Dir;}
private:
     float x_val_;
     float y_val_;

     float x_pos_;
     float y_pos_;

     int Main_width;
     int Main_height;


     Input input_type;
     int frame_;//left
     int frame_1;//right
     int frame_0;//dungyen
     int frame_bantrai;
     int frame_banphai;
     int status_;

     Audio A;
     bool da_ban;
     bool is_move;
     bool is_alive;
     bool is_win;

    int Dir;

    int damage_rasengan;
    int damage_shuriken;

    bool ban_shuriken;
    bool ban_rasengan;

     int so_rasengan;
     int so_shuriken;

     SDL_Rect clip_right[6];
     SDL_Rect clip_left[6];
     SDL_Rect clip_dungyen[6];
     SDL_Rect clip_bandanphai[6];
     SDL_Rect clip_bandantrai[6];
     SDL_Rect clip_move_up[6];
     SDL_Rect clip_move_down[6];
     int frame_up;
     int frame_down;

     int toc_do;

     int blood_main;
     int map_x;
     int map_y;

     std::vector<Bullet*> p_amo_list;
};
#endif // MAIN_OBJECT_H_
