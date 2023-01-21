#include "stdafx.h"
#include "Missile.h"
#include "Enemyplane.h"
#include "EnemyFleet.h"
#include "MissileModel.h"

Missile::Missile() {

	model = FindGO<MissileModel>("missileModel");

	player = FindGO<Player>("Player");
	Front = player->Front;

	Hud = FindGO<hud>("hud");

	pos = player->pos;
	rot = player->rot;

	if (Hud->LockON == 1) LockON = 1;

	for (int i = 0; i < model->num; i++) {

		if (model->Available[i]==0) {

			model->Available[i] = 1;
			num = i;
			break;

		}

	}

}

Missile::~Missile() {


	model->pos[num] = {99999,99999,99999};

}

void Missile::Update() {


	Vector3 ToEnemy;

	bool Isinit=0;

	QueryGOs<EnemyPlane>("Enemy", [&](EnemyPlane* enemyPlane) {

		if (enemyPlane->HP > 0) {

			Vector3 Buffer = enemyPlane->pos - pos;

			if (Isinit == 0 || ToEnemy.Length() > Buffer.Length()) {

				ToEnemy = Buffer;

			}

			Isinit = 1;

		}
		return true;
		});


	QueryGOs<EnemyFleet>("EnemyFleet", [&](EnemyFleet* enemyFleet) {

		if (enemyFleet->HP > 0) {

			Vector3 Buffer = enemyFleet->pos - pos;

			if (Isinit == 0 || ToEnemy.Length() > Buffer.Length()) {

				ToEnemy = Buffer;

			}

			Isinit = 1;

		}
		return true;
		});

	if (Hud->LockON==1 && LockON==1) {

		Vector3 targetVec;

		targetVec = ToEnemy;
		targetVec.Normalize();

		pos += targetVec * spd;

		rot.SetRotation(Vector3::Front, targetVec);

	}

	else {

		LockON = 0;

		pos += Front * spd;

	}

	if (pos.y <= -8000) {

		effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->SetPosition(pos);
		effectEmitter->Init(0);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->Play();

		SoundSource* se = NewGO<SoundSource>(0);

		se->Init(0);
		se->SetVolume(0.7);
		se->Play(false);

		model->Available[num] = 0;
		model->pos[num] = { 99999,99999,99999 };
		pos = { 99999,99999,99999 };
		DeleteGO(this);

	}

	model->pos[num] = pos;
	model->rot[num] = rot;
}