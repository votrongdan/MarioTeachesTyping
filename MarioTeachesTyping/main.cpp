#include "CommonFunc.h"
#include "BaseObj.h"
#include "Road.h"
#include "Mario.h"
#include "Character.h"
#include "Timer.h"
#include "Hand.h"

BaseObj gBackground;

BaseObj gameTimeTexture;

BaseObj typedTexture;

BaseObj errorTexture;

BaseObj wordPerMinute;

BaseObj temp;

Road road;

RightHand rightHand;

LeftHand leftHand;

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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
	gFont = TTF_OpenFont( "media/font/roboto.ttf", 48 );
	if( gFont == NULL ) {
		printf( "Failed to load roboto font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	gameFont = TTF_OpenFont( "media/font/roboto.ttf", 32 );
	if( gameFont == NULL ) {
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

	if (!rightHand.loadRightHand(gRenderer, "media/image/rightHand.png")) {
		printf( "Failed to load right hand' texture image!\n" );
		success = false;
	}

	if (!leftHand.loadLeftHand(gRenderer, "media/image/leftHand.png")) {
		printf( "Failed to load left hand' texture image!\n" );
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
	gameTimeTexture.free();
	typedTexture.free();
	errorTexture.free();
	rightHand.free();
	leftHand.free();

	//Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
	gameFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();

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

	int xRoad = 0;

	// initialize flag to stop
	int stop = 240;

	// set text color
	SDL_Color textColor = { 255, 255, 255, 255 };

	vector<Character> arrChar;

	// create five character
	for (int i = 0; i < 4; i++) {
		c.createChar();
		c.createThreat();

		arrChar.push_back(c);

	}

	Character mainChar = arrChar[0];

    // main loop flag
    bool quit = false;

    // event handler
    SDL_Event e;

	//The frames per second cap timer
	Timer capTimer;

	// the time of game
	Timer gameTimer;

	gameTimer.start();

	// count true pressing
	int typed = 0;

	// count false pressing
	int error = 0;

	// count threat
	int count = 4;

	// end game flag
	bool endGame = false;

	double velCam = 0;

	int wpm = 0;

	// the area camera
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // while app is running
    while (!quit) {

		capTimer.start();

        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if ( e.type == SDL_QUIT ) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == mainChar.getChar()) {
					mainChar.setDead(true);
					typed++;
					if (mainChar.getThreat() == 1) {
						gMario.setStatus(2);
					}
				} 
				else {
					error++;
				}

			}

        } 

		// check character 
		if (mainChar.isDead() == true) {

			arrChar[0].free();
			arrChar.erase(arrChar.begin());
			stop += 240;

		}

		// calculate wpm
		wpm = 0;

		// add character
		while (arrChar.size() < 4 && count < MAX_THREAT) {

			c.createChar();
			c.createThreat();

			arrChar.push_back(c);

			count++;

		}

		if (!temp.loadFromRenderedText(gRenderer, gameFont, "Hello, World!", textColor)) {
			printf("Unable to render temp texture!\n");
			return -1;
		}	

		if (!errorTexture.loadFromRenderedText(gRenderer, gameFont, "Error: " + to_string(error), textColor)) {
			printf("Unable to render error texture!\n");
			return -1;
		}

		if (!typedTexture.loadFromRenderedText(gRenderer, gameFont, "Typed: " + to_string(typed), textColor)) {
			printf("Unable to render typed texture!\n");
			return -1;
		}

		if (!wordPerMinute.loadFromRenderedText(gRenderer, gameFont, "WPM: " + to_string(wpm), textColor)) {
			printf("Unable to render wpm texture!\n");
			return -1;
		}

		if (!gameTimeTexture.loadFromRenderedText(gRenderer, gameFont, gameTimer.convert(), textColor)) {
			printf("Unable to render game time texture!\n");
			return -1;
		}

		// load character texture
		switch (typed) {
			case (MAX_THREAT - 3):
				for (int i = 0; i < 3; i++) {
					string s(1, arrChar[i].getChar());
					if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
						printf( "Unable to render character texture!\n" );
						return -1;
					}

				}
				break;
			case (MAX_THREAT - 2): 

				for (int i = 0; i < 2; i++) {
					string s(1, arrChar[i].getChar());
					if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
						printf( "Unable to render character texture!\n" );
						return -1;
					}

				}
				break;
			case (MAX_THREAT - 1):

				for (int i = 0; i < 1; i++) {
					string s(1, arrChar[i].getChar());
					if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
						printf( "Unable to render character texture!\n" );
						return -1;
					}

				}
				break;
			case MAX_THREAT:
				break;
			
			default:

				for (int i = 0; i < 4; i++) {
					string s(1, arrChar[i].getChar());
					if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
						printf( "Unable to render character texture!\n" );
						return -1;
					}

				} 
				break;
		}
		

		mainChar = arrChar[0];

		// if (gMario.getXPos() - camera.x > 96 && (camera.x + SCREEN_WIDTH) < (MAX_THREAT + 1) * 240) {
		// 	camera.x += 10;
		// }

		// if ((camera.x + SCREEN_WIDTH) < (MAX_THREAT + 1) * 240) {
		// 	if (gMario.getXPos() - camera.x <= 96) {
		// 		velCam = 0;
		// 	}
		// 	else if (gMario.getXPos() - camera.x > 96 && gMario.getXPos() - camera.x <= (24 * 5)) {
		// 		velCam = 1;
		// 	} 
		// 	else if (gMario.getXPos() - camera.x > (24 * 5) && gMario.getXPos() - camera.x <= (24 * 9)) {
		// 		velCam = 2;
		// 	} 
		// 	else if (gMario.getXPos() - camera.x > (24 * 9) && gMario.getXPos() - camera.x <= (24 * 13)) {
		// 		velCam = 4;
		// 	} 
		// 	else if (gMario.getXPos() -camera.x > (24 * 13)) {
		// 		velCam = 10;
		// 	} 

		// } else {
		// 	velCam = 0;
		// }

		

		if ((camera.x + SCREEN_WIDTH) < (MAX_THREAT + 1) * 240) {
			camera.x += velCam;
		}

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

		// render background
        gBackground.render(0, 0, gRenderer);

		if (xRoad + SCREEN_WIDTH <= camera.x) {
			xRoad += SCREEN_WIDTH;
		}
		
		// render road
		road.renderRoad(gRenderer, xRoad - camera.x);

		switch (typed) {
			case (MAX_THREAT - 3):

				// render threat and character
				for (int i = 0; i < 3; i++) {
					int xThreat = stop + i * 240 - camera.x;
					if (arrChar[i].getThreat() == 0) {
						gTurtle.renderTurtle(gRenderer, xThreat);


						arrChar[i].render(xThreat + 34, gTurtle.getYPos() + 29, gRenderer);
					} else {
						gTile.renderTile(gRenderer, xThreat);
						arrChar[i].render(xThreat + 34, gTile.getYPos() + 21, gRenderer);
					}
				}
				break;
			case (MAX_THREAT - 2): 

				// render threat and character
				for (int i = 0; i < 2; i++) {
					int xThreat = stop + i * 240 - camera.x;
					if (arrChar[i].getThreat() == 0) {
						gTurtle.renderTurtle(gRenderer, xThreat);


						arrChar[i].render(xThreat + 34, gTurtle.getYPos() + 29, gRenderer);
					} else {
						gTile.renderTile(gRenderer, xThreat);
						arrChar[i].render(xThreat + 34, gTile.getYPos() + 21, gRenderer);
					}
				}
				break;
			case (MAX_THREAT - 1):

				// render threat and character
				for (int i = 0; i < 1; i++) {
					int xThreat = stop + i * 240 - camera.x;
					if (arrChar[i].getThreat() == 0) {
						gTurtle.renderTurtle(gRenderer, xThreat);


						arrChar[i].render(xThreat + 34, gTurtle.getYPos() + 29, gRenderer);
					} else {
						gTile.renderTile(gRenderer, xThreat);
						arrChar[i].render(xThreat + 34, gTile.getYPos() + 21, gRenderer);
					}
				}
				break;
			case MAX_THREAT:
				endGame = true;
				break;
			
			default:

				// render threat and character
				for (int i = 0; i < 4; i++) {
					int xThreat = stop + i * 240 - camera.x;
					if (arrChar[i].getThreat() == 0) {
						gTurtle.renderTurtle(gRenderer, xThreat);


						arrChar[i].render(xThreat + 34, gTurtle.getYPos() + 29, gRenderer);
					} else {
						gTile.renderTile(gRenderer, xThreat);
						arrChar[i].render(xThreat + 34, gTile.getYPos() + 21, gRenderer);
					}
				}
				break;
		}
		gameTimeTexture.render(40, 560, gRenderer);

		typedTexture.render(40, 640, gRenderer);

		errorTexture.render(950, 640, gRenderer);

		wordPerMinute.render(950, 560, gRenderer);

		rightHand.renderRightHand(gRenderer, mainChar.getChar());
		leftHand.renderLeftHand(gRenderer, mainChar.getChar());

		// render main character
		mainChar.render(562, 562, gRenderer);

		// if (gMario.getXPos() < stop - 70) {
		// 	gMario.run(gRenderer, camera.x);
		// } 
		// // else if (gMario.getXPos() == stop - 70 && mainChar.getThreat() == 1) {
		// // 	gMario.jump(gRenderer);
		// // }
		// else if (gMario.getXPos() >= stop - 70) {
		// 	gMario.stand(gRenderer, camera.x);
		// }

		if (gMario.getXPos() < stop - 70 && gMario.getStatus() != 2) {
			gMario.setStatus(1);
			velCam += 0.15;
		} else if (gMario.getXPos() >= stop - 70) {
			gMario.setStatus(0);
			velCam -= 0.05;
		}

		if (velCam <= 2) {
			velCam = 2;
		} 

		if (gMario.getXPos() - camera.x < 192) {
			velCam = 1;
		}

		if (velCam >= 10) {
			velCam = 10;
		}

		if (gMario.getXPos() - camera.x < 96) {
			velCam = 0;
		}

		// cout << velCam << " ";

		gMario.run(gRenderer, camera.x, stop);

        // update screen
        SDL_RenderPresent( gRenderer );

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICKS_PER_FRAME ) {
			//Wait remaining time
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
		}

    }

	//Free resources and close SDL
	close();

	return 0;
}