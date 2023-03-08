#include "graphics.h"

// Set instance as NULL so we can tell that it has not been instantiated
GFX* GFX::_instance = nullptr;

GFX* GFX::init(GameMaster* gm){
	if (_instance == nullptr)
		_instance = new GFX(gm);
	else
		std::cerr << "Warning: GFX was not initialized because an instance of it already exists.\n";
	return _instance;
}

void GFX::renderClear(unsigned long hex_color){
	SDL_Color col = convertHexColor(hex_color, 0xFF);
	SDL_SetRenderDrawColor(_gm->_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(_gm->_renderer);
}
void GFX::renderPresent(){
	SDL_RenderPresent(_gm->_renderer);
}
void GFX::renderText(int x, int y, 
				string text, unsigned long hex_color, size_t font_idx,
				int w, int h){
	assert(font_idx < _gm->_fonts.size() && "Error: Font index exceeds number of available fonts!");
	SDL_Rect rect;
	SDL_Surface *surface = nullptr;
	SDL_Color color = convertHexColor(hex_color);
	SDL_SetRenderDrawColor(_gm->_renderer, color.r, color.g, color.b, color.a);
	surface = TTF_RenderText_Solid(_gm->_fonts[font_idx], text.c_str(), color);
	_gm->_texture = SDL_CreateTextureFromSurface(_gm->_renderer, surface);
	w = surface->w;
	h = surface->h;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(_gm->_renderer, _gm->_texture, nullptr, &rect);
	SDL_DestroyTexture(_gm->_texture);
}
