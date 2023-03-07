#include "menu.h"

void funcA(){
	printf("Running function A\n");
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

Button* initMenu(size_t num_btns, int nrows, int ncols, int rgap, int cgap){
	int bw = 200, bh = 100;
	int x = 150, y = 150;
	const char* text[6] = {
		"Button A","Button B","Button C", 
		"Button D","Button E","Button F", 
	};

	int colors[6] = {
		RED, SKY_BLUE, BLUE,
		GREEN, WHITE, RED,
	};

	void* func[6] = {funcA, funcB, funcC, funcD, funcE, funcF};

	int y_start = y;
	int r = 0;
	Button* buttons = (Button*)malloc(sizeof(Button)*num_btns);
	for (int i = 0; i < num_btns; i++){
		buttons[i] = newButton(x, y, bw, bh, colors[i], text[i], WHITE, 0, func[i]);
		r++;
		if (r == nrows){
			r = 0;
			x += bw + cgap;
			y = y_start;
		} else {
			y += bh + rgap;
		}
	}
	return buttons;
}

void menuRender(Button* buttons, size_t num_btns, GameData* gd){
	for (int i = 0; i < num_btns; i++)
		GFX_RenderButton(&buttons[i], gd);
}

void menuHandle(Button* buttons, size_t num_btns, SDL_Event* event, GameData* gd){
	for (int i = 0; i < num_btns; i++)
		btnHandleEvents(&buttons[i], event);
}
