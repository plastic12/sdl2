#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include"game.h"

using namespace rapidxml;
using namespace std;




int main(int argc,char** argv)
{
  Game g;
  g.init();
  g.run();
  //thread f(Game::render,g);
  //f.join();


  return 0;
}
/*
int gui(bool* quit)
{

	//main loop init
	SDL_Event e;

	//iW and iH are the clip width and height

  int iW = 100, iH = 100;
  SDL_Rect clips[4];
  for (int i = 0; i < 4; ++i){
    clips[i].x = i / 2 * iW;
    clips[i].y = i % 2 * iH;
    clips[i].w = iW;
    clips[i].h = iH;
  }
  int useClip=0;
	//We'll be drawing only clips so get a center position for the w/h of a clip
	//main loop

	while (!*quit)
	{
		//logic
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				*quit = true;
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym){
					case SDLK_ESCAPE:
						*quit = true;
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
*/
