#pragma once
#include "SDL.h"
#include "TexturasSDL.h"

class GlobosPG : public ObjetoPG
{
public:
	
	//GlobosPG(TexturasSDL* img, int px, int py);
	GlobosPG(JuegoPG * hereJuego);
	~GlobosPG();

	TexturasSDL * pTextura = new TexturasSDL;
	SDL_Rect rect;
	//Textura_t pTextura = ObjetoPG::draw();

	bool visible, muerto;
	int valorGlobo;
	void draw() const;
	bool onClick();
	void update();

private:
	 
	static const int DT = 5;	// Disminución de tamaño
	static const int AP = 5;	// Aumento de puntos
	static const int PVIS = 70; // Probabilidad Visibles
	static const int PDES = 30; // Probabilidad Desinflados
};

