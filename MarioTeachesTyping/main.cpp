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
			}
		}
	}

	return success;
}

bool loadMedia () {

    bool success = true;

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

	vector<Character> arrChar;

	for (int i = 0; i < 5; i++) {
		Character c;
		c.createChar();
		c.createThreat();
		arrChar.push_back(c);
	}

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
				
				// switch (e.key.keysym.sym) {

				// 	case SDLK_UP:
				// 		gMario.setStatus(1);
				// 		frame = 0;
				// 		check1 = true;
				// 		break;
				// 	case SDLK_DOWN:
				// 		gMario.setStatus(2);
				// 		break;
				// }


			}
        } 

        //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

		// render background
        gBackground.render(0, 0, gRenderer);

		// render road
		road.renderRoad(gRenderer);

		for (int i = 0; i < 5; i++) {
			if (arrChar[i].getThreat() == 0) {
				gTurtle.renderTurtle(gRenderer, stop + i * 240);
			} else {
				gTile.renderTile(gRenderer, stop + i * 240);
			}
		}

		// gMario.run(gRenderer, xPos, yPos, frame % 6);
		// xPos += 1;

		// if (xPos > 240) {
		// 	if (check1 == false) {
		// 		xPos = 240;
		// 	}
		// }

		// frame++;
		
		// if (gMario.getStatus() == 1 && frame == 36) {
		// 	frame == 0;
		// }

        // update screen
        SDL_RenderPresent( gRenderer );


    }

	//Free resources and close SDL
	close();

	return 0;
}