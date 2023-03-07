#include "game.h"

SDL_Color hexToColor(unsigned long hex_color){
	SDL_Color color;
	color.r = ((hex_color >> 16) & 0xFF); // Extract first two bytes
	color.g = ((hex_color >> 8) & 0xFF); // Extract middle two bytes
	color.b = ((hex_color) & 0xFF); // Extract last two bytes
	return color;
}

GameData* newGameData(){
	GameData* gd = (GameData*) malloc(sizeof(GameData));
	gd->window = SDL_CreateWindow("Menu Test",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_W, SCREEN_H,
			SDL_WINDOW_RESIZABLE);

	if (!gd->window){
		fprintf(stderr, "Fatal Error: Window failed to initialize\n");
		fprintf(stderr, "SDL2 Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	gd->renderer = SDL_CreateRenderer(gd->window, -1, SDL_RENDERER_ACCELERATED);
	gd->texture = NULL;

	TTF_Init();
	gd->font = TTF_OpenFont(FONT_FILE, FONT_SIZE);
	if (!gd->font){
		fprintf(stderr, "Error: Font file \"%s\" not found\n", FONT_FILE);
		exit(EXIT_FAILURE);
	}

	// Allow window to be resizable
	SDL_SetWindowResizable(gd->window, SDL_TRUE);
	// Allows for transparent rendering
	SDL_SetRenderDrawBlendMode(gd->renderer, SDL_BLENDMODE_BLEND);
	// Allow resolution independence (This fucks up coordinates though)
	// SDL_RenderSetLogicalSize(gd->renderer, SCREEN_W, SCREEN_H);
	return gd;
}

void GFX_ClearScreen(GameData* gd, unsigned long hex_color){
	SDL_Color color = hexToColor(hex_color);
	SDL_SetRenderDrawColor(gd->renderer, color.r, color.g, color.b, 255);
	SDL_RenderClear(gd->renderer);
}

void GFX_Render(GameData* self){
	GFX_ClearScreen(self, BLACK);
}

void GFX_RenderPresent(GameData* self){
	SDL_RenderPresent(self->renderer);
}

Button newButton(int x, int y, int w, int h,
				unsigned long hex_bgcolor,
				const char* text, 
				unsigned long hex_fontcolor,
				int params, void(*function)()){
	Button b;
	b.rect.x = x;
	b.rect.y = y;
	b.rect.w = w;
	b.rect.h = h;
	b.text = strdup(text);
	b.hex_currcolor = b.hex_bgcolor = hex_bgcolor;
	b.hex_fontcolor = hex_fontcolor;
	b.function = function;
	return b;
}

void btnHandleEvents(Button* self, SDL_Event* e){
	SDL_Rect rect = {
		.x = self->rect.x, .y = self->rect.y,
		.w = self->rect.w, .h = self->rect.h,
	};

	SDL_bool inside = SDL_FALSE;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		int mx, my;
		SDL_GetMouseState(&mx, &my);
		
		// printf("mouse: (%i,%i)\n", mx, my);

		if (mx < rect.x) // mouse left of button
			inside = SDL_FALSE;
		else if (mx > rect.x + rect.w) // mouse right of button
			inside = SDL_FALSE;
		else if (my < rect.y) // mouse above button
			inside = SDL_FALSE;
		else if (my > rect.y + rect.h) // mouse below button
			inside = SDL_FALSE;
		else 
			inside = SDL_TRUE;
	}

	if (inside){
		self->hex_currcolor = GREEN0;
		if (e->type == SDL_MOUSEBUTTONDOWN && self->function)
			self->function();
	} else {
		self->hex_currcolor = self->hex_bgcolor;
	}

	// (inside) ? printf("in\n") : printf("out\n");

}

void GFX_RenderButton(Button* b, GameData* gd){
	SDL_Rect rect = {
		.x = b->rect.x, .y = b->rect.y,
		.w = b->rect.w, .h = b->rect.h,
	};
	SDL_Surface* surface = NULL;
	SDL_Color bgc = hexToColor(b->hex_currcolor);
	SDL_Color fontc = hexToColor(b->hex_fontcolor);
	SDL_SetRenderDrawColor(gd->renderer, bgc.r, bgc.g, bgc.b, 255);
	SDL_RenderFillRect(gd->renderer, &rect);
	SDL_SetRenderDrawColor(gd->renderer, fontc.r, fontc.g, fontc.b, 255);
	GFX_RenderText((rect.x + (0.25f)*rect.w), (rect.y + (0.25f)*rect.h), rect.w, rect.h, b->text, 0, gd);
}

void GFX_RenderText(int x, int y, int w, int h, char* text, unsigned long hex_color, GameData* gd){
	SDL_Rect rect;
	SDL_Surface *surface = NULL;
	SDL_Color color = hexToColor(hex_color);
	SDL_SetRenderDrawColor(gd->renderer, color.r, color.g, color.b, color.a);
	surface = TTF_RenderText_Solid(gd->font, text, color);
	gd->texture = SDL_CreateTextureFromSurface(gd->renderer, surface);
	w = surface->w;
	h = surface->h;
	SDL_FreeSurface(surface);
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(gd->renderer, gd->texture, NULL, &rect);
	SDL_DestroyTexture(gd->texture);
}
