#include "stdafx.h"
#include "bullet.h"
#include "Player.h"
#include "EnemyFleet.h"
#include "bomb.h"
#include "missile.h"
#include "EnemyFleetBullet.h"

EnemyFleet::EnemyFleet() {

	model = FindGO<EnemyFleetModel>("enemyFleetModel");

	for (int i = 0; i < 5; i++) {

		if (model->Available[i] == 0) {

			model->Available[i] = 1;

			num = i;
			break;

		}
	}

}


EnemyFleet::~EnemyFleet() {



}

void EnemyFleet::Update() {

	for (int i = 0; i < 5; i++) {


		if (0 >= HP) {

			model->pos[num] = { 99999,99999,99999 };
			model->Available[num] = 0;
		}

		else {

		Player* player=	FindGO<Player>("Player");
		Vector3 diff = player->pos - pos;

			if (diff.Length()<110) {
				HP = 0;

				Death();
				player->Death();

			}

			QueryGOs<bullet>("bullet", [&](bullet* bullet) {
				Vector3 diff = bullet->pos - pos;

				if (diff.Length() < 110) {
					HP -= 1;
					
					if (HP>0) {

						effectEmitter = NewGO<EffectEmitter>(1);
						effectEmitter->SetPosition(pos);
						effectEmitter->Init(1);
						effectEmitter->SetScale({ 30.0f,30.0f,30.0f });
						effectEmitter->Play();

					}

					else {

						Death();

					}

					bullet->pos = { 99999,99999,99999 };
				}

					return true;
			});

			QueryGOs<Bomb>("bomb", [&](Bomb* bomb) {
				Vector3 diff = bomb->pos - pos;

				if (diff.Length() < 110) {

					HP = 0;

					Death();

				}
				return true;

			});

			QueryGOs<Missile>("missile", [&](Missile* missile) {
				Vector3 diff = missile->pos - pos;

				if (diff.Length() < 110) {

					HP = 0;

					Death();

				}
				return true;

				});

			model->pos[num] = pos;

			if(coolDown>0) coolDown--;

			
			diff = player->pos - pos;

			if (coolDown <= 0 && diff.Length()<1000) {

				for (i = 0; i < 2; i++) {

					Shot();

				}

			}

		}

	}

}

void EnemyFleet::Death() {

	effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->SetPosition(pos);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 50.0f,30.0f,50.0f });
	effectEmitter->Play();

	model->Available[num] = 1;
	Player* player = FindGO<Player>("Player");
	player->f += 1;

}

void EnemyFleet::Shot() {

	EnemyFleetBullet* bullet = NewGO<EnemyFleetBullet>(0, "enemyfleetbullet");
	bullet->num = num;
	coolDown = 100;
		
	SoundSource* se = NewGO<SoundSource>(1);
	se->Init(1);
	se->SetVolume(0.7);
	se->Play(false);
}