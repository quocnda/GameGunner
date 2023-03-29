#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunc.h"
#include "BulletObject.h"

class BossObject:public BaseObject
{
public :
    bool LoadImg(std::string path,SDL_Renderer* screen);

private:
    float x_pos;
    float y_pos;

    int x_val;
    int y_val;

};

#endif // BOSS_OBJECT_H_
