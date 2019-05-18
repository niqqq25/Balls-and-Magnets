#pragma once

#include "Engine.h"

class ObjectDisplay {

public:
	static SDL_Texture *texture(const char *pname);
	static void ImageDisplay(SDL_Texture* texture, SDL_Rect crop, SDL_Rect DestR);
};
