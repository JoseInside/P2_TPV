#ifndef  _H_ObjetoPG_H_

#include "SDL.h"
#include "JuegoPG.h"
#include "ObjetoJuego.h"


class ObjetoPG : public ObjetoJuego
{

public:
	
	ObjetoPG(JuegoPG * juego, int x, int y, Texturas_t t_textura);
	virtual ~ObjetoPG();

	JuegoPG * obJuego;
	Texturas_t tipoTextura;

	SDL_Rect rect;
	int posX, posY;
	bool visible;
	virtual void draw();
	virtual void update() = 0;
	virtual bool onClick() = 0;

	bool dentro(int x, int y)const;

};

#endif