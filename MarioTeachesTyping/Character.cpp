#include "Character.h"

Character::Character() {

    c = '\0';

    threat = -1;

    xPos = 0;

}

void Character::createChar() {

    c = ('a' + rand() % 26);

}

char Character::getChar() {

    return c;

}

void Character::createThreat() {

    threat = rand() % 2;

}

int Character::getThreat() {

    return threat;

}



void Character::renderCharacter(SDL_Renderer* renderer) {

    // if (threat == 0) {
    //     gTurtle.renderTurtle(renderer, xPos);
    // } else {
    //     gTile.renderTile(renderer, xPos);
    // }

    

}

Turtle::Turtle() {


}

Turtle::~Turtle() {

    BaseObj::free();

}

void Turtle::renderTurtle(SDL_Renderer* renderer, int x) {

    BaseObj::render(x, yPos, renderer);

}

Tile::Tile() {

}

Tile::~Tile() {

    BaseObj::free();

}

void Tile::renderTile(SDL_Renderer* renderer, int x) {

    BaseObj::render(x, yPos, renderer);

}

