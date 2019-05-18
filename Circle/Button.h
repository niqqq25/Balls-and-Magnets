#pragma once
#include "Sprite.h"
#include "HandleEvents.h"

enum ButtonState {
	BUTTON_CLICKED,
	BUTTON_NOT_CLICKED
};

class Button
{
public:
	Button(HandleEvents* handleevents, const char* buttonName, int x, int y, int width, int height, const char* text);
	~Button();

	void Draw();
	void Update();
	bool get_isClicked();

private:
	bool isClicked;
	SDL_Rect buttonParm;
	HandleEvents* mouseInput;
	Text * button_text;
	Sprite *button_Clicked;
	Sprite *button_Not_Clicked;
	int cameraPosX, cameraPosY;
	ButtonState buttonState;
};
