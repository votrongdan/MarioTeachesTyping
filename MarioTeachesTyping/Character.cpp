#include "Character.h"

Character::Character() {

    c = '\0';

    threat = -1;

    dead = false;

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

void Character::setDead(bool isTrue) {

    dead = isTrue;

}

bool Character::isDead() {

    return dead;

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

