#include "ObjetoPG.h"


bool ObjetoPG::dentro(int x, int y)const {
	int posX, posY;
	juego->getMousePos(posX, posY);
	juego->getTextura(text);
	
	if ((x <= posX) && posX <= (x + text.w) && (y <= posY) && posY <= (y + text.h))
		return true;
	else return false;
}

void ObjetoPG::draw() {
	juego->getTextura(pTextura);
}

void ObjetoPG::update(){

}