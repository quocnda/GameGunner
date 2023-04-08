
#ifndef MAP_H_
#define MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"


#define MAX_TILES 10

class TileMap : public BaseObject
{
public:
    TileMap() {;}
    ~TileMap() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    void setGate(int i,int j) {game_map_.tile[i][j]=8;}
    Map getMap()const
    {
        return game_map_;
    };
    void SetMap(Map& map_data) {game_map_=map_data;};

private:
    Map game_map_;
    TileMap tile_map[MAX_TILES];
};
#endif // MAP_H_
