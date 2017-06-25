#include <iostream>
#include <string>
#include "cleanup.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,SDL_Rect *clip);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,SDL_Rect *clip);

