/***************************************************************
****************************************************************
				PRÁCTICA 2 - EL PINCHA GLOBOS
Integrantes: 
	José María Monreal González
	Nahikari Madrid Ferrer

Mejoras:
	- Cuadro de diálogo al inicio y fin de partida mostrando la puntuación del usuario
	- Fondo de pantalla a mostrar durante el juego

****************************************************************
****************************************************************
*/



#include "JuegoPG.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]){

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	JuegoPG juego;
	
	juego.run();
	
	return 0;
}