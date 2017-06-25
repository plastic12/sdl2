#include "window.h"


Layer::Layer(const std::string &file, SDL_Renderer *ren,int x,int y)
{
	//std::cout<<file<<'\n';
	//std::cout<<ren<<'\n';
	tex=loadTexture(file,ren);
	//std::cout<<tex<<'\n';
	if (tex == nullptr){
		SDL_Quit();
	}
	this->x=x;
	this->y=y;
}
void Layer::render(SDL_Renderer *ren)
{
	renderTexture(tex, ren, x, y,NULL);
}

Layer::~Layer()
{
}
SDL_Texture *Layer::getTexture(){return tex;}

Window::Window()
{}
void Window::add(Layer* l)
{
	layers.push_back(l);
}
void Window::render(SDL_Renderer *ren)
{
	for(int i=0;i<layers.size();i++)
	{
		layers[i]->render(ren);
	}
}
