#include "Circle.h"
#include "Engine.h"

void CircleParm::Init(HandleEvents * handleevents, float centrePosX, float centrePosY, int radius)
{
	this->radius = radius;
	this->handleevents = handleevents;
	this->centrePosX = centrePosX;
	this->centrePosY = centrePosY;
}

bool CircleParm::isHitboxTriggered(bool isForNewCircle) const
{
	int mouseX = handleevents->mousePos().x;
	int mouseY = handleevents->mousePos().y;

	if (Formulas::Distance(mouseX, centrePosX, mouseY, centrePosY) <= radius * (isForNewCircle + 1)) {
		return true;
	}
	return false;
}

void CircleParm::setColor()
{
	uint8_t r = Random::RandNumberGen(0, 255);
	uint8_t g = Random::RandNumberGen(0, 255);
	uint8_t b = Random::RandNumberGen(0, 255);
	uint8_t a = Random::RandNumberGen(0, 255);

	color = { r, g, b, a };
}

void CircleParm::setCircleState(CircleState circleState)
{
	this->circleState = circleState;
}





Ball::Ball(HandleEvents *handleevents, float centrePosX, float centrePosY, float radius)
{
	setColor();
	circleState = NEW;
	Init(handleevents, centrePosX, centrePosY, radius);
	velocityX = Random::RandNumberGen(-1, 1);
	velocityY = Random::RandNumberGen(-1, 1);
}

Ball::Ball(HandleEvents *handleevents, float centrePosX, float centrePosY, float velocityX, float velocityY, float radius, SDL_Color color)
{
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	this->color = color;
	circleState = ALIVE;
	Init(handleevents, centrePosX, centrePosY, radius);
}

Ball::~Ball(){}

void Ball::Update()
{
	if (handleevents->isLeftMouseButtonClicked()) {
		if (isHitboxTriggered(false) && circleState != NEW) {
			circleState = DEAD;
		}
	}
	SpeedLimitation();
	Movement();
}

void Ball::Draw()
{
	SDL_SetRenderDrawColor(Engine::renderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++) {
		for (int h = 0; h < radius * 2; h++) {
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius)) {
				SDL_RenderDrawPoint(Engine::renderer, centrePosX + dx, centrePosY + dy);
			}
		}
	}
}

void Ball::Movement()
{
	centrePosX += velocityX;
	centrePosY += velocityY;
}

void Ball::SpeedLimitation()
{
	if (velocityX > 2) velocityX = 2;
	if (velocityY > 2) velocityY = 2;
	if (velocityX < -2) velocityX = -2;
	if (velocityY < -2) velocityY = -2;
}




Attractor::Attractor(HandleEvents * handleevents, int centrePosX, int centrePosY, int radius)
{
	circleState = NEW;
	Init(handleevents, centrePosX, centrePosY, radius);
	setColor();
}

Attractor::Attractor(HandleEvents * handleevents, int centrePosX, int centrePosY, int radius, SDL_Color color)
{
	this->color = color;
	circleState = ALIVE;
	Init(handleevents, centrePosX, centrePosY, radius);
}

Attractor::~Attractor(){}

void Attractor::Update()
{
	if (handleevents->isRightMouseButtonClicked()) {
		if (isHitboxTriggered(false) && circleState != NEW) {
			circleState = DEAD;
		}
	}
}

void Attractor::Draw()
{
	SDL_SetRenderDrawColor(Engine::renderer, color.r, color.g, color.b, color.a);
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int err = tx - (radius << 1);

	while (x >= y)
	{
		SDL_RenderDrawPoint(Engine::renderer, centrePosX + x, centrePosY - y);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX + x, centrePosY + y);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX - x, centrePosY - y);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX - x, centrePosY + y);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX + y, centrePosY - x);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX + y, centrePosY + x);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX - y, centrePosY - x);
		SDL_RenderDrawPoint(Engine::renderer, centrePosX - y, centrePosY + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}
