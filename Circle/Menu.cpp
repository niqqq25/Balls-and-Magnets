#include "Menu.h"

MainMenu::MainMenu(HandleEvents* handleEvents, GameMode *mode)
{
	cameraX = cameraY = 0;

	gameMode = mode;

	int buttonPos_Centre = (WINDOW_WIDTH - 337) / 2;
	startButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 200, 337, 138, "Start Game");
	loadButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 300, 337, 138, "Load Game");
	exitButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 400, 337, 138, "Quit Game");
	background = new Sprite("RandomSprites/background.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, &cameraX, &cameraY);

	mainMenu_name = new Text("Fonts/Pacifico.ttf", 50, "Ball game :)");
	mainMenu_name->loadFond();
}


MainMenu::~MainMenu()
{
	delete startButton;
	delete loadButton;
	delete exitButton;
	delete background;
}

void MainMenu::Update()
{
	startButton->Update();
	if (startButton->get_isClicked()) {
		*gameMode = GAMEPLAY;
	}
	loadButton->Update();
	if (loadButton->get_isClicked()) {
		*gameMode = LOAD_GAME;
	}
	exitButton->Update();
	if (exitButton->get_isClicked()) {
		*gameMode = QUIT_GAME;
	}
}

void MainMenu::Draw()
{
	background->Draw();
	mainMenu_name->Draw(275, 50);
	startButton->Draw();
	loadButton->Draw();
	exitButton->Draw();
}

PauseMenu::PauseMenu(HandleEvents * handleEvents, GameMode * mode)
{
	cameraX = cameraY = 0;

	gameMode = mode;

	int buttonPos_Centre = (WINDOW_WIDTH - 337) / 2;
	resumeButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 200, 337, 138, "Resume Game");
	saveButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 300, 337, 138, "Save Game");
	exitButton = new Button(handleEvents, "Buttons/button_case.png", buttonPos_Centre, 400, 337, 138, "Quit Game");
	background = new Sprite("RandomSprites/background.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, &cameraX, &cameraY);

	pauseMenu_text = new Text("Fonts/Pacifico.ttf", 50, "Game paused");
	pauseMenu_text->loadFond();
}

PauseMenu::~PauseMenu()
{
	delete resumeButton;
	delete saveButton;
	delete exitButton;
	delete background;
	delete pauseMenu_text;
}

void PauseMenu::Update()
{
	resumeButton->Update();
	if (resumeButton->get_isClicked()) {
		*gameMode = GAMEPLAY;
	}
	saveButton->Update();
	if (saveButton->get_isClicked()) {
		*gameMode = SAVE_GAME;
	}
	exitButton->Update();
	if (exitButton->get_isClicked()) {
		*gameMode = QUIT_GAME;
	}
}

void PauseMenu::Draw()
{
	background->Draw();
	pauseMenu_text->Draw(275, 50);
	resumeButton->Draw();
	saveButton->Draw();
	exitButton->Draw();
}

