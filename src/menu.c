#include "menu.h"

void funcA(GameData* gd){
	printf("Running function A\n");
	gd->state = MENU_A;
}
void funcB(GameData* gd){
	printf("Running function B\n");
	gd->state = PLAY;
}
void funcC(GameData* gd){
	printf("Running function C\n");
}
void quitGame(GameData* gd){
	printf("Running function D\n");
	gd->state = QUIT;
}

void resumeGame(GameData* gd){
	printf("Resuming game\n");
	gd->state = PLAY;
}

void gotoMainMenu(GameData* gd){
	gd->state = MENU_MAIN;	
}

Button* newMenu(int x, int y, int w, int h,
		int nrows, int ncols, 
		int rgap, int cgap, 
		unsigned long hex_color, const char* text[], void* func[],
		size_t num_btns){

	int y_start = y;
	int r = 0;
	Button* buttons = (Button*)malloc(sizeof(Button)*num_btns);
	for (int i = 0; i < num_btns; i++){
		buttons[i] = newButton(x, y, w, h, hex_color, text[i], WHITE, 0, func[i]);
		r++;
		if (r == nrows){
			r = 0;
			x += w + cgap;
			y = y_start;
		} else {
			y += h + rgap;
		}
	}
	return buttons;
}

void menuRender(Button* menu, size_t num_btns, GameData* gd){
	for (int i = 0; i < num_btns; i++)
		btnRender(&menu[i], gd);
}

void menuHandle(Button* menu, size_t num_btns, SDL_Event* event, GameData* gd){
	for (int i = 0; i < num_btns; i++)
		btnHandleEvents(&menu[i], event, gd);
}
