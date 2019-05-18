#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <vector>
#include "Manager.h"
#include <fstream>

#include <iostream>

enum GameMode {
	GAMEPLAY,
	MAIN_MENU,
	SAVE_GAME,
	PAUSE_GAME,
	QUIT_GAME,
	LOAD_GAME,
};

class Engine
{
public:
	Engine();
	~Engine();
	bool Init(const char &windowTitle, int x, int y, int width, int height);
	bool Run();
	void Update();
	void Render();
	void Destroy();
	void Save();
	void Load();
	void BallAndAttractorInteraction();


	static SDL_Renderer* renderer;
private:
	Collision *collision;
	HandleEvents *handleevents;
	BallManager *ballmanager;
	AttractorManager *attractormanager;
	Uint32 frameStart;
	int frameDelay, frameTime;
	GameMode gameMode;
	SDL_Window* window;
	bool isRunning;
};