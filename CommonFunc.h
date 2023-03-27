#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <SDL_ttf.h>
#include<SDL_mixer.h>


static SDL_Window* gWindow=NULL;
static SDL_Renderer* gScreen=NULL;
static SDL_Texture* gText=NULL;
static SDL_Event gevent;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
//const int toc_do=5;

typedef struct Input{
    int left;
    int right;
    int up;
    int down;
};

#define TILE_SIZE 64
#define NUM_THREAT 25
#define MAP_X 31

#define MAP_Y 25



typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAP_Y][MAP_X];
    char *file_name;
};

static bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
#endif // COMMON_FUNC_H_
