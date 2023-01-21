#include "stdafx.h"
#include "bullet.h"
#include "Player.h"
#include "BulletModel.h"

bullet::bullet() {

	player = FindGO<Player>("Player");

	Front = player->Front;
	pos = player->pos+ Front*player->spd;

	rot = player->rot;

	bulletModel = FindGO<BulletModel>("bulletmodel");

	for (int i = 0; i < 7; i++) {

		if (bulletModel->available[i]==0) {

			num = i;
			bulletModel->available[num] = 1;
			bulletModel->rot[num] = rot;
			break;

		}


	}

}

bullet::~bullet() {


}


void bullet::Update() {

	pos += Front* spd;

	if (count == 50) {

		bulletModel->pos[num] = {9999,9999,9999};
		bulletModel->available[num] = 0;
		DeleteGO(this);

	}


	else {

		if (count > player->spd/2+1) {

			bulletModel->pos[num] = pos;
		}

		count++;
	}


}