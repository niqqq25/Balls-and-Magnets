#pragma once
#include "Button.h"
#include "HandleEvents.h"

class MainMenu
{
public:
	MainMenu(HandleEvents* handleEvents, GameMode *mode);
	~MainMenu();

	void Update();
	void Draw();

private:
	GameMode *gameMode;
	Button *startButton;
	Button *loadButton;
	Button *exitButton;

	Sprite *background;
	Text *mainMenu_name;
	int cameraX, cameraY;
};

class PauseMenu
{
public:
	PauseMenu(HandleEvents* handleEvents, GameMode *mode);
	~PauseMenu();

	void Update();
	void Draw();

private:
	GameMode *gameMode;
	Button *resumeButton;
	Button *saveButton;
	Button *exitButton;

	Sprite *background;
	Text *pauseMenu_text;
	int cameraX, cameraY;
};