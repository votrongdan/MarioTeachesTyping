#include "CommonFunc.h"
#include "BaseObj.h"
#include "Road.h"
#include "Mario.h"
#include "Character.h"

BaseObj gBackground;

Road road;

Mario gMario;

Turtle gTurtle;

Tile gTile;

Character c;

bool init() {

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Set texture filtering to linear
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {

			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Mario teaches typing", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN );
		if ( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 ) {
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia () {

    bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "roboto.ttf", 48 );
	if( gFont == NULL )
	{
		printf( "Failed to load roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    if ( !gBackground.loadMedia(gRenderer, "media/image/background.png" ) ) {
		printf( "Failed to load background' texture image!\n" );
		success = false;
	}

    if ( !road.loadGrass(gRenderer, "media/image/grass.png" ) ) {
		printf( "Failed to load grass' texture image!\n" );
		success = false;
	}

    if ( !gMario.loadMario(gRenderer, "media/image/mario.png" ) ) {
		printf( "Failed to load Mario' texture image!\n" );
		success = false;
	}

	if (!gTurtle.loadMedia(gRenderer, "media/image/turtle.png" ) ) {
		printf( "Failed to load turtle' texture image!\n" );
		success = false;
	}

	if (!gTile.loadMedia(gRenderer, "media/image/tile.png" ) ) {
		printf( "Failed to load tile' texture image!\n" );
		success = false;
	}

    return success;

}

void close () {

    gBackground.free();
	road.free();
	gMario.free();
	gTurtle.free();
	gTile.free();
	c.free();

	//Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}



int main( int argc, char* args[] ) {

    // start up SDL
    if (!init()) {
        printf( "Failed to initialize! %s\n" );
        return -1;
    }

    if (!loadMedia()) {
        printf( "Failed to load media! %s\n" );
        return -1;
    }

	int frame = 0;

	// initialize flag to stop
	int stop = 240;

	// set text color
	SDL_Color textColor = { 255, 255, 255, 255 };

	vector<Character> arrChar;

	for (int i = 0; i < 5; i++) {
		c.createChar();
		c.createThreat();

		arrChar.push_back(c);

	}

	for (int i = 0; i < 5; i++) {
		string s(1, arrChar[i].getChar());
		if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
			printf( "Unable to render character texture!\n" );
			return -1;
		}
	}


	Character mainChar = arrChar[0];;

    // main loop flag
    bool quit = false;

    // event handler
    SDL_Event e;

    // while app is running
    while (!quit) {

        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if ( e.type == SDL_QUIT ) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == mainChar.getChar()) {
					arrChar[0].free();
					arrChar.erase(arrChar.begin());
					stop += 240;
				}

			}
        } 

		if (arrChar.size() < 5) {

			c.createChar();
			c.createThreat();

			arrChar.push_back(c);

		}

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

		for (int i = 0; i < 5; i++) {
			string s(1, arrChar[i].getChar());
			if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
				printf( "Unable to render character texture!\n" );
				return -1;
			}
		}

		mainChar = arrChar[0];

		// render background
        gBackground.render(0, 0, gRenderer);

		// render road
		road.renderRoad(gRenderer);

		for (int i = 0; i < 5; i++) {
			int xThreat = stop + i * 240;
			if (arrChar[i].getThreat() == 0) {
				gTurtle.renderTurtle(gRenderer, xThreat);
				arrChar[i].render(xThreat + 34, gTurtle.getYPos() + 29, gRenderer);
			} else {
				gTile.renderTile(gRenderer, xThreat);
				arrChar[i].render(xThreat + 34, gTile.getYPos() + 21, gRenderer);
			}
		}

		mainChar.render(576, 570, gRenderer);


        // update screen
        SDL_RenderPresent( gRenderer );


    }

	//Free resources and close SDL
	close();

	return 0;
}