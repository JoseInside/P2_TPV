#ifndef _H_TexturasSDL_H_
#define _H_TexturasSDL_H_

#include "SDL.h"
#include <string>

using namespace std;

class TexturasSDL
{
public:
	string nombArch;

	TexturasSDL() {};
	~TexturasSDL();

	bool load(SDL_Renderer* pRender, string const& nombArch);
	void draw(SDL_Renderer* pRender, SDL_Rect const& rect);

private:

	SDL_Renderer* pRender = nullptr;
	SDL_Texture* textura = nullptr;		
};

#endif