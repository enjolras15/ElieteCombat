#include "stdafx.h"
#include "missile.h"
#include "bullet.h"
#include "EnemyPlane.h"
#include "EnemyPlaneModel.h"
#include "EnemyBullet.h"
#include "sound/SoundEngine.h"

EnemyPlane::EnemyPlane() {

	//rot = Quaternion::Identity;

	//Quaternion XRotation, YRotation;


	//XRotation.SetRotationDegX(Xrad);
	//YRotation.SetRotationDegY(Zrad);

	//rot.Multiply(XRotation, rot);
	//rot.Multiply(YRotation);

	//Matrix Mrot = Matrix::Identity;

	//Mrot.MakeRotationFromQuaternion(rot);

	//Front.x = Mrot.m[2][0];
	//Front.y = Mrot.m[2][1];
	//Front.z = Mrot.m[2][2];

	model = FindGO<EnemyPlaneModel>("enemyPlaneModel");

	for (int i = 0; i < 5; i++) {

		if (model->Available[i] == 0) {

			model->Available[i] = 1;

			num = i;
			break;

		}
	}

}

EnemyPlane::~EnemyPlane() {


}

void EnemyPlane::Update() {

	Player* player = FindGO<Player>("Player");

		if (0>=HP) {

			model->pos[num] = { 99999,99999,99999 };
			model->Available[num] = 0;
		}

		else {

			QueryGOs<bullet>("bullet", [&](bullet* bullet) {
				Vector3 diff = bullet->pos - pos;

				if (diff.Length() < 30)
					HP -= 20;

				if (0 >= HP)
				{
					Death();

				}

				return true;
				});

			QueryGOs<Missile>("missile", [&](Missile* missile) {

				Vector3 diff = missile->pos - pos;



				if (diff.Length() < 10)

				{

					DeleteGO(missile);
					Death();

				}

				return true;
				});



			Vector3 toPlayer = player->pos - pos;
			Vector3 diff = toPlayer;
			toPlayer.Normalize();
			Front.Normalize();

			if (pos.y + criterion_height <= 0) {

				Death();

			}

			if (diff.Length() > 3000) {

				moveDir.Lerp(0.01f, Front, toPlayer);

			}

			else {

				moveDir.Lerp(0.005f, Front, toPlayer);

			}

			if (pos.y + criterion_height <100 && moveDir.y<0) {

				moveDir.y *=-1;

			}

			if (pos.y + criterion_height > 9000 && moveDir.y > 0) {

				moveDir.y *= -1;

			}

			
			pos += moveDir * spd;
			model->pos[num] = pos;


			float t = toPlayer.Dot(moveDir);

			float angle = acos(t);

			float product = Front.Dot(moveDir);

				if (product>0.5 && diff.Length()<600 && fabsf(angle) < Math::DegToRad(45.0f)) {

					if (coolDown == 0) {

						Shot();

					}

				}

			Front = moveDir;

			rot.SetRotation(Vector3::Front, moveDir);

			model->rot[num] = rot;

			if (coolDown > 0) {

				coolDown--;

			}

		}


}

void EnemyPlane::Death() {

	HP = 0;
	effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->SetPosition(pos);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
	effectEmitter->Play();

	model->Available[num] = 0;

	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(0);
	se->Play(false);

	Player* player = FindGO<Player>("Player");
	player->p += 1;

}

void EnemyPlane::Shot() {

	EnemyBullet* bullet=NewGO<EnemyBullet>(0,"enemybullet");
	bullet->num = num;
	coolDown = 15;

	SoundSource* se = NewGO<SoundSource>(1);
	se->Init(1);
	se->SetVolume(0.7);
	se->Play(false);
}