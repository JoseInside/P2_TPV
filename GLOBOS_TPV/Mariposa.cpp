#include "Mariposa.h"


Mariposa::Mariposa(JuegoPG * hereJuego, int x, int y, Texturas_t textura) : ObjetoPG(hereJuego, x, y, textura)
{
	visible = true;
}

Mariposa::~Mariposa()
{
}

bool Mariposa::onClick(){
	
	if (dentro(rect.x, rect.y)){
		//Aumentamos los clicks en uno
		numClicks++;
		posX = rand() % 610;
		posY = rand() % 420;

		if (numClicks == 3){
			obJuego->newBaja(this);
		}
		return true;
	}
	else return false;
}
void Mariposa::update(){
	
	if (visible){
		//animacion
	}
}