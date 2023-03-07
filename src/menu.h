#ifndef MENU_H
#define MENU_H
#include "graphics.h"

Button* newMenu(int x, int y, int w, int h,
		int nrows, int ncols, 
		int rgap, int cgap, 
		const char* text[], int colors[], void* func[],
		size_t num_btns);

void gotoMainMenu(GameData* gd);

void menuRender(Button* menu, size_t num_btns, GameData* gd);
void menuHandle(Button* menu, size_t num_btns, SDL_Event* event, GameData* gd);

void funcA(GameData* gd);
void funcB(GameData* gd);
void funcC(GameData* gd);
void resumeGame(GameData* gd);
void quitGame(GameData* gd);

#endif // MENU_H
