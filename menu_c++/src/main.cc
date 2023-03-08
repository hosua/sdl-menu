#include "graphics.h"
#include "game.h"
#include "menu.h"

vector<size_t> font_sizes = {100, 90, 80, 70, 60, 50, 40, 30, 20};
const char* ttf_pixel_letters = "fonts/pixel-letters.ttf";

int main(){
	GameMaster* gm = GameMaster::init();
	GFX* gfx = GFX::init(gm);
	
	// Create some fonts
	for (size_t sz : font_sizes)
		gm->addFont(ttf_pixel_letters, sz);

	while (gm->_is_running){
		SDL_Event event;
		switch(gm->_state){
			case GAME_MAINMENU:
				gfx->renderClear(GRAY);
				for (int i = 0; i < gm->_fonts.size(); i++)
					gfx->renderText(15, (i+1)*60, string("Font " + std::to_string(i)), WHITE, i);
				while (SDL_PollEvent(&event)){
					gm->handleInput(event);
				}
				gfx->renderPresent();
				break;
			case GAME_QUIT:
				gm->_is_running = false;
				break;
		}
	}	
	// TTF_Font cleanup
	for (TTF_Font* font : gm->_fonts)
		TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
