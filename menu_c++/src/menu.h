#ifndef MENU_H
#define MENU_H
#include "game.h"
#include <memory>

typedef void(*func_t)(GameMaster*);

class Button {
public:

	Button(int x, int y, int w, int h,
			unsigned long hex_bgcolor,
			string text, size_t font_idx, unsigned long hex_fontcolor,
			float x_offset=0.25f, float y_offset=0.25f,
			int params=0, func_t function=nullptr);

	~Button(){}

	void render(GameMaster* gm);
	void handleEvents(SDL_Event* e, GameMaster* gm);

private:
	string _text;
	SDL_Surface* _surface;
	SDL_Rect _rect;
	float _x_offset, _y_offset;
	size_t _font_idx;
	unsigned long _hex_bgcolor, _hex_fontcolor, _hex_currcolor;
	func_t _function;
};

class Menu {
public:
	Menu(size_t num_buttons, vector<string> text, vector<func_t> functions,
	 	 int x, int y, int w, int h,
		 int ncols,
		 int rgap=10, int cgap=10,
		 float x_offset=0.1f, float y_offset=0.1f,
		 size_t font_idx=0,
		 unsigned long hex_bgcolor=WHITE, unsigned long hex_fontcolor=BLACK);
	
	void render(GameMaster* gm);
	void handleEvents(SDL_Event* e, GameMaster* gm);
private:
	vector<shared_ptr<Button>> _buttons;
};


#endif // MENU_H
