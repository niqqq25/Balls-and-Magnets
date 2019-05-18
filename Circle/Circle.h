#pragma once

#include "HandleEvents.h"
#include "Utilities.h"

enum CircleState {
	NEW,
	ALIVE,
	DEAD
};

class CircleParm {
public:
	CircleParm() {};
	~CircleParm() {};

	void Init(HandleEvents *handleevents, float x, float y, int radius);
	bool isHitboxTriggered(bool isForNewCircle) const;

	int getRadius() { return radius; }
	float getCentrePosX() { return centrePosX; }
	float getCentrePosY() { return centrePosY; }
	CircleState getCircleState() { return circleState; }
	SDL_Color getColor() { return color; }

	void setColor();
	void setCircleState(CircleState circleState);
	void setCentrePosX(float x) { centrePosX = x; }
	void setCentrePosY(float y) { centrePosY = y; }

protected:
	CircleState circleState;
	HandleEvents *handleevents;
	SDL_Color color;
	float centrePosX, centrePosY;
	int radius;
};



class Ball : public CircleParm
{
public:
	Ball(HandleEvents *handleevents, float centrePosX, float centrePosY, float radius);
	Ball(HandleEvents *handleevents, float centrePosX, float centrePosY, float velocityX, float velocityY, float radius, SDL_Color color);

	~Ball();

	void Update();
	void Draw();
	void Movement();
	void SpeedLimitation();

	float getVelocityX() { return velocityX; }
	float getVelocityY() { return velocityY; }

	void setVelocityX(float velocityX) { this->velocityX = velocityX; }
	void setVelocityY(float velocityY) { this->velocityY = velocityY; }

private:
	float velocityX, velocityY;
};


class Attractor : public CircleParm 
{
public:
	Attractor(HandleEvents *handleevents, int centrePosX, int centrePosY, int radius);
	Attractor(HandleEvents *handleevents, int centrePosX, int centrePosY, int radius, SDL_Color color);

	~Attractor();
	void Update();
	void Draw();
};