#pragma once

#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BALL_SIZE 10
#define ATTRACTOR_SIZE 20
#define ATTRACTOR_POWER 1
#define ATTRACTOR_RANGE 200

#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Vector2D {
	float x;
	float y;
};

namespace Random {

	void RandSeedInit();
	int RandNumberGen(int minNumber, int maxNumber);
}

namespace Formulas {

	float Distance(int x1, int x2, int y1, int y2);
	float Distance(int averageX, int everageY);
}

namespace Vector {

	Vector2D unitVector(Vector2D normalVector);
	float dotProduce(Vector2D firstVector, Vector2D secondVector);
	Vector2D scalarMultiplication(float primeNum, Vector2D vect);
	Vector2D Gravity(Vector2D normalVector);


}
