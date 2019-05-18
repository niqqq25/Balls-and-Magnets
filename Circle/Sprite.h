#pragma once
#include "ObjectDisplay.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>


class Sprite
{
public:
	Sprite(const char* spriteName, int x, int y, int width, int height, int *cameraPosX, int *cameraPosY);
	~Sprite();

	void Draw();
	void setCrop(int x, int y, int weight, int height);

	int getSpriteX() { return spriteParm.x; }
	int getSpriteY() { return spriteParm.y; }
	int getSpriteWidth() { return spriteParm.w; }
	int getSpriteHeight() { return spriteParm.h; }

private:
	int textureSizeWidth, textureSizeHeight;
	int *cameraPosX, *cameraPosY;
	SDL_Texture* texture;
	SDL_Rect spriteParm, spriteCrop;
};

class Text
{
public:
	Text(const char* font_path, int font_size, const char* message_text);
	~Text();
	SDL_Texture * loadFond();
	void Draw(int textPos_x, int textPos_y);
	void setColor(SDL_Color textColor);
	SDL_Rect getText_rect();

private:
	SDL_Texture* texture;
	TTF_Font* font;
	std::string textMsg;
	SDL_Color textColor;
	SDL_Rect text_rect;
};
