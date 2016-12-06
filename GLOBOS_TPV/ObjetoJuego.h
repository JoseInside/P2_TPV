#pragma once
#include "JuegoPG.h"
#include "ObjetoPG.h"
class ObjetoJuego
{
public:

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual bool onClick() = 0;
};

