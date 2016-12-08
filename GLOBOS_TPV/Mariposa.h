#pragma once
#include "SDL.h"
#include "ObjetoPG.h"


class Mariposa : public ObjetoPG
{
public:
	Mariposa(JuegoPG * hereJuego, int x, int y, Texturas_t textura);
	~Mariposa();

	int numClicks = 0;
	//virtual void draw() const;
	virtual bool onClick();
	virtual void update();
};

