#ifndef CHARACTER_H
#define CHARACTER_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Character {

    public:

        Character();

        void createChar();

        char getChar();

        void renderCharacter(int order);

    private:

        char c;
        
        int order;

        bool isExist;


};

class Turtle : public BaseObj {

    public:

        Turtle();
        ~Turtle();

        void renderTurtle(SDL_Renderer* renderer, int x);
    
    private:

        const int yPos = 384;


};

class Tile : public BaseObj {

    public:

        Tile();
        ~Tile();

        void renderTile(SDL_Renderer* renderer, int x);
    
    private:

        const int yPos = 184;


};

#endif