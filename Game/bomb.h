#pragma once
#include"Player.h"
#include "BombModel.h"

class Bomb : public IGameObject
{
public:
	Bomb();
	~Bomb();

	void Update();

	Vector3 pos;

private:
	int num;
	float accel = 0.0f;
	Player* player;
	BombModel* model;
	EffectEmitter* effectEmitter;
};

