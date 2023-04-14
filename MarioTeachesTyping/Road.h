#ifndef ROAD_H
#define ROAD_H

#include "CommonFunc.h"
#include "BaseObj.h"

class GrassBlock : public BaseObj {

    public: 

        GrassBlock() {;}
        ~GrassBlock() {;}


};

class Road {

    public:

        Road() {;}
        ~Road();

        // load grass block from file
        bool loadGrass (SDL_Renderer* renderer, string path);

        // render road
        void renderRoad (SDL_Renderer* renderer);

        // free texture if it exist
        void free();

    private:
        
        // initialize grass block
        BaseObj gGrass;

};


#endif