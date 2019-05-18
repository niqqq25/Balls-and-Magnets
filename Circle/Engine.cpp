#include "Engine.h"
#include "Menu.h"

MainMenu *mainmenu;
PauseMenu *pausemenu;

SDL_Renderer* Engine::renderer = nullptr;

Engine::Engine()
{
	const int FPS = 120;
	frameDelay = 1000 / FPS;

	isRunning = true;
}

Engine::~Engine()
{
}

bool Engine::Init(const char & windowTitle, int x, int y, int width, int height)
{
	int Init = SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(&windowTitle, x, y, width, height, 0);

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if (Init != 0 || window == NULL || TTF_Init() == -1) {

		return false;
	}

	Random::RandSeedInit();

	handleevents = new HandleEvents();

	mainmenu = new MainMenu(handleevents, &gameMode);
	pausemenu = new PauseMenu(handleevents, &gameMode);

	ballmanager = new BallManager();
	attractormanager = new AttractorManager();
	collision = new Collision();

	return true;
}

bool Engine::Run()
{
	if (Init(*"Balls and Attractors", WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT) == false) {
		return false;
	}

	gameMode = MAIN_MENU;

	while (isRunning && !handleevents->get_isQuit()) {

		frameStart = SDL_GetTicks();

		Update();
		Render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	Destroy();


	return true;
}

void Engine::Update()
{
	handleevents->Update();
	switch (gameMode)
	{
	case GAMEPLAY:
		if (handleevents->isPaused()) {
			gameMode = PAUSE_GAME;
		}
		ballmanager->UpdateBall(handleevents);
		attractormanager->UpdateAttractor(handleevents);
		BallAndAttractorInteraction();
		break;
	case MAIN_MENU:
		mainmenu->Update();
		break;
	case SAVE_GAME:
		Save();
		gameMode = GAMEPLAY;
		break;
	case PAUSE_GAME:
		pausemenu->Update();
		break;
	case QUIT_GAME:
		isRunning = false;
		break;
	case LOAD_GAME:
		Load();
		gameMode = GAMEPLAY;
		break;
	default:
		break;
	}
}

void Engine::Render()
{
	SDL_RenderClear(renderer);

	switch (gameMode)
	{
	case GAMEPLAY:
		attractormanager->DrawAttractor();
		ballmanager->DrawBall();
		break;
	case MAIN_MENU:
		mainmenu->Draw();
		break;
	case PAUSE_GAME:
		pausemenu->Draw();
		break;
	default:
		break;
	}

	SDL_SetRenderDrawColor(Engine::renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}

void Engine::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Engine::Save()
{
	std::ofstream saveFile("save.txt");
	if (!saveFile.is_open()) {
		std::cout << "Cant open file";
	}
	else {
		ballmanager->SaveToFile(saveFile, "ball");
		attractormanager->SaveToFile(saveFile, "attractor");
	}
	saveFile.close();
}

void Engine::Load()
{
	std::ifstream saveFile("save.txt");
	if (!saveFile.is_open()) {
		std::cout << "Cant open file";
	}
	else {
		ballmanager->LoadFromFile(handleevents, saveFile, "ball");
		attractormanager->LoadFromFile(handleevents, saveFile, "attractor");
	}
	saveFile.close();
}

void Engine::BallAndAttractorInteraction()
{
	for (int a = 0; a < ballmanager->getObjectAmmount(); a++) {
		for (int b = 0; b < attractormanager->getObjectAmmount(); b++) {

			float ballPosX = ballmanager->getObject(a)->getCentrePosX();
			float ballPosY = ballmanager->getObject(a)->getCentrePosY();
			float attractorPosX = attractormanager->getObject(b)->getCentrePosX();
			float attractorPosY = attractormanager->getObject(b)->getCentrePosY();

			float distance = Formulas::Distance(ballPosX, attractorPosX, ballPosY, attractorPosY);

			if (distance <= ATTRACTOR_RANGE) {
				Vector2D normalVector = { attractorPosX - ballPosX, attractorPosY - ballPosY};
				Vector2D unitVector = Vector::Gravity(normalVector);

				float velocityX = ballmanager->getObject(a)->getVelocityX();
				float velocityY = ballmanager->getObject(a)->getVelocityY();
				ballmanager->getObject(a)->setVelocityX(velocityX + unitVector.x * ATTRACTOR_POWER);
				ballmanager->getObject(a)->setVelocityY(velocityY + unitVector.y * ATTRACTOR_POWER);
			}
		}
	}
}
