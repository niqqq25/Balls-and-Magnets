#include "Button.h"

Button::Button(HandleEvents* handleevents, const char* buttonName, int x, int y, int width, int height, const char* text)
{
	mouseInput = handleevents;

	cameraPosX = cameraPosY = 0;

	button_Clicked = new Sprite(buttonName, x, y, width, height / 2, &cameraPosX, &cameraPosY);
	button_Clicked->setCrop(0, 69, 337, 69); // <-- Must be same size buttons

	button_Not_Clicked = new Sprite(buttonName, x, y, width, height / 2, &cameraPosX, &cameraPosY);
	button_Not_Clicked->setCrop(0, 0, 337, 69); // <-- Must be same size buttons

	button_text = new Text("Fonts/Pacifico.ttf", 30, text);
	button_text->loadFond();

	buttonState = BUTTON_NOT_CLICKED;

	buttonParm.x = x;
	buttonParm.y = y;
	buttonParm.w = width;
	buttonParm.h = height / 2;

	isClicked = false;
}

Button::~Button()
{
	delete button_Clicked;
	delete button_Not_Clicked;
	delete button_text;
}

void Button::Draw()
{
	int textPosX = buttonParm.x + (buttonParm.w - button_text->getText_rect().w) / 2;
	int textPosY = buttonParm.y + (buttonParm.h - button_text->getText_rect().h) / 2;

	if (buttonState == BUTTON_NOT_CLICKED) {
		button_Not_Clicked->Draw();
		button_text->Draw(textPosX, textPosY);
	}
	else if (buttonState == BUTTON_CLICKED) {
		button_Clicked->Draw();
		button_text->Draw(textPosX + 5, textPosY + 5); //text moves down
	}
}

void Button::Update()
{
	int mouseX = mouseInput->get_event().button.x;
	int mouseY = mouseInput->get_event().button.y;
	int buttonStartCoord_X = button_Clicked->getSpriteX();
	int buttonEndCoord_X = button_Clicked->getSpriteX() + button_Clicked->getSpriteWidth();
	int buttonStartCoord_Y = button_Clicked->getSpriteY();
	int buttonEndCoord_Y = button_Clicked->getSpriteY() + button_Clicked->getSpriteHeight();

	if (mouseX >= buttonStartCoord_X && mouseX <= buttonEndCoord_X && mouseY >= buttonStartCoord_Y && mouseY <= buttonEndCoord_Y) {
		if (mouseInput->get_event().type == SDL_MOUSEBUTTONDOWN) {
			buttonState = BUTTON_CLICKED;
		}
		else if (mouseInput->get_event().type == SDL_MOUSEBUTTONUP) {
			if (buttonState == BUTTON_CLICKED) {
				isClicked = true;
			}
			buttonState = BUTTON_NOT_CLICKED;
		}
	}
	else {
		isClicked = false;
		buttonState = BUTTON_NOT_CLICKED;
	}
}

bool Button::get_isClicked()
{
	return isClicked;
}