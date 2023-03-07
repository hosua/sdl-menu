#include "game.h"
#include "menu.h"

GameData* gd = NULL;

const char* mainMenuText[6] = {
	"Button A","Button B","Button C", 
	"Button D","Button E","Button F", 
};
int mainMenuColors[6] = {
	RED, SKY_BLUE, BLUE,
	GREEN, WHITE, RED,
};
void* mainMenuFuncs[6] = {funcA, funcB, funcC, funcD, funcE, funcF};
size_t n_btns_main = 6;

const char* menuAText[] = { "Option A", "Back" };
int menuAColors[] = {GREEN, RED};
void* menuAFuncs[] = {NULL, gotoMainMenu};
size_t n_btns_a = 2;


int main(){
	bool running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	Button* mainMenu = initMenu(150, 150, 200, 100, 
								3, 2, 
								10, 20, 
								mainMenuText, mainMenuColors, mainMenuFuncs,
								n_btns_main);

	Button* menuA = initMenu(150, 150, 200, 100, 
								1, 2, 
								10, 20, 
								menuAText, menuAColors, menuAFuncs,
								n_btns_main);
	gd = initGameData();
	// Button b = newButton(150, 25, 200, 100, SKY_BLUE, "Press me", WHITE, 0, buttonAction);
	// game loop
	while (running){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			// btnHandleEvents(&b, &event);
			switch(gd->state){
				case MENU_MAIN:
					menuHandle(mainMenu, n_btns_main, &event, gd);
					break;
				case MENU_A:
					menuHandle(menuA, n_btns_a, &event, gd);
					break;
				case MENU_B:
					break;
			}

			if (event.type == SDL_QUIT || 
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				running = false;
		}
		GFX_Render(gd);
		switch(gd->state){
			case MENU_MAIN:
				menuRender(mainMenu, n_btns_main, gd);
				break;
			case MENU_A:
				menuRender(menuA, n_btns_a, gd);
				break;
			case MENU_B:
				break;
		}
		// GFX_RenderButton(&b, gd);
		// GFX_RenderText(game_data, 5, 5, 100, 100, "Hello world", WHITE);
		GFX_RenderPresent(gd);
	}
}
