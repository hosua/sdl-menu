#ifndef GAME_H 
#define GAME_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <assert.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define FONT_FILE "fonts/pixel-letters.ttf"
#define FONT_SIZE 30
#define FPS 60

#define WHITE 0xFFFFFF
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define GRAY 0x302F2F
#define BLUE 0x0000FF
#define SKY_BLUE 0x2F9CEB
#define GREEN 0x00FF00
#define GREEN0 0x009C00
#define RED 0xFF0000
#define PURPLE 0x640A6E

using std::string;
using std::vector;

// Game states for the state machine
typedef enum {
	GAME_QUIT,
	GAME_MAINMENU,
} GameState;

/* GameMaster class is a singleton, it can and should only be instantiated once.
 * To initialize it, call the init() function like so:
 * GameMaster* game = GameMaster::init();
 */

class GameMaster {
public:
	// Call this function instead of using new operator to instantiate GameMaster
	static GameMaster* init();

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;

	vector<TTF_Font*> _fonts;

	GameState _state;
	bool _is_running;

	void addFont(string font_file, size_t font_size);

	void handleInput(SDL_Event e);

private:
	// Private constructor to prevent new operator from being used outside of init()
	GameMaster();
	// The stored instance. Using this to verify if GameMaster has been initialized yet
	static GameMaster* _instance;
};

// Creates a font object
TTF_Font* initFont(string font_file, size_t font_size);
// Convert hexadecimal representation of color to SDL_Color object. 
// Opacity range is 0-255, default opacity is fully opaque.
SDL_Color convertHexColor(unsigned long hex_color, uint8_t opacity=0xFF);

#endif // GAME_H
