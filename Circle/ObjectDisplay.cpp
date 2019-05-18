#include "ObjectDisplay.h"

SDL_Texture * ObjectDisplay::texture(const char *pname)
{
	SDL_Surface* surface = IMG_Load(pname);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}

void ObjectDisplay::ImageDisplay(SDL_Texture* texture, SDL_Rect crop, SDL_Rect DestR)
{
	SDL_RenderCopy(Engine::renderer, texture, &crop, &DestR); //<-- Change NULL
}