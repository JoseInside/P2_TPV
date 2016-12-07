#include "Premio.h"


Premio::Premio(JuegoPG * hereJuego, int x, int y, Texturas_t textura) : ObjetoPG(hereJuego, x, y, textura)
{
	visible = false;
	PP = 100;
}


Premio::~Premio()
{
}


bool Premio::onClick(){
	
	if (dentro(rect.x, rect.y)){
		obJuego->newPuntos(this);
		obJuego->newBaja(this);
		return true;
	}
	else return false;
}

void Premio::update(){
	//Disminuimos posibilidad de clickear
	numIntentos--;
	PP-= 20;
	if (numIntentos == 0){
		obJuego->newBaja(this);
	}
}

void Premio::reinicia(){
	visible = false;
	numIntentos = 3;
	PP = 100;
}