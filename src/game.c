#include "game.h"

Player* newPlayer(int max_hp, int vel, int x, int y, int w, int h){
	Player* player = (Player*) malloc(sizeof(Player));
	SDL_Rect rect = { .x=x, .y=y, .w=w, .h=h };
	player->r = rect;
	player->vel = vel;
	player->max_hp = player->hp = max_hp;
	return player;
}

void playerRender(Player* self, GameData* gd){
	SDL_Rect rect = {
		.x = self->r.x, .y = self->r.y,
		.w = self->r.w, .h = self->r.h,
	};
	SDL_Surface* surface = NULL;
	SDL_Color plc = hexToColor(PLAYER_COLOR);
	SDL_SetRenderDrawColor(gd->renderer, plc.r, plc.g, plc.b, 255);
	SDL_RenderFillRect(gd->renderer, &rect);
}

void playerHandle(Player* self, SDL_Event* event, GameData* gd){
	if (event->type == SDL_QUIT || 
			(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE))
		gd->state = PAUSED;
	switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
				case SDLK_w: case SDLK_UP:
					self->r.y -= self->vel;
					break;
				case SDLK_s: case SDLK_DOWN:
					self->r.y += self->vel;
					break;
				case SDLK_a: case SDLK_LEFT:
					self->r.x -= self->vel;
					break;
				case SDLK_d: case SDLK_RIGHT:
					self->r.x += self->vel;
					break;
				case SDLK_p: 
					gd->state = PAUSED;
					break;
			}
			break;
	}

}
