#ifndef _H_ObjetoPG_H_
#define _H_ObjetoPG_H_

#include "SDL.h"
#include "JuegoPG.h"
#include "ObjetoJuego.h"


class ObjetoPG : public ObjetoJuego
{
public:

	ObjetoPG(JuegoPG * juego, int x, int y, Texturas_t t_textura);
	virtual ~ObjetoPG() {};

	virtual void draw();
	virtual void update() = 0;
	virtual bool onClick() = 0;

	bool visible;

protected:
	JuegoPG * obJuego;
	Texturas_t tipoTextura;
	SDL_Rect rect;

	int posX, posY;
	bool dentro(int x, int y)const;
};

#endif
