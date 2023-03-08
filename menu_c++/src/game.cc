#include "game.h"

// Set instance as NULL so we can tell that it has not been instantiated
GameMaster* GameMaster::_instance = nullptr;

// All SDL initialization happens in the GameMaster constructor
GameMaster::GameMaster(): _texture(nullptr), _state(GAME_MAINMENU), _is_running(true) {
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	_window = SDL_CreateWindow("Menu Test",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_W, SCREEN_H,
			SDL_WINDOW_RESIZABLE
		);

	if (!_window){
		fprintf(stderr, "Fatal Error: Window failed to initialize\n");
		fprintf(stderr, "SDL2 Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	TTF_Init(); // This must be called in order to use fonts

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	// _font = newFont(FONT_FILE, FONT_SIZE);
	// Allow window to be resizable
	SDL_SetWindowResizable(_window, SDL_TRUE);
	// Allows for transparent rendering
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	// Allow resolution independence (This fucks up coordinates though)
	// SDL_RenderSetLogicalSize(gd->renderer, SCREEN_W, SCREEN_H);
}

GameMaster* GameMaster::init(){
	// Only instantiate GameMaster if we haven't already
	if (_instance == nullptr)
		_instance = new GameMaster();
	else
		std::cerr << "Warning: GameMaster was not initialized because an instance of it already exists.\n";
	return _instance;
}

void GameMaster::addFont(string font_file, size_t font_size){
	_fonts.push_back(initFont(font_file, font_size));	
}


void GameMaster::handleInput(SDL_Event e){
	if (e.type == SDL_QUIT || // If user pressed [X] or Ctrl+C in terminal (and other methods of exit)
			(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){ // If user presses ESC
		_is_running = false;
		_state = GAME_QUIT;
	}
}

void GameMaster::renderClear(unsigned long hex_color){
	SDL_Color col = convertHexColor(hex_color, 0xFF);
	SDL_SetRenderDrawColor(_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(_renderer);
}
void GameMaster::renderPresent(){
	SDL_RenderPresent(_renderer);
}
void GameMaster::renderText(int x, int y, 
				string text, unsigned long hex_color, size_t font_idx,
				int w, int h){
	assert(font_idx < _fonts.size() && "Error: Font index exceeds number of available fonts!");
	SDL_Rect rect;
	SDL_Surface *surface = nullptr;
	SDL_Color color = convertHexColor(hex_color);
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	surface = TTF_RenderText_Solid(_fonts[font_idx], text.c_str(), color);
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	w = surface->w;
	h = surface->h;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(_renderer, _texture, nullptr, &rect);
	SDL_DestroyTexture(_texture);
}

TTF_Font* initFont(string font_file, size_t font_size){
	TTF_Font* font = TTF_OpenFont(font_file.c_str(), font_size);
	if (!font) 
		std::cerr << "Error: Font file: " << font_file << " was not found.\n";	
	return font;
}

SDL_Color convertHexColor(unsigned long hex_color, uint8_t opacity){
	uint8_t r = ((hex_color >> 16) & 0xFF);
	uint8_t g = ((hex_color >> 8) & 0xFF);
	uint8_t b = ((hex_color) & 0xFF);
	uint8_t a = opacity;
	return SDL_Color { .r=r, .g=g, .b=b, .a=a };
}
