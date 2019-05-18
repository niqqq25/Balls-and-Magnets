#include "HandleEvents.h"
#include <iostream>

HandleEvents::HandleEvents()
{
	isQuit = false;
	isButtonClicked = isButtonPushed = false;
	isMouseButtonClicked = isMouseButtonPushed = false;
}

HandleEvents::~HandleEvents() {}

void HandleEvents::Update()
{
	SDL_PollEvent(&event);

	checkForButtonClick();
	checkForMouseButtonClick();

	checkForQuit();
}

void HandleEvents::checkForQuit()
{
	if (event.type == SDL_QUIT) {
		isQuit = true;
	}
}

bool HandleEvents::get_isQuit()
{
	return isQuit;
}

bool HandleEvents::isPaused()
{
	if (isButtonClicked && event.key.keysym.sym == SDLK_ESCAPE) {
		return true;
	}
	return false;
}

void HandleEvents::checkForButtonClick()
{
	isButtonClicked = false;

	if (event.type == SDL_KEYDOWN) {
		isButtonPushed = true;
	}
	if (event.type == SDL_KEYUP && isButtonPushed) {
		isButtonClicked = true;
		isButtonPushed = false;
	}
}

void HandleEvents::checkForMouseButtonClick()
{
	isMouseButtonClicked = false;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		isMouseButtonPushed = true;
	}
	if (event.type == SDL_MOUSEBUTTONUP && isMouseButtonPushed) {
		isMouseButtonClicked = true;
		isMouseButtonPushed = false;
	}
}

bool HandleEvents::isLeftMouseButtonClicked()
{
	if (isMouseButtonClicked && event.button.button == SDL_BUTTON_LEFT) {
		return true;
	}
	return false;
}

bool HandleEvents::isRightMouseButtonClicked()
{
	if (isMouseButtonClicked && event.button.button == SDL_BUTTON_RIGHT) {
		return true;
	}
	return false;
}

SDL_Event HandleEvents::get_event()
{
	return event;
}

