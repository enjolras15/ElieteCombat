#pragma once
#include "EnemyPlane.h"
#include "EnemyBulletModel.h"
class EnemyBullet : public IGameObject
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Update();

	bool Start();

	Vector3 pos;
	Vector3 Front;
	Quaternion rot;
	int num;

private:
	EnemyPlane* enemyplane;
	int modelnum=-1;
	int count = 0;
	float spd = 30.0f;

	EnemyBulletModel* bulletModel;

};

