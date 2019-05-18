#include "Manager.h"


template<class T>
inline Manager<T>::Manager()
{
}

template<class T>
inline Manager<T>::~Manager()
{
}

template<class T>
void Manager<T>::CreateNewObject(HandleEvents * handleevents, int centrePosX, int centrePosY, int radius)
{
	object.emplace_back(std::make_unique<T>(handleevents, centrePosX, centrePosY, radius));
}

template<class T>
void Manager<T>::DeleteObject(int index)
{
	object.erase(object.begin() + index);
}

template<class T>
void Manager<T>::Draw()
{
	for (auto& obj : object) {
		obj->Draw();;
	}
}

template<class T>
bool Manager<T>::isPossibleCreateNew(HandleEvents * handleevnts, int radius)
{
	for (auto& obj : object) {
		if (obj->isHitboxTriggered(true)) {
			return false;
		}
	}
	if(handleevnts->mousePos().x - radius <= 0 || handleevnts->mousePos().x + radius >= WINDOW_WIDTH 
		|| handleevnts->mousePos().y - radius <= 0 || handleevnts->mousePos().y + radius >= WINDOW_HEIGHT){
		return false;
	}
	return true;
}

template<class T>
void Manager<T>::ChangeObjectStatus()
{
	for (auto& obj : object) {
		if (obj->getCircleState() == NEW) {
			obj->setCircleState(ALIVE);
		}
	}
}



BallManager::BallManager()
{
	collision = new Collision();
}

void BallManager::CreateNewObjectFromLoad(HandleEvents * handleevents, float centrePosX, float centrePosY, float velocityX, float velocityY, float radius, SDL_Color color)
{
	object.emplace_back(std::make_unique<Ball>(handleevents, centrePosX, centrePosY, velocityX, velocityY, radius, color));
}

void BallManager::SaveToFile(std::ofstream & fileName, const char* keyWord)
{
	for (auto& obj : object) {
		fileName << keyWord << ' ';
		fileName << obj->getCentrePosX() << ' ' << obj->getCentrePosY() << ' ' << obj->getVelocityX() << ' '
			<< obj->getVelocityY() << ' ' << (int) obj->getColor().r << ' ' << (int) obj->getColor().g << ' ' <<
			(int) obj->getColor().b << ' ' << (int) obj->getColor().a << "\n";
	}
	fileName << "#" << "\n";
}

void BallManager::LoadFromFile(HandleEvents *handleevents, std::ifstream & fileName, const char * keyWord)
{
	std::string indicator;
	float centrePosX, centrePosY, velocityX, velocityY;
	int color1, color2, color3, color4;
	SDL_Color color;

	while (fileName >> indicator) {
		if (indicator == keyWord) {

			fileName >> centrePosX >> centrePosY >> velocityX >> velocityY >> color1 >> color2 >> color3 >> color4;

			color = { (uint8_t)color1, (uint8_t)color2 , (uint8_t)color3, (uint8_t)color4 };

			CreateNewObjectFromLoad(handleevents, centrePosX, centrePosY, velocityX, velocityY, BALL_SIZE, color);

		}
		else { break; }
	}
}

void BallManager::UpdateBall(HandleEvents *handleevents)
{
	ChangeObjectStatus();
	if(handleevents->isLeftMouseButtonClicked() && isPossibleCreateNew(handleevents, BALL_SIZE)) {
		CreateNewObject(handleevents, handleevents->mousePos().x, handleevents->mousePos().y, BALL_SIZE);
	}

	int i = 0;
	for (auto& obj : object) {

		obj->Update();

		if (obj->getCircleState() == DEAD) {
			DeleteObject(i);
			break;
		}
		else { i++; }
		CheckForTwoBallCollision(*obj, i);
		collision->ElasticCollesionWithWall(*obj);
	}
}

void BallManager::DrawBall()
{
	Draw();
}

void BallManager::CheckForTwoBallCollision(Ball &obj, int begin)
{
	for (auto it = object.begin() + begin; it != object.end(); it++) {
		
		float distance = Formulas::Distance(obj.getCentrePosX(), (*it)->getCentrePosX(), obj.getCentrePosY(), (*it)->getCentrePosY());

		if (distance <= BALL_SIZE * 2) {

			collision->DisplacementOfTwoBalls(*(*it), obj, distance);
			collision->ElasticTwoBallCollision(*(*it), obj);
			break;
		}
	}
}


void AttractorManager::CreateNewObjectFromLoad(HandleEvents * handleevents, float centrePosX, float centrePosY, float radius, SDL_Color color)
{
	object.emplace_back(std::make_unique<Attractor>(handleevents, centrePosX, centrePosY, radius, color));
}

void AttractorManager::SaveToFile(std::ofstream & fileName, const char * keyWord)
{
	for (auto& obj : object) {
		fileName << keyWord << ' ';
		fileName << obj->getCentrePosX() << ' ' << obj->getCentrePosY() << ' ' << ' ' << (int)obj->getColor().r << ' '
			<< (int)obj->getColor().g << ' ' << (int)obj->getColor().b << ' ' << (int)obj->getColor().a << "\n";
	}
}

void AttractorManager::LoadFromFile(HandleEvents * handleevents, std::ifstream & fileName, const char * keyWord)
{
	std::string indicator;
	float centrePosX, centrePosY;
	int color1, color2, color3, color4;
	SDL_Color color;

	while (fileName >> indicator) {

		if (indicator == keyWord) {

			fileName >> centrePosX >> centrePosY >> color1 >> color2 >> color3 >> color4;

			color = { (uint8_t)color1, (uint8_t)color2 , (uint8_t)color3, (uint8_t)color4 };

			CreateNewObjectFromLoad(handleevents, centrePosX, centrePosY, ATTRACTOR_SIZE, color);

		}
		else { break; }
	}
}

AttractorManager::AttractorManager()
{}

AttractorManager::~AttractorManager(){}

void AttractorManager::UpdateAttractor(HandleEvents * handleevents)
{
	ChangeObjectStatus();
	if (handleevents->isRightMouseButtonClicked() && isPossibleCreateNew(handleevents, ATTRACTOR_SIZE)) {
		CreateNewObject(handleevents, handleevents->mousePos().x, handleevents->mousePos().y, ATTRACTOR_SIZE);
	}

	int i = 0;
	for (auto& obj : object) {

		obj->Update();

		if (obj->getCircleState() == DEAD) {
			DeleteObject(i);
			break;
		}
		else { i++; }
	}
}

void AttractorManager::DrawAttractor()
{
	Draw();
}

