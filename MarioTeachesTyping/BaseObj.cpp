
#include "BaseObj.h"
#include "CommonFunc.h"

BaseObj::BaseObj () {

    // initialize obj
    obj = NULL;
    width = 0;
    height = 0;

}

BaseObj::~BaseObj () {

    free();

}

bool BaseObj::loadMedia(SDL_Renderer* renderer, string path ) {

	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} else {
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		} else {
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	obj = newTexture;
	return obj != NULL;

}

void BaseObj::free () {

	//Free texture if it exists
	if ( obj != NULL ) {
		SDL_DestroyTexture( obj );
		obj = NULL;
		width = 0;
		height = 0;
	}

}

void BaseObj::render ( int x, int y, SDL_Renderer* renderer) {

	//Set rendering space and render to screen
	SDL_Rect rect = { x, y, width, height };
	SDL_RenderCopy( renderer, obj, NULL, &rect );
}


int BaseObj::getWidth () {

	return width;
}


int BaseObj::getHeight () {

	return height;
}
