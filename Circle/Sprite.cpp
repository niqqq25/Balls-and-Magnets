#include "Sprite.h"


Sprite::Sprite(const char * spriteName, int x, int y, int width, int height, int *cameraPosX, int *cameraPosY)
{
	texture = ObjectDisplay::texture(spriteName);

	if (texture == NULL) {
		std::cout << "Cant load image from " << spriteName << std::endl;
	}

	spriteParm.y = y;
	spriteParm.x = x;
	spriteParm.w = width;
	spriteParm.h = height;

	this->cameraPosX = cameraPosX;
	this->cameraPosY = cameraPosY;

	SDL_QueryTexture(texture, NULL, NULL, &textureSizeWidth, &textureSizeHeight);
	spriteCrop.x = spriteCrop.y = 0;
	spriteCrop.w = textureSizeWidth;
	spriteCrop.h = textureSizeHeight;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
}

void Sprite::Draw()
{
	SDL_Rect tempRect;
	tempRect.w = spriteParm.w;
	tempRect.h = spriteParm.h;

	tempRect.x = spriteParm.x - *cameraPosX;
	tempRect.y = spriteParm.y - *cameraPosY;

	ObjectDisplay::ImageDisplay(texture, spriteCrop, tempRect);
}

void Sprite::setCrop(int x, int y, int weight, int height)
{
	spriteCrop.x = x;
	spriteCrop.y = y;
	spriteCrop.w = weight;
	spriteCrop.h = height;
}

Text::Text(const char * font_path, int font_size, const char * message_text)
{
	textColor = { 0, 0, 0 };
	textMsg = message_text;

	font = TTF_OpenFont(font_path, font_size);
}

SDL_Texture * Text::loadFond()
{
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, textMsg.c_str(), textColor);

	texture = SDL_CreateTextureFromSurface(Engine::renderer, text_surface);
	SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);

	SDL_FreeSurface(text_surface);

	return texture;
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
}

void Text::Draw(int textPos_x, int textPos_y)
{
	text_rect.x = textPos_x;
	text_rect.y = textPos_y;

	SDL_RenderCopy(Engine::renderer, texture, NULL, &text_rect);
}

void Text::setColor(SDL_Color textColor)
{
	this->textColor = textColor;
}

SDL_Rect Text::getText_rect()
{
	return text_rect;
}