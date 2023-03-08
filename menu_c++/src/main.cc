#include "game.h"
#include "menu.h"

vector<size_t> font_sizes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
const char* ttf_pixel_letters = "fonts/pixel-letters.ttf";

void startGame(GameMaster* gm){ gm->_state = GAME_PLAY; }
void goSettings(GameMaster* gm){ gm->_state = GAME_SETTINGS; }
void goLevelSelect(GameMaster* gm){ gm->_state = GAME_LEVELSELECT; }
void quitGame(GameMaster* gm){ gm->_state = GAME_QUIT; }

int main(){
	GameMaster* gm = GameMaster::init();
	
	// Create some fonts and store them in GameMaster object
	for (size_t sz : font_sizes)
		gm->addFont(ttf_pixel_letters, sz);

	vector<string> main_menu_text = {"Play", "Level Select", "Settings", "Quit"};
	vector<func_t> main_menu_funcs = {startGame, goLevelSelect, goSettings, quitGame};

	unique_ptr<Menu> main_menu(new Menu(4, main_menu_text, main_menu_funcs,
			150, 150, 150, 50,	
			2,
			10, 10,
			0.10f, 0.10f,
			2,
			WHITE, BLACK)
	);


	while (gm->_is_running){
		SDL_Event event;
		switch(gm->_state){
			case GAME_MAINMENU:
				gm->renderClear(GRAY);
				main_menu->render(gm);
				// for (int i = 0; i < gm->_fonts.size(); i++)
				// 	gm->renderText(15, (i+1)*60, string("Font " + std::to_string(i+1)), WHITE, i);
				while (SDL_PollEvent(&event)){
					gm->handleInput(event);
					// test_button->handleEvents(&event, gm);
					main_menu->handleEvents(&event, gm);
				}
				gm->renderPresent();
				break;
			case GAME_QUIT:
				gm->_is_running = false;
				break;
			case GAME_PLAY:
				cout << "Selected play button\n";
				gm->_state = GAME_MAINMENU;
				break;
			case GAME_LEVELSELECT:
				cout << "Selected level select button\n";
				gm->_state = GAME_MAINMENU;
				break;
			case GAME_SETTINGS:
				cout << "Selected settings button\n";
				gm->_state = GAME_MAINMENU;
				break;
		}
	}	
	// TTF_Font cleanup
	for (TTF_Font* font : gm->_fonts)
		TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
