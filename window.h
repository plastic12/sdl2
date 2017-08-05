#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cleanup.h"
#include <string>
#include "utility.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class GraphicLib
{
	private:
	static const string init_file;
	static vector<SDL_Texture *> lib;
	public:
	static void add(const std::string &file, SDL_Renderer *ren);
	static SDL_Texture* get(int index);
	static void init(SDL_Renderer *ren);
};

class Layer
{
	private:
	string name;
	bool isRender;
	SDL_Texture *tex;
	int x;
	int y;
	public:
	Layer(int source_id, SDL_Renderer *ren,int x,int y,string name);
	void render(SDL_Renderer *ren);
	void toggleRender();
	bool getRender();
	string getName();
	~Layer();
	SDL_Texture * getTexture();
};


class Window
{
	private:
		vector<Layer*> layers;
	public:
		Window();
		void add(Layer* l);
		void render(SDL_Renderer *ren);
		void render(SDL_Renderer *ren,int index);
		string getName(int index);
		int getSize();
		bool getRender(int index);
		void toggleRender(int index);
};
