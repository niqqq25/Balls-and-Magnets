#pragma once

#include "SDL.h"

class HandleEvents
{
public:
	HandleEvents();
	~HandleEvents();

	void Update();

	void checkForQuit();

	bool get_isQuit();
	bool isPaused();

	void checkForButtonClick();
	void checkForMouseButtonClick();

	bool get_isButtonClicked() { return isButtonClicked; }

	bool isLeftMouseButtonClicked();
	bool isRightMouseButtonClicked();

	SDL_Point mousePos() { return {event.button.x, event.button.y}; }
	SDL_Event get_event();

private:
	bool isButtonClicked, isButtonPushed;
	bool isMouseButtonClicked, isMouseButtonPushed;
	SDL_Event event;
	bool isQuit;
};
