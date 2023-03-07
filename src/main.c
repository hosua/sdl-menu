#include "game.h"
#include "menu.h"

GameData* gd = NULL;

void buttonAction(){
	printf("Pressed button\n");
}

int main(){
	bool running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	int num_btns = 6;
	Button* buttons = initMenu(num_btns, 3, 2, 10, 20);
	gd = newGameData();
	// Button b = newButton(150, 25, 200, 100, SKY_BLUE, "Press me", WHITE, 0, buttonAction);
	// game loop
	while (running){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			// btnHandleEvents(&b, &event);

			menuHandle(buttons, num_btns, &event, gd);

			if (event.type == SDL_QUIT || 
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				running = false;
		}
		GFX_Render(gd);
		menuRender(buttons, num_btns, gd);
		// GFX_RenderButton(&b, gd);
		// GFX_RenderText(game_data, 5, 5, 100, 100, "Hello world", WHITE);
		GFX_RenderPresent(gd);
	}
}
