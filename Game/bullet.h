#pragma once
#include "Player.h"
#include "BulletModel.h"

class Player;
class BulletModel;

class bullet : public IGameObject
{

public:
	bullet();
	~bullet();

	void Update();

	Vector3 pos;
	Quaternion rot;
	Player* player;
	BulletModel* bulletModel;

	Vector3 Front;

	int count=0;
	int num;

	float spd=30.0;


};