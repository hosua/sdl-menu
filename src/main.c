#include "graphics.h"
#include "menu.h"
#include "game.h"

GameData* gd = NULL;

size_t n_btns_main = 4;
const char* mainMenuText[] = {"Button A","Play Game","Button C","Quit Game"};
void* mainMenuFuncs[] = {funcA, funcB, funcC, quitGame};

size_t n_btns_a = 2;
const char* menuAText[] = { "Option A", "Back" };
void* menuAFuncs[] = {NULL, gotoMainMenu};

size_t n_btns_pause = 3;
const char* menuPauseText[] = { "Resume", "Main Menu", "Quit" };
void* menuPauseFuncs[] = {resumeGame,gotoMainMenu,quitGame};


int main(){
	bool running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	Button* mainMenu = newMenu(150, 150, 200, 100, 
								2, 2, 
								10, 10, 
								WHITE, mainMenuText, mainMenuFuncs,
								n_btns_main);

	Button* menuA = newMenu(150, 150, 200, 100, 
								1, 2, 
								10, 10, 
								WHITE, menuAText, menuAFuncs,
								n_btns_a);

	Button* pauseMenu = newMenu(150,150,200,100,
								2,2,
								10,10,
								WHITE, menuPauseText, menuPauseFuncs,
								n_btns_pause);
	gd = initGameData();
	// Button b = newButton(150, 25, 200, 100, SKY_BLUE, "Press me", WHITE, 0, buttonAction);
	
	// Main menu loop
	while (running){
		SDL_Event event;
		switch(gd->state){
			case MENU_MAIN:
				GFX_ClearScreen(gd, BLACK);
				while (SDL_PollEvent(&event)){
					menuHandle(mainMenu, n_btns_main, &event, gd);
					if (event.type == SDL_QUIT || 
							(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
						running = false;
				}
				menuRender(mainMenu, n_btns_main, gd);
				GFX_RenderPresent(gd);
				break;
			case MENU_A:
				GFX_ClearScreen(gd, BLACK);
				while (SDL_PollEvent(&event)){
					menuHandle(menuA, n_btns_a, &event, gd);
					if (event.type == SDL_QUIT || 
							(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
						running = false;
				}
				menuRender(menuA, n_btns_a, gd);
				GFX_RenderPresent(gd);
				break;
			case MENU_B:
				break;
			case PLAY:
			{
				// Gameplay code goes here
				Player* player = newPlayer(PLAYER_MAX_HP, PLAYER_VEL, 25, 25, PLAYER_W, PLAYER_H);
				SDL_bool ingame = SDL_TRUE;
				SDL_bool paused = SDL_FALSE;
				while (ingame){ // Game loop
					GFX_ClearScreen(gd, BLACK);
					paused = (gd->state == PAUSED) ? SDL_TRUE : SDL_FALSE;
					if (gd->state == MENU_MAIN || gd->state == QUIT){
						free(player);
						break;
					}
					if (!paused){ // playing
						while (SDL_PollEvent(&event))
							playerHandle(player, &event, gd);
					} else { // paused
						while (SDL_PollEvent(&event))
							menuHandle(pauseMenu, n_btns_pause, &event, gd);
						menuRender(pauseMenu, n_btns_pause, gd);
					}
					playerRender(player, gd);
					GFX_RenderPresent(gd);
					if (!running)
						break;
				} // end game loop
				break;
			}
			case QUIT: default:
				running = false;
				break;
		}
	}
}
