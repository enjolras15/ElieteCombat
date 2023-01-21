#include "stdafx.h"
#include "player.h"
#include "hud.h"
#include "EnemyPlane.h"
#include "EnemyFleet.h"

hud::hud () {

	player = FindGO<Player>("Player");

	spriteRender.Init("Assets/image/hud.dds", 50, 50);
	spriteRender.SetPosition({ 99999,99999,99999 });
}

hud::~hud() {


}

void hud::Update() {

	bool IsInit = 0;
	Vector3 ToEnemy;
	Vector3 target;

	QueryGOs<EnemyPlane>("Enemy", [&](EnemyPlane* enemyPlane) {

		if (enemyPlane->HP > 0) {

			Vector3 Buffer = enemyPlane->pos - player->pos;

			if (IsInit == 0 || ToEnemy.Length() > Buffer.Length()) {

				ToEnemy = Buffer;
				target = enemyPlane->pos;
			}

			IsInit = 1;

		}
		return true;
		});


	QueryGOs<EnemyFleet>("EnemyFleet", [&](EnemyFleet* enemyFleet) {

		if (enemyFleet->HP > 0) {

			Vector3 Buffer = enemyFleet->pos - player->pos;

			if (IsInit == 0 || ToEnemy.Length() > Buffer.Length()) {

				ToEnemy = Buffer;
				target = enemyFleet->pos;
			}

			IsInit = 1;

		}
		return true;
		});

	Vector3 moveDir=player->Front;
	
	Vector3 ToEnemyDir = ToEnemy;

	ToEnemyDir.Normalize();

	float t = ToEnemyDir.Dot(moveDir);

	float angle = acos(t);

	if (IsInit==1 && ToEnemy.Length() < 1200 && fabsf(angle) < Math::DegToRad(45.0f)) {

		Vector2 ScreenTargetpos;

		g_camera3D->CalcScreenPositionFromWorldPosition(ScreenTargetpos,target);


		spriteRender.SetPosition(Vector3(ScreenTargetpos.x , ScreenTargetpos.y, 0.0f));
		LockON = 1;
	}

	else {

		LockON = 0;
		spriteRender.SetPosition({ 99999,99999,99999 });

	}

	spriteRender.Update();


}

void hud::Render(RenderContext& rc) {

	spriteRender.Draw(rc);

}