#pragma once
#include "EnemyPlane.h"
#include "EnemyFleet.h"
#include "Player.h"

class EnemyPlane;
class EnemyFleet;
class Player;
class Game;

class Stage : public IGameObject
{

public:
	Stage();
	~Stage();

	void Update();
	void Render(RenderContext& rc);

	float StageNumber = 0;
	long int wave = 0;
	wchar_t Text[256];

private:

	FontRender fontRender;
	EnemyPlane* enemy;
	EnemyFleet* enemyFleet;
	Player* player;
	Game* game;

};

