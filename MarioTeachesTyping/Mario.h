#ifndef MARIO_H
#define MARIO_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Mario : public BaseObj {

    public:

        // initialise Mario
        Mario();
        ~Mario();

        // load Mario image from file
        bool loadMario(SDL_Renderer* renderer, string path);

        // render Mario
        void renderMario(SDL_Renderer* renderer);

        // render Mario running
        void run(SDL_Renderer* renderer, double x, double y, int f);
        
        // render Mario standing
        void stand(SDL_Renderer* renderer, double x, double y, int f = 0);

        // render Mario jumping
        void jump(SDL_Renderer* renderer, double x, double y, int f);

        // get x condinate of Mario
        int getXPos();

        // get y condinate of Mario
        int getYPos();

        // set Mario status
        void setStatus(int status);

        // get Mario status
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

        // initialize clips of status
        SDL_Rect runClips[6];
        SDL_Rect jumpClips[11];
        SDL_Rect standClips[9];

        // initialize frame of clip
        int frame;

        // initialize status
        int status;


};

#endif