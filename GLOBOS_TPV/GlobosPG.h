#pragma once
#include "SDL.h"
#include "ObjetoPG.h"

class GlobosPG : public ObjetoPG
{
public:
	
	GlobosPG(JuegoPG * hereJuego, int x, int y, Texturas_t textura);
	~GlobosPG();

	//TexturasSDL * pTextura = new TexturasSDL;
	//SDL_Rect rect;
	//Textura_t pTextura = ObjetoPG::draw();

	bool muerto;
	int valorGlobo;

	virtual void draw() const;
	virtual bool onClick();
	virtual void update();

private:
	 
	static const int DT = 5;	// Disminución de tamaño
	static const int AP = 5;	// Aumento de puntos
	static const int PVIS = 70; // Probabilidad Visibles
	static const int PDES = 30; // Probabilidad Desinflados
};

