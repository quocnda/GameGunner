#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
//#include "ThreatObject.h"


class MainObject:public BaseObject
{
public:
   MainObject();
   ~MainObject() ;
   bool LoadImg(std::string path,SDL_Renderer* screen);
   void Show(SDL_Renderer* screen);
   void handle(SDL_Event &e,SDL_Renderer* screen);
   void SetClip();


    void DoPlayer (Map& map_data);
    void checktomap(Map& map_data);

    bool get_a_live() {return is_alive;}
    void set_alive(bool t) {is_alive=t;}

   void settocdo(int x) {toc_do=x;}
   int gettocdo() {return toc_do;}

   void Camera(Map& map_data);
   void SetmapXY(const int x,const int y) {map_x=x;map_y=y;}

   void Setamolist (std::vector<Bullet*> amo_list) {p_amo_list=amo_list;}
   std::vector<Bullet*>  Getamo() {return p_amo_list;}
   void RemoveBullet(const int &idx);
   void HandleBullet(SDL_Renderer* screen, Map& map_data);

   //void ChecktoBullet(ThreatObject& p_threat);


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

     bool da_ban;
     bool is_alive;
    int Dir;

     SDL_Rect clip_right[6];
     SDL_Rect clip_left[6];
     SDL_Rect clip_dungyen[6];
     SDL_Rect clip_bandanphai[6];
     SDL_Rect clip_bandantrai[6];

     int toc_do;

     int map_x;
     int map_y;

     std::vector<Bullet*> p_amo_list;
};
#endif // MAIN_OBJECT_H_
