#ifndef BASE_OBJ_H
#define BASE_OBJ_H

#include "CommonFunc.h"

class BaseObj {

    public: 

        // initializes variable
        BaseObj();

        // deallocates memory
        ~BaseObj();

        // load media from file
        bool loadFromFile(SDL_Renderer* renderer, string path);

        // render obj
        void render(int x, int y, SDL_Renderer* renderer);

        // deallocates obj
        void free();

        // get obj dimention
        int getWidth();
        int getHeight();

    private:

        SDL_Texture* obj;
        
        int width;
        int height;

};

#endif