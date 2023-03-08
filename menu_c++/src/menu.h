#ifndef MENU_H
#define MENU_H
#include "game.h"
#include <memory>

typedef void(*func_t)(shared_ptr<GameMaster>);

class Button {
public:
	Button(int x, int y, int w, int h,
			unsigned long hex_btncolor,
			string text, size_t font_idx, unsigned long hex_fontcolor,
			float x_offset=0.25f, float y_offset=0.25f,
			int params=0, func_t function=nullptr);

	~Button(){}

	void render(shared_ptr<GameMaster> gm);
	void handleEvents(SDL_Event* e, shared_ptr<GameMaster> gm);

private:
	string _text;
	SDL_Surface* _surface;
	SDL_Rect _rect;
	float _x_offset, _y_offset;
	size_t _font_idx;
	unsigned long _hex_btncolor, _hex_fontcolor, _hex_currcolor;
	func_t _function;
};

class Menu {
public:
	Menu(vector<string> text, vector<func_t> functions,
	 	 int x, int y, int w, int h,
		 int ncols,
		 int rgap=10, int cgap=10,
		 float x_offset=0.1f, float y_offset=0.1f,
		 size_t font_idx=0,
		 unsigned long hex_btncolor=WHITE, unsigned long hex_fontcolor=BLACK);
	
	void render(shared_ptr<GameMaster> gm);
	void handleEvents(SDL_Event* e, shared_ptr<GameMaster> gm);
	
	// TODO: Add the ability to set a title for menus
	void setBackground(unsigned long hex_bgcolor, int border_sz=15);
private:
	vector<shared_ptr<Button>> _buttons;
	unsigned long _hex_bgcolor;
	int _nbtns;
	int _ncols, _rgap, _cgap;
	SDL_Rect _rect;
	unique_ptr<SDL_Rect> _bgrect;
};


#endif // MENU_H
