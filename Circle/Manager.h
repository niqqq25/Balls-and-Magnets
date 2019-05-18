#pragma once

#include <vector>
#include "Collision.h"
#include <memory>
#include <fstream>
#include <string>

template <class T>
class Manager {
public:
	Manager();
	~Manager();
	void CreateNewObject(HandleEvents *handleevents, int centrePosX, int centrePosY, int radius);
	void DeleteObject(int index);
	void Draw();
	bool isPossibleCreateNew(HandleEvents* handleevnts, int radius);
	void ChangeObjectStatus();

	std::unique_ptr<T>& getObject(int index) { return object[index]; }
	int getObjectAmmount() { return object.size(); }

protected:
	std::vector<std::unique_ptr<T>> object;
};


class BallManager : public Manager<Ball>
{
public:
	BallManager();
	~BallManager() {};

	void CreateNewObjectFromLoad(HandleEvents *handleevents, float centrePosX, float centrePosY, float velocityX, float velocityY, float radius, SDL_Color color);
	void SaveToFile(std::ofstream &fileName, const char* keyWord);
	void LoadFromFile(HandleEvents *handleevents, std::ifstream &fileName, const char* keyWord);
	void UpdateBall(HandleEvents *handleevents);
	void DrawBall();

	void CheckForTwoBallCollision(Ball &obj, int begin);

private:
	Collision *collision;
};


class AttractorManager : public Manager<Attractor> 
{
public:
	void CreateNewObjectFromLoad(HandleEvents *handleevents, float centrePosX, float centrePosY, float radius, SDL_Color color);
	void SaveToFile(std::ofstream &fileName, const char* keyWord);
	void LoadFromFile(HandleEvents *handleevents, std::ifstream &fileName, const char* keyWord);
	AttractorManager();
	~AttractorManager();

	void UpdateAttractor(HandleEvents *handleevents);
	void DrawAttractor();
};