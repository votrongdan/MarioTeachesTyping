#ifndef MARIO_H
#define MARIO_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Mario : public BaseObj {

    public:

        Mario();
        ~Mario();

        // load Mario image from file
        bool loadMario(SDL_Renderer* renderer, string path);

        // render Mario
        void renderMario(SDL_Renderer* renderer);

        void run(SDL_Renderer* renderer, double x, double y, int f);
        
        void stand(SDL_Renderer* renderer, double x, double y, int f = 0);

        void jump(SDL_Renderer* renderer, double x, double y, int f);

        int getXPos();

        int getYPos();

        void setStatus(int status);
        int getStatus();

    private:

        SDL_Texture* mario = BaseObj::getObj();

        // initialize position of Mario
        double xPos;
        double yPos;

        // initialize distance
        int xDistance;
        int yDistance;

        // initialize size of Mario frame
        int widthMario;
        int heightMario;

        SDL_Rect runClips[6];
        SDL_Rect jumpClips[11];
        SDL_Rect standClips[9];

        int frame;

        int count;

        int status;


};

#endif