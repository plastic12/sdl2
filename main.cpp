#include "rapidxml.hpp"  
#include "rapidxml_utils.hpp"  
#include "rapidxml_print.hpp"  
#include "window.h"

using namespace rapidxml; 
using namespace std;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//const int TILE_SIZE =40;
int main(int argc,char** argv)
{

	//sdl img init
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}
	//sdl init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	//make window
	SDL_Window *window = SDL_CreateWindow("v1", 100, 100, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	//link renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
	GraphicLib::init(renderer);
	//xml analysis
	file<> xmlFile("texture.xml");
	xml_document<> doc;    // character type defaults to char
	doc.parse<0>(xmlFile.data());    // 0 means default parse flags
	xml_node <>*root=doc.first_node();
	Window w;
	xml_node<>*texture=root->first_node();
	//Layer
	Layer l0(stoi(texture->first_node("source_id")->value()),
	renderer,
	stoi(texture->first_node("x")->value()),
	stoi(texture->first_node("y")->value()));
	w.add(&l0);
	
	texture=texture->next_sibling();
	Layer l1(stoi(texture->first_node("source_id")->value()),
	renderer,
	stoi(texture->first_node("x")->value()),
	stoi(texture->first_node("y")->value()));
	w.add(&l1);
	//main loop init
	bool quit=false;
	SDL_Event e;
	
	//iW and iH are the clip width and height
	//We'll be drawing only clips so get a center position for the w/h of a clip
	
	int iW = 100, iH = 100;

	//Setup the clips for our image
	SDL_Rect clips[4];
	for (int i = 0; i < 4; ++i){
		clips[i].x = i / 2 * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
	}
	//Specify a default clip to start with
	int useClip = 0;
	
	//main loop
	
	while (!quit)
	{
		//logic
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym){
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
		}
		//render
		SDL_RenderClear(renderer);
		w.render(renderer);
		//l0.render(renderer);
		//renderTexture(l1.getTexture(), renderer, 0, 0, &clips[useClip]);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
	
	
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
	return 0;
	

}