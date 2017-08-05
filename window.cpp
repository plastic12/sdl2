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

Layer::Layer(int source_id, SDL_Renderer *ren,int x,int y,string name)
{
	isRender=true;
	this->name=name;
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
void Layer::toggleRender()
{
	isRender=!isRender;
}
bool Layer::getRender(){return isRender;}
string Layer::getName(){return name;}
Layer::~Layer()
{
	cout<<"Layer destroy"<<endl;
}
SDL_Texture *Layer::getTexture(){return tex;}

Window::Window()
{}
void Window::add(Layer* l)
{
	layers.push_back(l);
}
string Window::getName(int index)
{
	if(index>=layers.size())
	{
		cout<<"index out of bound";
		return "";
	}
	return layers[index]->getName();
}
void Window::render(SDL_Renderer *ren)
{
	for(int i=0;i<layers.size();i++)
	{
		if(layers[i]->getRender())
			layers[i]->render(ren);
	}
}
int Window::getSize()
{return layers.size();}
bool Window::getRender(int index)
{
	return layers[index]->getRender();
}
void Window::render(SDL_Renderer *ren,int index)
{
	layers[index]->render(ren);
}
void Window::toggleRender(int index)
{
	layers[index]->toggleRender();
}
