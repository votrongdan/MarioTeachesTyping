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

void GameMap::drawMap(SDL_Renderer* renderer, string path) {

    // initialize area to render tile mat
    int beginX = 0;
    int endX = 0;

    int beginY = 0;
    int endY = 0;

    beginX = (map.x % TILE_SIZE) * -1;
    endX = beginX + TILE_SIZE + (beginX == 0 ? 0 : TILE_SIZE);

    beginY = (map.y % TILE_SIZE) * -1;
    endY = beginY + TILE_SIZE + (beginY == 0 ? 0 : TILE_SIZE);

    // initialize location to render tile mat
    int mapX = 0;
    int mapY = 0;

    mapX = map.x / TILE_SIZE;
    mapY = map.y / TILE_SIZE;

    // draw tile mat
    for (int i = beginY; i < endY; i += TILE_SIZE) {

        mapX = map.x / TILE_SIZE;
        for (int j = beginX; j < endX; j += TILE_SIZE) {

            int val = map.tiles[mapY][mapX];
            if (val > 0) {

                tileMat.render(j, i, renderer);

            }
            mapX++;

        }
        mapY++;

    }

}

