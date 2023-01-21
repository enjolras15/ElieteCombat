#pragma once
#include "EnemyFleetModel.h"
class EnemyFleet : public IGameObject
{
public:
	EnemyFleet();
	~EnemyFleet();

	void Update();
	Vector3 pos;
	int HP;

	int num;

private:

	int coolDown = 100;
	
	int type = 0;

	EnemyFleetModel* model;

	EffectEmitter* effectEmitter;

	void Death();

	void Shot();

};

