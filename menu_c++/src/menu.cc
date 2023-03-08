#include "menu.h"

Button::Button(int x, int y, int w, int h,
			unsigned long hex_bgcolor,
			string text, size_t font_idx, unsigned long hex_fontcolor,
			float x_offset, float y_offset,
			int params, func_t function)
		: _function(function), _text(text.c_str()), _hex_bgcolor(hex_bgcolor), _hex_currcolor(hex_bgcolor),
		  _hex_fontcolor(hex_fontcolor), _font_idx(font_idx), 
		  _x_offset(x_offset), _y_offset(y_offset), 
		  _rect({.x=x, .y=y, .w=w, .h=h}){
}

void Button::render(GameMaster* gm){
	SDL_Rect r = { .x=_rect.x, .y=_rect.y, .w=_rect.w, .h=_rect.h };
	SDL_Color bgc = convertHexColor(_hex_currcolor);
	SDL_Color fontc = convertHexColor(_hex_fontcolor);
	SDL_SetRenderDrawColor(gm->_renderer, bgc.r, bgc.g, bgc.b, 255);
	SDL_RenderFillRect(gm->_renderer, &_rect);
	SDL_SetRenderDrawColor(gm->_renderer, fontc.r, fontc.g, fontc.b, 255);
	gm->renderText((r.x + (_x_offset)*r.w), (r.y + (_y_offset)*r.h), _text, BLACK, _font_idx);
}

void Button::handleEvents(SDL_Event* e, GameMaster* gm){
	SDL_Rect rect = {
		.x = _rect.x, .y = _rect.y,
		.w = _rect.w, .h = _rect.h,
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
		_hex_currcolor = GREEN0;
		if (e->type == SDL_MOUSEBUTTONDOWN && _function)
			_function(gm);
	} else {
		_hex_currcolor = _hex_bgcolor;
	}
}

Menu::Menu(size_t num_buttons, vector<string> text, vector<func_t> functions,
	 int x, int y, int w, int h,
	 int ncols,
	 int rgap, int cgap,
	 float x_offset, float y_offset,
	 size_t font_idx,
	 unsigned long hex_bgcolor, unsigned long hex_fontcolor){
	
	int c = 0;
	int x_start = x;
	for (int i = 0; i < num_buttons; i++){
		shared_ptr<Button> button(new Button(x, y, w, h,
				WHITE, text[i], font_idx, BLACK,
				x_offset, y_offset,
				0, functions[i])
		);
		_buttons.push_back(button);
		c++;
		if (c == ncols){
			c = 0;
			y += h + rgap;
			x = x_start;
		} else {
			x += w + cgap;
		}
	}
}

void Menu::render(GameMaster* gm){
	for (shared_ptr<Button> btn : _buttons)
		btn->render(gm);
}
void Menu::handleEvents(SDL_Event* e, GameMaster* gm){
	for (shared_ptr<Button> btn : _buttons)
		btn->handleEvents(e, gm);
}
