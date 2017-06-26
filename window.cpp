#include "window.h"


vector<SDL_Texture *> GraphicLib::lib;
const string GraphicLib::init_file="graphics.xml";

void GraphicLib::add(const std::string &file, SDL_Renderer *ren)
{
	lib.push_back(loadTexture(file,ren));
}
SDL_Texture* GraphicLib::get(int index)
{
	if(index<0||index>lib.size())
		return NULL;
	else
		return lib[index];
}

void GraphicLib::init(SDL_Renderer *ren)
{
	file<> xmlFile(init_file.c_str());
	xml_document<> doc;    // character type defaults to char
	doc.parse<0>(xmlFile.data());    // 0 means default parse flags
	xml_node <>*root=doc.first_node();
	for(xml_node<>*texture=root->first_node();texture;texture=texture->next_sibling())
	{
		string filename=texture->first_node("source")->value();
		add(filename,ren);
	}
}

Layer::Layer(int source_id, SDL_Renderer *ren,int x,int y)
{
	//std::cout<<file<<'\n';
	//std::cout<<ren<<'\n';
	tex=GraphicLib::get(source_id);
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
