#ifndef PLAY_POWER_H_
#define PLAY_POWER_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayPower : public BaseObject
{
public:
    PlayPower();
    ~PlayPower();
    void SetNum(int n) {number=n;}
    void Addpos(int x);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void Increase();
    void Decrease();
private:
    int number;
    std::vector<int> pos_list;
};
#endif // PLAY_POWER_H_
