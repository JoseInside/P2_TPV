#include "JuegoPG.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include "GlobosPG.h"
#include <time.h>
#include "Mariposa.h"
#include "Premio.h"

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
	initObjetos();

	if (pWin == nullptr || pRender == nullptr || pTexture == nullptr) { 
		cout << " Fatal Error\n Press Enter";  cin.ignore();
		error = true;
	}
}


JuegoPG::~JuegoPG()
{
	freeObjetos();
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

bool JuegoPG::initObjetos(){

	srand(time(NULL));

	int x, y;
	int i;
	
	archText[0] = { "..\\bmps\\fondo.png" };
	archText[1] = { "..\\bmps\\globo.png" };
	archText[2] = { "..\\bmps\\mariposa.png" };
	archText[3] = { "..\\bmps\\premio.png" };
	
	/*
	//Para el fondo
	fondo = new TexturasSDL;
	fondo->load(pRender, archText[0]);
	*/

	//Cargamos las texturas (fondo, globos, mariposas y premio)
	for (int j = 0; j < archText.size(); ++j){

		pTexture = new TexturasSDL;
		pTexture->load(pRender, archText[j]);
		vTexturas.push_back(pTexture);
	}
	

	//Creamos la mariposa y la metemos en la primera posición del array
	x = rand() % 610;
	y = rand() % 420;
	ObjetoJuego* mariposa = new Mariposa(this, x, y, TMariposa);
	vObjetos.push_back(mariposa);

	for (i = 1; i < globosTotales; ++i){	
		x = rand() % 610;
		y = rand() % 420;
		ObjetoJuego* unGlobo = new GlobosPG(this, x, y, TGlobos);
		vObjetos.push_back(unGlobo);
	}
	
	//Creamos el premio y lo metemos en la última posición del array
	x = rand() % 610;
	y = rand() % 420;
	ObjetoJuego* premio = new Premio(this, x, y, TPremio);
	vObjetos.push_back(premio);


	if (i == vObjetos.size())
		return true;
	else return false;

}

void JuegoPG::freeObjetos() {
	
	for (int i = 0; i < vObjetos.size(); ++i)
		delete vObjetos[i];
	
	for (int j = 0; j < vTexturas.size(); ++j)
		delete vTexturas[j];
}


void JuegoPG::render() const{

	SDL_RenderClear(pRender);
	
	//Primero pintamos el fondo
	vTexturas[0]->draw(pRender,aux);

	for (int i = 1; i < vObjetos.size(); ++i){
		vObjetos[i]->draw();
	}

	SDL_RenderPresent(pRender);
}

void JuegoPG::onClick(int pmx, int pmy) {
	
	int i = vObjetos.size() - 1;
	//bool pinchado = false;
	px = pmx;
	py = pmy;

	while (i >= 0){
		vObjetos[i]->onClick();
			//pinchado = true;
		--i;
	}
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
	if (typeid(po) == typeid(GlobosPG)){
		--globos;
		if (globos == 0){
			gameOver = true;
		}
	}
	else if (typeid(po) == typeid(Mariposa)){
		dynamic_cast<Mariposa*>(po)->visible = false;
		dynamic_cast<Mariposa*>(po)->numClicks = 0;
		newPremio(po);
	}
	else if (typeid(po) == typeid(Premio)){
		dynamic_cast<Premio*>(po)->reinicia();
	}
}

void JuegoPG::newPuntos(ObjetoJuego * po){
	if (typeid(po) == typeid(GlobosPG)){
		
		puntos += dynamic_cast<GlobosPG*>(po)->valorGlobo;
	}
	else if (typeid(po) == typeid(Premio)){
		puntos += dynamic_cast<Premio*>(po)->PP;
	}
}

void JuegoPG::newPremio(ObjetoJuego* po){
	dynamic_cast<Premio*>(po)->visible = true;
}