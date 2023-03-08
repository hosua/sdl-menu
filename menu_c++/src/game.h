#ifndef GAME_H 
#define GAME_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <functional>
#include <memory>

#define SCREEN_W 800
#define SCREEN_H 600
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

using std::cout;
using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;

// Game states for the state machine
typedef enum {
	GAME_QUIT,
	GAME_MAINMENU,
	GAME_SETTINGS,
	GAME_LEVELSELECT,
	GAME_PLAY,
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

	void renderClear(unsigned long hex_color=BLACK);
	// renderPresent() must be called after rendering in the current frame is complete
	void renderPresent();
	// render text to screen
	void renderText(int x, int y, 
					string text, unsigned long hex_color=BLACK, size_t font_idx=0,
					int w=25, int h=25);

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
