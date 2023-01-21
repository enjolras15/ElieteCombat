#pragma once
#include "bullet.h"
#include "EnemyPlaneModel.h"

class EnemyPlane : public IGameObject
{
public:

	EnemyPlane();
	~EnemyPlane();

	void Update();

	int num=0;

	int HP = 0;

	Vector3 pos;
	Quaternion rot;

	float Xrad=0;
	float Zrad=0;

	Vector3 Front;

	Vector3 moveDir;

	EnemyPlaneModel* model;

private: 

	float spd = 10.0f;

	int coolDown = 0;

	void Death();

	void Shot();

	EffectEmitter* effectEmitter;

	const float criterion_height = 8000.0f;

};

