#include "CommonFunc.h"
#include "BaseObj.h"
#include "Road.h"
#include "Mario.h"

BaseObj gBackground;

Road road;

Mario gMario;

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

    return success;

}

void close () {

    gBackground.free();
	road.free();

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

	double xPos = gMario.getXPos();
	double yPos = gMario.getYPos();

	int frame = 0;

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
				gMario.setStatus(1);
			}
        } 

        //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

		// render background
        gBackground.render(0, 0, gRenderer);

		// render road
		road.renderRoad(gRenderer);

		if (gMario.getStatus() == 0) {

			gMario.stand(gRenderer, xPos, yPos);

		} else if (gMario.getStatus() == 1 && frame < 6) {

			gMario.run(gRenderer, xPos, yPos, frame);
			frame++;
			xPos += 40;

		} else if (gMario.getStatus() == 1 && frame == 6) {

			gMario.setStatus(0);
			frame = 0;

		}

        // update screen
        SDL_RenderPresent( gRenderer );


    }

	//Free resources and close SDL
	close();

	return 0;
}