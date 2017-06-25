#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cleanup.h"
#include <string>
#include "utility.h"

using namespace std;

class Layer
{
	private:
	SDL_Texture *tex;
	int x;
	int y;
	public:
	Layer(const std::string &file, SDL_Renderer *ren,int x,int y);
	void render(SDL_Renderer *ren);
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
};
