#include "window.h"
#include "mingw.thread.h"

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
class Game
{
private:
  bool quit;
  SDL_Renderer *renderer;
  Window* w;
  SDL_Window *window;
public:
  Game();
  int init();
  void run();
  void render();
  void menu();
};
