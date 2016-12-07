#pragma once
#include "GlobosPG.h"
#include "TexturasSDL.h"
#include <vector>
#include "ObjetoJuego.h"


enum Texturas_t { TFondo, TMariposa, TGlobos, TPremio };


class JuegoPG : public ObjetoJuego
{
public:
		
	JuegoPG();
	~JuegoPG();
	void run();
	bool error;
	
	vector <string> archText;

	TexturasSDL* getTextura(Texturas_t et) const { return vTexturas[et]; }
	SDL_Renderer* getRender() const { return pRender; };
	void getMousePos(int & mpx, int & mpy) const;
	
	void newBaja(ObjetoJuego* po); // Los objetos informarán al juego cuando causen baja
	void newPuntos(ObjetoJuego* po); // Los objetos informarán al juego cuando se obtengan puntos
	void newPremio(ObjetoJuego* po); // Los objetos informará al juego cuando se obtenga un premio

private:

	SDL_Rect aux;
	SDL_Window * pWin = nullptr;        //La ventana donde se mostrará el render
	SDL_Renderer * pRender = nullptr;   //Render
	TexturasSDL * pTexture = nullptr;   //La imagen (globos.png) que mostraremos por ventana
	TexturasSDL * fondo = nullptr;		//El fondo de pantalla en el juego


	int globos, puntos;
	bool exit, gameOver, pausa;
	int px = -1, py = -1;
	vector <ObjetoJuego*> vObjetos;
	vector <TexturasSDL*>  vTexturas;

	const int SCREEN_WIDTH = 640;   //Ancho de ventana
	const int SCREEN_HEIGHT = 480;  //Alto de ventana
	const int globosTotales = 5;	//Numero de globos que se dibujan (NG)
	
	void initMedia(); // carga las texturas en el vector de texturas (fuente y música)
	void freeMedia();

	bool initSDL();
	void closeSDL();
	bool initObjetos();
	void freeObjetos();
	void render() const;
	void onClick(int pmx, int pmy);
	void update();
	void handle_event();
};

