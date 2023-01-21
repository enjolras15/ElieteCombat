#include "stdafx.h"
#include "EnemyBullet.h"
#include "EnemyPlane.h"

EnemyBullet::EnemyBullet() {

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

bool EnemyBullet::Start() {

	QueryGOs<EnemyPlane>("Enemy", [&](EnemyPlane* enemy) {

		if (enemy->num == num) {

			Front = enemy->moveDir;
			pos = enemy->pos;
			rot = enemy->rot;
			bulletModel->rot[modelnum] = rot;

		}

		return true;
		});

	return true;

}


EnemyBullet::~EnemyBullet() {



}

void EnemyBullet::Update() {

	pos += Front * spd;

	if (count == 50) {

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

