#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "JuegoPG.h"

GlobosPG::GlobosPG(JuegoPG * hereJuego)
{	
}


GlobosPG::~GlobosPG()
{
}


void GlobosPG::draw() const{
	if (visible){
		pTextura->draw(pRender, rect);
	}
}

bool GlobosPG::onClick(){

	if (visible && ObjetoPG::dentro(rect.x, rect.y)){
		//Explotamos el globo
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
			return false;
		}
		else return true;
	}
	else return true;
}