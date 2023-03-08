#ifndef GRAPHICS_H 
#define GRAPHICS_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define FONT_FILE "fonts/pixel-letters.ttf"
#define FONT_SIZE 30

#define BLOCK_SIZE 25
#define GRID_W 10
#define GRID_H 10

#define WHITE 0xFFFFFF
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define BLUE 0x0000FF
#define SKY_BLUE 0x2F9CEB
#define GREEN 0x00FF00
#define GREEN0 0x009C00
#define RED 0xFF0000
#define PURPLE 0x640A6E

#define PLAYER_COLOR PURPLE
#define PLAYER_W 20
#define PLAYER_H 30
#define PLAYER_MAX_HP 100
#define PLAYER_VEL PLAYER_W

typedef enum {
	QUIT,
	MENU_MAIN,
	MENU_A,
	MENU_B,
	PLAY,
	PAUSED,
} GameState;

typedef struct GameData {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture *texture;
	GameState state;
	TTF_Font* font;
	float fps;
} GameData;

typedef struct Button {
	char* text;
	SDL_Surface* surface;
	SDL_Rect rect;
	unsigned long hex_bgcolor, hex_fontcolor, hex_currcolor;
	void (*function)(GameData* gd); // Callback function
} Button;

GameData* initGameData();
Button newButton(int x, int y, int w, int h,
				unsigned long hex_bgcolor,
				const char* text, 
				unsigned long hex_fontcolor,
				int params, void(*function)());

SDL_Surface *initText(char* text, int font_size, int font_hex_color, int params);
SDL_Color hexToColor(unsigned long hex_color);

void GFX_ClearScreen(GameData* gd, unsigned long hex_color);
void GFX_RenderText(int x, int y, int w, int h, char* text, unsigned long hex_color, GameData* gd);
void GFX_RenderPresent(GameData* self);

void btnRender(Button* btn, GameData* gd);
void btnHandleEvents(Button* self, SDL_Event* e, GameData* gd);

#endif // GRAPHICS_H
