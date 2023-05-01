#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <ostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <SDL_ttf.h>
#include<SDL_mixer.h>


static SDL_Window* gWindow=NULL;
static SDL_Renderer* gScreen=NULL;
static SDL_Texture* gText=NULL;
static SDL_Event gevent;
static SDL_Rect menu_pos[3];


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
//const int toc_do=5;
const float dx[16]={-1,0,1,1,1,0,-1,-1,-2,0,2,2,2,0,-2,-2};
const float dy[16]={-1,-1,-1,0,1,1,1,0,-2,-2,-2,0,2,2,2,0};
typedef struct Input{
    int left;
    int right;
    int up;
    int down;
};

const int TILE_SIZE=64;

#define MAP_X 42
#define MAP_Y 29

#define BOSS_POS_X 448
#define BOSS_POS_Y 704

#define BOSS_POS_X_1 1728
#define BOSS_POS_Y_1 896

#define BOSS_POS_X_2 1728
#define BOSS_POS_Y_2 1536

#define NUM_RASENGAN 20
#define NUM_SHURIKEN 20

#define GAME_MAX_LEVEL 1

#define TIME_ 500

#define NUM_BOSS_DIE 0
#define NUM_THREAT_DIE 0

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAP_Y][MAP_X];
    char *file_name;
};
static void SetPosMenu()
{
    menu_pos[0].x=SCREEN_WIDTH*0.2;
    menu_pos[0].y=SCREEN_HEIGHT*0.5;

    menu_pos[1].x=SCREEN_WIDTH*0.2;
    menu_pos[1].y=SCREEN_HEIGHT*0.5+70;

    menu_pos[2].x=SCREEN_WIDTH*0.2;
    menu_pos[2].y=SCREEN_HEIGHT*0.5+140;
}
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

static bool check_mouse(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}
#endif // COMMON_FUNC_H_
