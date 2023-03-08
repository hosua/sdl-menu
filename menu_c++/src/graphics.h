#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "game.h"

// Note: All font_idx arguments refer to the index of the font in _gm->fonts that you wish to use
// GFX is a Singleton object as it has no need to be instantiated more than once. 
// It also must attach to the GameMaster object.
class GFX {
public:
	static GFX* init(GameMaster* gm);
	// clear the render of a certain color (black by default)
	void renderClear(unsigned long hex_color=BLACK);
	// renderPresent() must be called after rendering in the current frame is complete
	void renderPresent();
	// render text to screen
	void renderText(int x, int y, 
					string text, unsigned long hex_color=BLACK, size_t font_idx=0,
					int w=25, int h=25);
private:
	static GFX* _instance;
	GFX(GameMaster* gm): _gm(gm){}
	GameMaster* _gm;
};

#endif // GRAPHICS_H
