#ifndef CHARACTER_H
#define CHARACTER_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Character : public BaseObj {

    public:

        Character();

        // random a character
        void createChar();

        // get character
        char getChar();
        
        // random a threat
        void createThreat();

        // get Threat
        int getThreat();

    private:

        // initialize character
        char c;
        
        // initialize threat
        int threat;

};

class Turtle : public BaseObj {

    public:

        Turtle();
        ~Turtle();

        void renderTurtle(SDL_Renderer* renderer, int x);

        int getYPos() {return yPos;}
    
    private:

        const int yPos = 384;

};

class Tile : public BaseObj {

    public:

        Tile();
        ~Tile();

        void renderTile(SDL_Renderer* renderer, int x);

        int getYPos() {return yPos;}
    
    private:

        const int yPos = 184;

};

#endif