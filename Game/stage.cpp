#include "stdafx.h"
#include "Stage.h"
#include "Game.h"
#include "EnemyPlane.h"
#include "EnemyFleet.h"

Stage::Stage() {

	fontRender.SetPosition({ -350.0f,-380.0f,0.0f });
	fontRender.SetScale(1);
	fontRender.SetColor({ 0.0f,1.0f,0.0f,1.0f });

	game = FindGO<Game>("Game");


}

Stage::~Stage() {


}

void Stage::Update() {

	if (game->mode != 1) {

		if (StageNumber == 1) {

			enemy = NewGO<EnemyPlane>(0, "Enemy");
			enemy->HP = 100;
			enemy->pos = { 1000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");
			enemy->HP = 100;
			enemy->pos = { -3000,-3500,1000 };


			StageNumber = 1.1;

		}

		if (StageNumber == 2) {

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 2000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { -1000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-2000,0 };

			StageNumber = 2.1;
		}

		if (StageNumber == 3) {

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 2000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-2000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-3500,0 };

			enemyFleet = NewGO<EnemyFleet>(0, "EnemyFleet");

			enemyFleet->HP = 25;
			enemyFleet->pos = { 0,-8000,0 };

			StageNumber = 3.1;
		}


		if (StageNumber == 4) {

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 2000,-3000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { 1000,-2000,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { -1000,-3500,0 };

			enemy = NewGO<EnemyPlane>(0, "Enemy");

			enemy->HP = 100;
			enemy->pos = { -2000,-3500,0 };

			enemyFleet = NewGO<EnemyFleet>(0, "EnemyFleet");

			enemyFleet->HP = 25;
			enemyFleet->pos = { 0,-8000,0 };

			enemyFleet = NewGO<EnemyFleet>(0, "EnemyFleet");

			enemyFleet->HP = 25;
			enemyFleet->pos = { 2000,-8000,1000 };

			StageNumber = 4.1;
		}

		swprintf_s(Text, 256, L"Wave%d", wave);

		fontRender.SetText(Text);

	}

}

void Stage::Render(RenderContext& rc) {

	fontRender.Draw(rc);

}
