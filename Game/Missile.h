#pragma once
#include"Player.h"
#include "hud.h"
#include "MissileModel.h"

class Missile : public IGameObject
{
public:
	Missile();
	~Missile();

	void Update();

	Vector3 pos;

private:

	int num;
	float spd = 30.0f;
	bool LockON = 0;

	Vector3 Front;
	Quaternion rot;
	Player* player;
	MissileModel* model;
	hud* Hud;
	EffectEmitter* effectEmitter;
};
