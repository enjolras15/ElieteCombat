#pragma once
#include "EnemyFleet.h"
#include "EnemyBulletModel.h"
class EnemyFleetBullet : public IGameObject
{
public:
	EnemyFleetBullet();
	~EnemyFleetBullet();

	void Update();

	bool Start();

	Vector3 pos;
	Vector3 Front;
	Quaternion rot;
	int num;

private:
	int modelnum=-1;
	int count = 0;
	float spd = 30.0f;

	Vector3 diff;
	EnemyFleet* enemyfleet;
	EnemyBulletModel* bulletModel;

};

