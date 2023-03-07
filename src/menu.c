#include "menu.h"

void funcA(GameData* gd){
	printf("Running function A\n");
	gd->state = MENU_A;
}
void funcB(){
	printf("Running function B\n");
}
void funcC(){
	printf("Running function C\n");
}
void funcD(){
	printf("Running function D\n");
}
void funcE(){
	printf("Running function E\n");
}
void funcF(){
	printf("Running function F\n");
}

void gotoMainMenu(GameData* gd){
	gd->state = MENU_MAIN;	
}

Button* initMenu(int x, int y, int w, int h,
		int nrows, int ncols, 
		int rgap, int cgap, 
		const char* text[], int colors[], void* func[],
		size_t num_btns){

	int y_start = y;
	int r = 0;
	Button* buttons = (Button*)malloc(sizeof(Button)*num_btns);
	for (int i = 0; i < num_btns; i++){
		buttons[i] = newButton(x, y, w, h, colors[i], text[i], WHITE, 0, func[i]);
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
		GFX_RenderButton(&menu[i], gd);
}

void menuHandle(Button* menu, size_t num_btns, SDL_Event* event, GameData* gd){
	for (int i = 0; i < num_btns; i++)
		btnHandleEvents(&menu[i], event, gd);
}
