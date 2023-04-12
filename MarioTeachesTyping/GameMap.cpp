#include "GameMap.h"

bool GameMap::loadMap(string path) {

    // initialize success
    bool success = true;

    // open file
    ifstream inFile;
    inFile.open(path.c_str(), ios::in);

    if (!inFile) {

        printf("Failed to open file! %s\n");
        success = false;

    }
    
    map.maxX = 0;
    map.maxY = 0;

    // read file
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {

            inFile >> map.tiles[i][j];
            int val = map.tiles[i][j];
            if (val > 0) {

                if (j > maxX) map.maxX = j;
                if (i > maxY) map.maxy = i;

            }

        }
    }

    // close file
    inFile.close();

    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxy = (map.maxy + 1) * TILE_SIZE;

    map.x = 0;
    map.y = 0;

    // save path
    map.path = path;

    return success;

}

bool GameMap::loadTileMat(SDL_Renderer* renderer, string path) {

    // initialize success flag
    bool success = true;

    // load tile mat
    if (!tileMat.loadMedia(renderer, path.c_str())) {

        printf("Failed to load tile mat! %s\n", SDL_GetError(), IMG_GetError);
        success = false;

    }

    return success;

}

