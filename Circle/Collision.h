#pragma once
#include "Circle.h"
#include <cmath>

class Collision
{
public:
	Collision();
	~Collision();
	void ElasticCollesionWithWall(Ball &object);
	void ElasticTwoBallCollision(Ball &object1, Ball &object2);
	void DisplacementOfTwoBalls(Ball &object1, Ball &object2, float distance);
};

