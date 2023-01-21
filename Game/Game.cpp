#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BulletModel.h"
#include "missileModel.h"
#include "BombModel.h"
#include "title.h"
#include "Sea.h"
#include "stage.h"
#include "hud.h"
#include "EnemyPlane.h"
#include "EnemyFleet.h"
#include "EnemyPlaneModel.h"
#include "EnemyFleetModel.h"
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"
#include "EnemyFleetBullet.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "vec.h"

void Game::InitSky() {

	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	// 環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
	// 環境日光の影響が分かりやすいように、ディレクションライトはオフに。
	//g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);

}

bool Game::Start()
{

	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/explode.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/shot.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/bgm.wav");
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/hit.efk");


	se = NewGO<SoundSource>(2);
	se->Init(2);
	se->Play(true);

	g_camera3D->SetNear(0.1f);

	g_camera3D->SetFar(10000000.0f);

	InitSky();

	g_k2Engine->SetDrawVectorEnable();
	NewGO<EnemyPlaneModel>(0, "enemyPlaneModel");
	NewGO<EnemyFleetModel>(0, "enemyFleetModel");
	NewGO<EnemyBulletModel>(0, "enemyBulletModel");
	NewGO<Stage>(0, "Stage");

	NewGO<MissileModel>(0,"missileModel");
	NewGO<BombModel>(0, "bombModel");
	NewGO<BulletModel>(0, "bulletmodel");

	NewGO<vec>(0, "vec");
	NewGO<Player>(0, "Player");
	NewGO<hud>(0, "hud");
	NewGO<Sea>(0,"Sea");
	
	return true;
}

void Game::Update()
{


	Player* player = FindGO<Player>("Player");

	if (GameOver == 0) {

		if (player->GameOver == 2) {



			QueryGOs<EnemyBullet>("enemybullet", [&](EnemyBullet* bullet) {

				DeleteGO(bullet);

				return true;
				});


			QueryGOs<EnemyFleetBullet>("enemyfleetbullet", [&](EnemyFleetBullet* bullet) {

				DeleteGO(bullet);

				return true;
				});

			QueryGOs<EnemyPlane>("Enemy", [&](EnemyPlane* enemyPlane) {

				DeleteGO(enemyPlane);

				return true;
				});


			QueryGOs<EnemyFleet>("EnemyFleet", [&](EnemyFleet* enemyFleet) {

				DeleteGO(enemyFleet);

				return true;
				});

			DeleteGO(player);
			DeleteGO(FindGO<vec>("vec"));
			DeleteGO(FindGO<hud>("hud"));
			DeleteGO(FindGO<Sea>("Sea"));
			DeleteGO(FindGO<Stage>("Stage"));
			DeleteGO(se);
			DeleteGO(m_skyCube);
			DeleteGO(FindGO<BulletModel>("bulletmodel"));
			DeleteGO(FindGO<BombModel>("bombmodel"));
			DeleteGO(FindGO<MissileModel>("missileModel"));

			DeleteGO(FindGO<EnemyBulletModel>("enemyBulletModel"));
			DeleteGO(FindGO<EnemyFleetModel>("enemyFleetModel"));
			DeleteGO(FindGO<EnemyPlaneModel>("enemyPlaneModel"));

			NewGO<title>(0, "title");

			DeleteGO(this);



			GameOver = 1;
		}

	}

}