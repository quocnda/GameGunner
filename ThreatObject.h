#ifndef THREATOBJECT_H
#define THREATOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "BulletObject.h"

#define FRAME 32
#define TIME 1

//class MainObject;

class ThreatObject : public BaseObject
{
    public:
        ThreatObject();
        ~ThreatObject();

       /* enum GhostDirection
        {
            DIR_UP = 25,
            DIR_LEFT = 26,
            DIR_DOWN = 27,
            DIR_RIGHT = 28,
        };
        */
        bool LoadImg(std::string path,SDL_Renderer* screen);
        void SetClip();

        void set_x_val(const float& xVal) {x_val = xVal;}
        void set_y_val(const float& yVal) {y_val = yVal;}

        void set_x_pos(const float& xp) {x_pos = xp;}
        void set_y_pos(const float& yp) {y_pos = yp;}

        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}

        void SetMapXY(const int& mp_x, const int& mp_y)
        {map_x = mp_x; map_y = mp_y;}
        bool is_alive() {return is_alive_;}
        void Show(SDL_Renderer* screen);
       // bool is_alive() const {return isAlive;}
        void DoPlayer(Map& gMap);
        void CheckToMap(Map& gMap);
        bool CheckToBullet(MainObject& p);
        int GetDir() {return Dir;}

        void SetBullet(std::vector<Bullet*> amo_list) {p_amo_list=amo_list;}
       std::vector<Bullet*> GetBullet() {return p_amo_list;}
       void InitBullet (Bullet* p_bullet,SDL_Renderer* screen);
        void MakeBullet(SDL_Renderer* screen, const int x_limit,const int y_limit);
    private:
        int map_x;
        int map_y;

        float x_val;
        float y_val;
        float x_pos;
        float y_pos;

        int Dir;
        int status_;

        SDL_Rect clip_left[5];
        SDL_Rect clip_right[5];

        int frame_;
        int frame_1;

        int Threat_width;
        int Threat_height;

        bool is_alive_;


        std::vector<Bullet*> p_amo_list;
};

#endif // THREATOBJECT_H
