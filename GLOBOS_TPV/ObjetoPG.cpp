#include "ObjetoPG.h"


//Constructora
ObjetoPG::ObjetoPG(JuegoPG * juego, int x, int y, Texturas_t t_textura){
	
	obJuego = juego;
	tipoTextura = t_textura;
	rect.x = posX = x;
	rect.y = posY = y;
}

// x/y = Click del ratón (coordenadas)   --   se comprueba si el click está dentro de los límites del rect
// de textura
bool ObjetoPG::dentro(int x, int y)const {
	
	return ((rect.x <= x) && x <= (rect.x + rect.w) && (rect.y <= y) && y <= (rect.y + rect.h));
	
}

void ObjetoPG::draw() {
	if (visible){
		obJuego->getTextura(tipoTextura)->draw(obJuego->getRender(), rect);
	}
}
