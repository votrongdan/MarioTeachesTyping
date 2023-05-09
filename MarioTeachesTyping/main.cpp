#include "CommonFunc.h"
#include "BaseObj.h"
#include "Road.h"
#include "Mario.h"
#include "Character.h"
#include "Timer.h"
#include "Hand.h"
#include "Button.h"

BaseObj gBackground;

BaseObj gameTimeTexture;
BaseObj typedTexture;
BaseObj errorTexture;
BaseObj wordPerMinute;

BaseObj menu;
BaseObj endGameTexture;

BaseObj temp;

Road road;

RightHand rightHand;
LeftHand leftHand;

Mario gMario;

Turtle gTurtle;
Tile gTile;

Character c;

Mix_Chunk *gJump = NULL;
Mix_Chunk *gBlockhit = NULL;
Mix_Chunk *gCoin = NULL;

Button exitButton;
Button playButton;
Button nextButton;
Button menuButton;

enum {
	PLAY = 1,
	END = 2,
	MENU = 0
};

bool init() {

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
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

                 //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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

    if ( !endGameTexture.loadMedia(gRenderer, "media/image/endGame.png" ) ) {
		printf( "Failed to load end game' texture image!\n" );
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

	if (!exitButton.loadButton(gRenderer, "media/image/exitButton.png")) {
		printf( "Failed to load exit button texture image!\n " );
		success = false;
	}

	if (!playButton.loadButton(gRenderer, "media/image/playButton.png")) {
		printf( "Failed to load play button texture image!\n " );
		success = false;
	}

	if (!nextButton.loadButton(gRenderer, "media/image/nextButton.png")) {
		printf( "Failed to load next button texture image!\n " );
		success = false;
	}

	if (!menuButton.loadButton(gRenderer, "media/image/menuButton.png")) {
		printf( "Failed to load menu button texture image!\n " );
		success = false;
	}

	if (!menu.loadMedia(gRenderer, "media/image/menuScreen.png")) {
		printf( "Failed to load menu texture image!\n " );
		success = false;
	}

    //Load sound effects
    gJump = Mix_LoadWAV( "media/sound/jump.wav" );
    if( gJump == NULL )
    {
        printf( "Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gCoin = Mix_LoadWAV( "media/sound/coin.wav" );
    if( gCoin == NULL )
    {
        printf( "Failed to load Coin sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gBlockhit = Mix_LoadWAV( "media/sound/blockhit.wav" );
    if( gBlockhit == NULL )
    {
        printf( "Failed to load blockhit sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
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
	menu.free();
	exitButton.free();
	playButton.free();
	endGameTexture.free();

    //Free the sound effects
    Mix_FreeChunk( gJump );
    Mix_FreeChunk( gCoin );
    Mix_FreeChunk( gBlockhit );
	gJump = NULL;
	gCoin = NULL;
	gBlockhit = NULL;

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
	Mix_Quit();

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

	// count true pressing
	int typed = 0;

	// count false pressing
	int error = 0;

	// count threat
	int count = 4;

	double velCam = 0;

	int game = MENU;

	double wpm = 0;

	// the area camera
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // while app is running
    while (!quit) {

		capTimer.start();

		if (gameTimer.isStarted() == false) {
			gameTimer.start();
		}

        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if ( e.type == SDL_QUIT ) {
                quit = true;
            } 
			else if (game == MENU) {
				playButton.handleEvent(&e);
				exitButton.handleEvent(&e);
			} 
			else if (game == PLAY) {
				if (e.type == SDL_KEYDOWN) {

					if (e.key.keysym.sym == mainChar.getChar()) {
						mainChar.setDead(true);
						typed++;
						if (mainChar.getThreat() == 1) {
							gMario.setStatus(2);
							Mix_PlayChannel(-1, gJump, 0);
						} else {
							Mix_PlayChannel(-1, gCoin, 0);
						}
					} 
					else {
						error++;
						Mix_PlayChannel(-1, gBlockhit, 0);
					}
				}
			}
			if (game == END) {
				nextButton.handleEvent(&e);
				menuButton.handleEvent(&e);
			}

        } 

		if (exitButton.isUp()) {
			quit = true;
		}
		else if (playButton.isUp()) {
			game = PLAY;
		} 
		else if (nextButton.isUp()) {
			game = PLAY;
			gameTimer.stop();
			gameTimer.start();
			cout << 1;
			count = 0;
			error = 0;
		} 
		else if (menuButton.isUp()) {
			game = MENU;
		}

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

		if (game == PLAY) {

			// check character 
			if (mainChar.isDead() == true) {

				arrChar[0].free();
				arrChar.erase(arrChar.begin());
				stop += 240;

			}

			// calculate wpm
			wpm = ((double) typed / 5) /  ((double) gameTimer.getTicks() / 60000);

			// add character
			while (arrChar.size() < 4 && count < MAX_THREAT) {

				c.createChar();
				c.createThreat();

				arrChar.push_back(c);

				count++;

			}

			if (!temp.loadFromRenderedText(gRenderer, gameFont, "Hello, World!", textColor)) {
				printf("Unable to render temp texture!\n", TTF_GetError());
				return -1;
			}	

			if (!errorTexture.loadFromRenderedText(gRenderer, gameFont, "Error: " + to_string(error), textColor)) {
				printf("Unable to render error texture!\n", TTF_GetError());
				return -1;
			}

			if (!typedTexture.loadFromRenderedText(gRenderer, gameFont, "Typed: " + to_string(typed), textColor)) {
				printf("Unable to render typed texture!\n", TTF_GetError());
				return -1;
			}

			if (!wordPerMinute.loadFromRenderedText(gRenderer, gameFont, "WPM: " + to_string((int) wpm), textColor)) {
				printf("Unable to render wpm texture!\n");
				return -1;
			}

			if (!gameTimeTexture.loadFromRenderedText(gRenderer, gameFont, gameTimer.convert(), textColor)) {
				printf("Unable to render game time texture!\n", TTF_GetError());
				return -1;
			}

			// load character texture
			switch (typed) {
				case (MAX_THREAT - 3):
					for (int i = 0; i < 3; i++) {
						string s(1, arrChar[i].getChar());
						if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
							printf( "Unable to render character texture!\n", TTF_GetError() );
							return -1;
						}

					}
					break;
				case (MAX_THREAT - 2): 

					for (int i = 0; i < 2; i++) {
						string s(1, arrChar[i].getChar());
						if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
							printf( "Unable to render character texture!\n", TTF_GetError() );
							return -1;
						}

					}
					break;
				case (MAX_THREAT - 1):

					for (int i = 0; i < 1; i++) {
						string s(1, arrChar[i].getChar());
						if (!arrChar[i].loadFromRenderedText(gRenderer, gFont, s, textColor)) {
							printf( "Unable to render character texture!\n", TTF_GetError() );
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
							printf( "Unable to render character texture!\n", TTF_GetError() );
							return -1;
						}

					} 
					break;
			}
			

			mainChar = arrChar[0];

			if ((camera.x + SCREEN_WIDTH) < (MAX_THREAT + 1) * 240) {
				camera.x += velCam;
			}

			// render background
			gBackground.render(0, 0, gRenderer);

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
					
					gameTimer.pause();
					game = END;
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

			// render main character
			mainChar.render(562, 562, gRenderer);

			// render road
			road.renderRoad(gRenderer, xRoad - camera.x);

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

			gameTimeTexture.render(40, 560, gRenderer);

			typedTexture.render(40, 640, gRenderer);

			errorTexture.render(950, 640, gRenderer);

			wordPerMinute.render(950, 560, gRenderer);

			rightHand.renderRightHand(gRenderer, mainChar.getChar());
			leftHand.renderLeftHand(gRenderer, mainChar.getChar());

			gMario.run(gRenderer, camera.x, stop);

			if (xRoad + SCREEN_WIDTH <= camera.x) {
				xRoad += SCREEN_WIDTH;
			}

		}
		else if (game == MENU) {

			menu.render(0, 0, gRenderer);

			playButton.setPosition(476, 410);
			exitButton.setPosition(476, 500);
			
			playButton.renderButton(gRenderer);
			exitButton.renderButton(gRenderer);

		} 

		if (game == END) {

			// render background
			gBackground.render(0, 0, gRenderer);

			// render road
			road.renderRoad(gRenderer, xRoad - camera.x);

			gameTimeTexture.loadFromRenderedText(gRenderer, gameFont, "Time: " + gameTimer.convert(), textColor);
			
			endGameTexture.render(334, 175, gRenderer);

			gameTimeTexture.render(555, 229, gRenderer);

			typedTexture.render(555, 288, gRenderer);

			errorTexture.render(555, 347, gRenderer);

			wordPerMinute.render(555, 404, gRenderer);

			nextButton.setPosition(375, 466);
			nextButton.renderButton(gRenderer);

			menuButton.setPosition(608, 466);
			menuButton.renderButton(gRenderer);

		}
		
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