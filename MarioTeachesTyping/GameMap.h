#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObj.h"

class TileMat :: public BaseObj {

    public:
        
        TileMat() {;}
        ~TileMat() {;}

};

class GameMap {

    public:

        GameMap() {;}
        ~GameMap() {;}

        // load map from file
        bool loadMap(string path);

        // load tile mat image
        bool loadTileMat(SDL_renderer* renderer);

        // draw tile on map
        void drawMap(SDL_renderer* renderer, string path);

    private:

        // initialize map
        Map map;

        // initialize tile mat
        TileMat tileMat;

        // path to file
        string path;

};

#endif