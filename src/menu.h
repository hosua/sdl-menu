#ifndef MENU_H
#define MENU_H
#include "game.h"

Button* initMenu(size_t num_btns, int nrows, int ncols, int rgap, int cgap);
void menuRender(Button* buttons, size_t num_btns, GameData* gd);
void menuHandle(Button* buttons, size_t num_btns, SDL_Event* event, GameData* gd);



#endif // MENU_H
