#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "JuegoPG.h"

GlobosPG::GlobosPG(JuegoPG * hereJuego, int x, int y, Texturas_t textura) : ObjetoPG(hereJuego, x, y,textura)
{	
	muerto = false;
}


GlobosPG::~GlobosPG()
{
}


bool GlobosPG::onClick(){

	if (visible && dentro(rect.x, rect.y)){
		//Explotamos el globo
		obJuego->newPuntos(this);
		obJuego->newBaja(this);
		muerto = true;
		return true;
	}
	else return false;


}
void GlobosPG::update(){

	if (!muerto) {
		if (rand() % 100 < PVIS)
			visible = true;
		else visible = false;
	}
	if (visible){

		if (rand() % 100 > PDES){
			rect.h -= DT;
			rect.w -= DT;
			valorGlobo += AP;
		}

		if (rect.h <= 0 || rect.w <= 0) {
			visible = false;
			muerto = true;
		}
	}
}