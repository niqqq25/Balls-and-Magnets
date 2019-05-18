#include "Collision.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::ElasticCollesionWithWall(Ball & object)
{
	if (object.getCentrePosX() + object.getRadius() >= WINDOW_WIDTH) {

		object.setVelocityX(-abs(object.getVelocityX()));
	}
	else if (object.getCentrePosX() - object.getRadius() <= 0) {

		object.setVelocityX(abs(object.getVelocityX()));
	}
	else if (object.getCentrePosY() + object.getRadius() >= WINDOW_HEIGHT) {

		object.setVelocityY(-abs(-object.getVelocityY()));
	}
	else if (object.getCentrePosY() - object.getRadius() <= 0) {
		object.setVelocityY(abs(object.getVelocityY()));
	}
}

void Collision::ElasticTwoBallCollision(Ball & object1, Ball & object2)
{
	Vector2D normalVector = { object2.getCentrePosX() - object1.getCentrePosX(), object2.getCentrePosY() - object1.getCentrePosY() };
	Vector2D unitVector = Vector::unitVector(normalVector);
	Vector2D unitTangentVector = { -unitVector.y, unitVector.x };

	Vector2D velocity1 = { object1.getVelocityX(), object1.getVelocityY() };
	Vector2D velocity2 = { object2.getVelocityX(), object2.getVelocityY() };

	float v1n = Vector::dotProduce(unitVector, velocity1);
	float v1t = Vector::dotProduce(unitTangentVector, velocity1);
	float v2n = Vector::dotProduce(unitVector, velocity2);
	float v2t = Vector::dotProduce(unitTangentVector, velocity2);

	float momentum1 = v2n;
	float momentum2 = v1n;

	object1.setVelocityX(unitTangentVector.x * v1t + unitVector.x * momentum1);
	object1.setVelocityY(unitTangentVector.y * v1t + unitVector.y * momentum1);
	object2.setVelocityX(unitTangentVector.x * v2t + unitVector.x * momentum2);
	object2.setVelocityY(unitTangentVector.y * v2t + unitVector.y * momentum2);
}

void Collision::DisplacementOfTwoBalls(Ball & object1, Ball & object2, float distance)
{
	float overlap = 0.5f * (distance - object1.getRadius() - object2.getRadius());

	float dx = overlap * (object1.getCentrePosX() - object2.getCentrePosX()) / distance; //first ball
	float dy = overlap * (object1.getCentrePosY() - object2.getCentrePosY()) / distance;
	object1.setCentrePosX(object1.getCentrePosX() - dx);
	object1.setCentrePosY(object1.getCentrePosY() - dy);

	dx = overlap * (object1.getCentrePosX() - object2.getCentrePosX()) / distance; //second ball
	dy = overlap * (object1.getCentrePosY() - object2.getCentrePosY()) / distance;
	object2.setCentrePosX(object2.getCentrePosX() + dx);
	object2.setCentrePosY(object2.getCentrePosY() + dy);
}
