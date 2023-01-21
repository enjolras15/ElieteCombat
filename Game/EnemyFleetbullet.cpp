#include "stdafx.h"
#include "EnemyFleetbullet.h"
#include "EnemyFleetBullet.h"
#include "Player.h"

EnemyFleetBullet::EnemyFleetBullet() {

	bulletModel = FindGO<EnemyBulletModel>("enemyBulletModel");

	for (int i = 0; i < bulletModel->num; i++) {

		if (bulletModel->available[i] == 0) {

			modelnum = i;
			bulletModel->available[modelnum] = 1;
			//bulletModel->rot[modelnum] = rot;
			break;

		}

	}

	if (modelnum == -1) DeleteGO(this);

}

bool EnemyFleetBullet::Start() {

	QueryGOs<EnemyFleet>("EnemyFleet", [&](EnemyFleet* enemy) {

		if (enemy->num == num) {

			pos = enemy->pos;

		}

		return true;
		});

	Player* player = FindGO<Player>("Player");

	diff = player->pos - pos;

	Front = diff;

	Front.Normalize();

	return true;

}


EnemyFleetBullet::~EnemyFleetBullet() {



}

void EnemyFleetBullet::Update() {

	pos += Front * spd;

	rot.SetRotation(Vector3::Front, Front);
	bulletModel->rot[modelnum] = rot;

	if (count >= 50) {

		bulletModel->pos[modelnum] = { 99999,99999,99999 };
		bulletModel->available[modelnum] = 0;
		DeleteGO(this);

	}


	else {

		if (count > 5) {
			bulletModel->pos[modelnum] = pos;
		}

		count++;
	}

}

