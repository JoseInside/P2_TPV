#pragma once
#include "JuegoPG.h"
#include "ObjetoJuego.h"

class ObjetoPG : public ObjetoJuego
{
public:
	ObjetoPG();
	virtual ~ObjetoPG();

	JuegoPG * juego;
	JuegoPG::Texturas_t pTextura;

	bool dentro(int x, int y)const;

	virtual void draw();

	virtual void update();

	virtual bool onClick();


private:

};

