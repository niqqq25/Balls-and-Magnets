#include "Utilities.h"

void Random::RandSeedInit()
{
	srand(time(NULL));
}

int Random::RandNumberGen(int minNumber, int maxNumber)
{
	int generatedNum = (rand() % (maxNumber - minNumber + 1)) + minNumber;

	return generatedNum;
}

float Formulas::Distance(int x1, int x2, int y1, int y2)
{
	float d = sqrt((float)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

	return d;
}

float Formulas::Distance(int averageX, int everageY)
{
	float d = sqrt((float)(averageX * averageX + everageY * everageY));

	return d;
}

Vector2D Vector::unitVector(Vector2D normalVector)
{
	float distance = (float)Formulas::Distance(normalVector.x, normalVector.y);
	
	return {normalVector.x / distance, normalVector.y / distance};
}

Vector2D Vector::Gravity(Vector2D normalVector)
{
	float distance = (float)Formulas::Distance(normalVector.x, normalVector.y);

	return { normalVector.x / (distance * distance), normalVector.y / (distance * distance)};
}

float Vector::dotProduce(Vector2D firstVector, Vector2D secondVector)
{
	return firstVector.x * secondVector.x + firstVector.y * secondVector.y;
}

Vector2D Vector::scalarMultiplication(float primeNum, Vector2D vect)
{
	return {primeNum * vect.x, primeNum * vect.y};
}
