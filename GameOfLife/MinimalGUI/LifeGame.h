#pragma once
#include "common.h"

#define MARGIN sf::Vector2f(25.f, 25.f)
#define MAX_UPDATE_TIME 3.f 
class GameLife
{
public:
	GameLife(sf::Vector2i _gridSize, float _updateTime = 1/20);
	~GameLife();

	void Init();
	void SetPause(bool _b);

	void SetLifePercent(float _f);
	void SetUdpdateTime(float _f);

	void Update(float _dt);
	void Draw(sf::RenderTarget& _render);
private:

	sf::Vector2i gridSize;
	sf::RectangleShape gridRect;
	sf::RectangleShape rect;
	sf::Vector2f cellSize;
	float updateTime;
	float lifePercent;
	float time;
	bool pause;
	std::vector<std::vector<bool>> cellAlive;
};