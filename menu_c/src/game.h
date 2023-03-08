#ifndef GAME_H
#define GAME_H
#include "graphics.h"


typedef struct Player {
	SDL_Rect r;
	int max_hp;
	int hp;
	int vel; 
} Player;

Player* newPlayer(int max_hp, int vel, int x, int y, int w, int h);
void playerRender(Player* player, GameData* gd);
void playerHandle(Player* self, SDL_Event* e, GameData* gd);


#endif // GAME_H
