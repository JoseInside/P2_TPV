#include "JuegoPG.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include "GlobosPG.h"
#include <time.h>

using namespace std;

JuegoPG::JuegoPG()
{  
	puntos = 0;
	gameOver = false;
	error = false;
	exit = false;
	pausa = false;
	globos = globosTotales;

	aux.x = 0;
	aux.y = 0;
	aux.h = SCREEN_HEIGHT;
	aux.w = SCREEN_WIDTH;

	initSDL();
	initGlobos();

	if (pWin == nullptr || pRender == nullptr || pTexture == nullptr) { 
		cout << " Fatal Error\n Press Enter";  cin.ignore();
		error = true;
	}
}


JuegoPG::~JuegoPG()
{
	freeGlobos();
	closeSDL();
}


void JuegoPG::run() {

	

	if (!error) {
		Uint32 MSxUpdate = 500;
		cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_event();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"EL PINCHA GLOBOS", "Preparado?\n Pulsa 'OK' cuando estes listo!", nullptr);
		while (!exit && !gameOver) {
			
			srand(SDL_GetTicks());

			if (SDL_GetTicks() - lastUpdate >= MSxUpdate) {
				// while (elapsed >= MSxUpdate) 
				update();
				lastUpdate = SDL_GetTicks();
			}
			render();
			handle_event();
			if (globos == 0)
				gameOver = true;
		}
		if (exit) cout << "EXIT \n";
		else {
 			string m = {"Has obtenido: " + to_string(puntos) + " puntos!\n Gracias por jugar!"};

			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"EL PINCHA GLOBOS", m.c_str(), nullptr);
			cout << "Has obtenido " << puntos << " puntos\n";
		}
		SDL_Delay(1000); 
	}
}

bool JuegoPG::initSDL(){
	
	bool success = true; //Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWin = SDL_CreateWindow("GLOBOS_TPV ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pWin == nullptr){
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRender = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRender == nullptr){
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	return success;
}

void JuegoPG::closeSDL () {

	SDL_DestroyRenderer(pRender);
	pRender = nullptr;

	SDL_DestroyWindow(pWin);
	pWin = nullptr;

	SDL_Quit();
}

bool JuegoPG::initGlobos(){

	/*
	----------------------------------------------------------
	Implementación para mostrar globos de diferentes texturas
						(SIN TERMINAR)
	----------------------------------------------------------

	string nombArch[3];
	nombArch[0] = { "..\\bmps\\globo.png" };
	nombArch[1] = { "..\\bmps\\globo2.png" };
	nombArch[2] = { "..\\bmps\\globo3.png" };

	for (int j = 0; j < 3; ++j) {
		pTexture->load(pRender, nombArch[j]);
		vTexturas.push_back(pTexture);
	}
	*/

	int x, y;
	int i;
	srand(time(NULL));
	
	for (i = 0; i < globosTotales; ++i){
		
		x = rand() % 610;
		y = rand() % 420;
		//int globoElegido = rand() % 3;	//Elegimos una textura de globo distinta al azar y se la ponemos a un globo determinado.
		GlobosPG* unGlobo = new GlobosPG(vTexturas[0], x, y);
		vObjetos.push_back(unGlobo);
	}
	
	
	 

	if (i == vGlobos.size())
		return true;
	else return false;

}

void JuegoPG::freeGlobos() {
	for (int i = 0; i < vGlobos.size(); ++i)
		delete vGlobos[i];
	
	for (int j = 0; j < vTexturas.size(); ++j)
		delete vTexturas[j];
}

void JuegoPG::initMedia(){


	//Para el fondo
	fondo = new TexturasSDL;
	string nombFondo = { "..\\bmps\\fondo.png" };
	fondo->load(pRender, nombFondo);

	//Para los globos
	pTexture = new TexturasSDL;
	string nombrGlobo = { "..\\bmps\\globo.png" };

	pTexture->load(pRender, nombrGlobo);
	vTexturas.push_back(pTexture);

	string nombrMariposa = { "url_mariposa" };
	string nombrPremio = { "url_premio" };

}

void JuegoPG::freeMedia(){
	delete fondo;
	delete pTexture;
}


void JuegoPG::render() const{


	SDL_RenderClear(pRender);
	
	//Primero pintamos el fondo
	fondo->draw(pRender,aux);

	for (int i = 0; i < vGlobos.size(); ++i){
		vGlobos[i]->draw(pRender);
	}

	SDL_RenderPresent(pRender);
}

void JuegoPG::onClick(int pmx, int pmy) {
	
	int i = vObjetos.size() - 1;
	bool pinchado = false;
	px = pmx;
	py = pmy;

	while (i >= 0 && !pinchado){
		if (vObjetos[i]->onClick()){
			globos--;
			puntos += vGlobos[i]->valorGlobo;
			pinchado = true;
		}
		--i;
	}

	/* !! IMPLEMENTACIÓN ANTES DE EVALUACIÓN !!
	for (int i = 0; i < vGlobos.size(); ++i){
		if (vGlobos[i]->onClick(pmx, pmy)){
			globos--;
			puntos+= vGlobos[i]->valorGlobo;
			vGlobos[i]->visible = false;
			vGlobos[i]->muerto = true;
		}
	}
	*/
}
void JuegoPG::getMousePos(int & mpx, int & mpy) const{
	
	if (px == -1 || py == -1){
		cout << "Error: mouse position not defined" << "\n";
	}
	else{
		mpx = px;
		mpy = py;
	}
}

void JuegoPG::update() {
	
	if (!pausa)
	{
		for (int i = 0; i < vObjetos.size(); ++i){
			vObjetos[i]->update();
				//globos--;
		}
	}
}

void JuegoPG::handle_event(){
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) exit = true;
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				cout << "CLICK\n";
				onClick(e.button.x, e.button.y);
			}
		}
		if (e.type == SDL_KEYUP){
			if (e.key.keysym.sym == SDLK_p)
				pausa = !pausa;
		}
	}
}

void JuegoPG::newBaja(ObjetoJuego* po){
	delete po;
}

void JuegoPG::newPuntos(ObjetoJuego * po){

}

void JuegoPG::newPremio(ObjetoJuego* po){

}