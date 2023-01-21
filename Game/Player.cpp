#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "bullet.h"
#include "bomb.h"
#include "Missile.h"
#include "EnemyBullet.h"
#include "EnemyFleetBullet.h"
#include "EnemyPlane.h"
#include "EnemyFleet.h"
#include "stage.h"
#include "vec.h"


Player::Player() {

	Vec = FindGO<vec>("vec");

	stage = FindGO<Stage>("Stage");

	pos = {0.0f,-3000.0f,0.0f};

	modelRender.Init("Assets/modeldata/plane.tkm",nullptr,0,nsK2EngineLow::enModelUpAxisY);

	m_toCameraPos.Set(0.0f, 100.0f, -300.0f);

	fontRender.SetPosition({ -800.0f,400.0f,0.0f });
	fontRender.SetScale(0.5);
	fontRender.SetColor({ 0.0f,1.0f,0.0f,1.0f });
	fontRender2.SetPosition({ -800.0f,450.0f,0.0f });
	fontRender2.SetScale(0.5);
	fontRender2.SetColor({ 0.0f,1.0f,0.0f,1.0f });

	fontRender3.SetScale(1);
	fontRender3.SetColor({ 0.0f,1.0f,0.0f,1.0f });

	spriteRender.Init("Assets/image/target.dds",50,50);
	spriteRender.SetPosition({ 0.0f,0.0f,0.0f });
	spriteRender2.Init("Assets/image/img.dds",150,300);
	spriteRender2.SetPosition({ 99999.0f,0.0f,0.0f });


}

Player::~Player() {


}

void Player::Update() {

	spriteRender2.Update();

	if (HP < 20 && HP>15) {

		fontRender2.SetText(L"損傷軽微");

	}

	else if (HP <= 15 && HP>9) {

		fontRender2.SetText(L"機体が損傷している。");

	}

	else if (HP<10) {

		fontRender2.SetText(L"機体の損傷が激しい！");

	}

	else {

		fontRender2.SetText(L"損傷なし");

	}

	if (GameOver ==0) {

		swprintf_s(Text, 256, L"速度:%.2f(失速:%.2f) \n高度%.3f\n熱源探知ミサイル%d　無誘導爆弾%d", spd-stall,stall, pos.y + criterion_height,weapon[0],weapon[1]);

	}

	else {
	
		fontRender.SetPosition({ -400.0f,300.0f,0.0f });
		fontRender.SetScale(5);
		fontRender.SetColor({ 0.0f,1.0f,0.0f,1.0f });

		fontRender2.SetText(L"");
		fontRender2.SetPosition({ -105.0f,100.0f,0.0f });
		fontRender2.SetScale(1);
		fontRender2.SetColor({ 0.0f,1.0f,0.0f,1.0f });

		fontRender3.SetPosition({ -100.0f,-100.0f,0.0f });

		spriteRender2.SetPosition({ -200.0f,-200.0f,0.0f });

		swprintf_s(Text, 256, L"GameOver");

		swprintf_s(Result, 256, L"%d\n\n\n\n%d",buffer1,buffer2);

		if (p>buffer1 || f>buffer2) {

			if (frame == 2) {

				if (p > buffer1) buffer1++;
				else buffer2++;

				frame = 0;

			}

			else frame++;


		}

		else {

			if (num <= 30) {

				fontRender2.SetText(L"Press X Button");

			}

			else {

				fontRender2.SetText(L"");

			}

			num++;

			if (num == 61) num = 0;

			if (g_pad[0]->IsTrigger(enButtonX)) {

				GameOver = 2;

			}

		}

		fontRender3.SetText(Result);

	}

	Move();

	fontRender.SetText(Text);
	modelRender.SetPosition(pos);
	modelRender.Update();

}

void Player::Move() {

	

	if (GameOver == 0) {


		Vector3 stickL, stickR;

		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
		float y = g_pad[0]->GetRStickYF();
		float x = g_pad[0]->GetRStickXF();

		Quaternion qRot;

		qRot.SetRotationDeg(Vector3::AxisY, -1.3f * x);

		qRot.Apply(m_toCameraPos);

		Vector3 axisX;

			if ((m_toCameraPos.y >= 300 && y < 0) || (m_toCameraPos.y <= -300 && y > 0)) {

			}

			else {

				axisX.Cross(Vector3::AxisY, m_toCameraPos);
				axisX.Normalize();
				qRot.SetRotationDeg(axisX, 1.3f * y);
				qRot.Apply(m_toCameraPos);

			}

			target.x = pos.x;
			target.y = pos.y + 80;
			target.z = pos.z;

			g_camera3D->SetTarget(target);

			CameraPos = target + m_toCameraPos;

			g_camera3D->SetPosition(CameraPos);

				if (stickL.x > 0) {

					Zrad += stickL.x;

				}

				if (stickL.x < 0) {

					Zrad += stickL.x;

				}

				if (stickL.y > 0) {

					Xrad += stickL.y/1.2;

				}

				if (stickL.y < 0) {

					Xrad += stickL.y/1.2;

				}

				rot = Quaternion::Identity;

				Quaternion XRotation, YRotation;


				XRotation.SetRotationDegX(Xrad);
				YRotation.SetRotationDegY(Zrad);

				rot.Multiply(XRotation,rot);
				rot.Multiply(YRotation);

		if (g_pad[0]->IsPress(enButtonRB1)) {

			if (spd < 12) {

				spd += 0.1;
			}

		}

		if (g_pad[0]->IsPress(enButtonLB1)) {

			if (spd > 8) {

				spd -= 0.1;
			}

		}


		if (g_pad[0]->IsTrigger(enButtonB)) {

			if (weapon[0] > 0) {

				NewGO<Missile>(0, "missile");
				weapon[0]--;
			}


		}


		if (g_pad[0]->IsPress(enButtonLB2)) {


		}


		if (g_pad[0]->IsTrigger(enButtonRB2)) {


			if (weapon[1] > 0 && coolDown[1] == 0) {

				NewGO<Bomb>(0, "bomb");
				coolDown[1] = MaxcoolDown[1];
				weapon[1]--;
			}

		}

		if (pos.y + criterion_height >= 11000) {

			stall = 30;

		}

		else {

			if (stall > 0) {

				stall -= 0.1;

				if (stall < 0)
					stall = 0;

			}

		}


		if (g_pad[0]->IsPress(enButtonA) && coolDown[0] == 0) {

			NewGO<bullet>(0,"bullet");

			SoundSource* se = NewGO<SoundSource>(1);
			se->Init(1);
			se->SetVolume(0.7);
			se->Play(false);


			coolDown[0] = MaxcoolDown[0];

		}

		modelRender.SetRotation(rot);

		Matrix Mrot = Matrix::Identity;

		Mrot.MakeRotationFromQuaternion(rot);

		Front.x = Mrot.m[2][0];
		Front.y = Mrot.m[2][1];
		Front.z = Mrot.m[2][2];

		//Right.x = Mrot.m[0][0];
		//Right.y = Mrot.m[0][1];
		//Right.z = Mrot.m[0][2];

		//Up.x = Mrot.m[1][0];
		//Up.y = Mrot.m[1][1];
		//Up.z = Mrot.m[1][2];

		if (stall > 0) {

			pos.y -= 15;

		}
		
		SkyCube* skyCube = FindGO<SkyCube>("skycube");

		Vector3 skypos = skyCube->pos += Front * (spd - stall);

		skyCube->SetPosition(skypos);

			pos += Front * (spd-stall);


		if (pos.y + criterion_height <= 0) {

			Death();

		}


		QueryGOs<EnemyBullet>("enemybullet", [&](EnemyBullet* bullet) {
			Vector3 diff = bullet->pos - pos;

			if (diff.Length() < 30) {

				HP -= 1;

				DeleteGO(bullet);

				if (HP<=0) {

					Death();

				}

			}

			return true;
			});


		QueryGOs<EnemyFleetBullet>("enemyfleetbullet", [&](EnemyFleetBullet* bullet) {
			Vector3 diff = bullet->pos - pos;

			if (diff.Length() < 30) {

				HP -= 1;

				DeleteGO(bullet);

				if (HP <= 0) {

					Death();

				}

			}

			return true;
			});


		bool IsDisplayVec=0;

		QueryGOs<EnemyPlane>("Enemy", [&](EnemyPlane* enemyPlane) {

			if (enemyPlane->HP > 0) {

				Vector3 Buffer = enemyPlane->pos - pos;

				if (IsDisplayVec == 0 || ToEnemy.Length() > Buffer.Length()) {

					ToEnemy = Buffer;

				}

				IsDisplayVec = 1;

			}
			return true;
			});


		QueryGOs<EnemyFleet>("EnemyFleet", [&](EnemyFleet* enemyFleet) {

			if (enemyFleet->HP > 0) {

				Vector3 Buffer = enemyFleet->pos - pos;

				if (IsDisplayVec == 0 || ToEnemy.Length() > Buffer.Length()) {

					ToEnemy = Buffer;

				}

				IsDisplayVec = 1;

			}
			return true;
			});


		if (IsDisplayVec) {

			Vector3 DrawV = ToEnemy;
			DrawV.Normalize();
			//DrawV *= 150;
			//g_k2Engine->DrawVector(DrawV, pos);
			Vec->V = DrawV;

			//Vector3 posBuffer;
			//posBuffer.x = pos.x - 230;
			//posBuffer.y = pos.y;
			//posBuffer.z = pos.z + 100;
			Vec->pos = pos;

		}

		else {

			//g_k2Engine->DrawVector(Vector3{ 0,0,0 }, Vector3{ 0,0,0 });
			Vec->V = Vector3{ 0,0,0 };
			stage->StageNumber = int(stage->StageNumber + 1);
			stage = FindGO<Stage>("Stage");
			Game* g = FindGO<Game>("Game");
			if (stage->StageNumber >= 5.0f && g->mode==0) {

				stage->StageNumber = 1;

			}

			stage->wave += 1;

			if (weapon[0] < 4) weapon[0]++;
			if (weapon[1] < 3) weapon[1]++;

		}

		Vector3 targetpos;

		Vector2 ScreenTargetpos;

		targetpos = pos;

		for (int i = 0; i < 7; i++) {

			targetpos += Front * 30;

		}

		g_camera3D->CalcScreenPositionFromWorldPosition(ScreenTargetpos, targetpos);


		spriteRender.SetPosition(Vector3(ScreenTargetpos.x+1,ScreenTargetpos.y,0.0f));
		spriteRender.Update();

	}

	else {

	spriteRender.SetPosition(Vector3(99999,99999,99999));
		g_k2Engine->DrawVector(Vector3{ 0,0,0 }, Vector3{ 0,0,0 });

	}


	for (int i = 0; i < 2; i++) {

		if (coolDown[i] > 0) {

			coolDown[i]--;

		}

	}

}

void Player::Render(RenderContext& rc) {

	modelRender.Draw(rc);
	fontRender.Draw(rc);
	fontRender2.Draw(rc);
	fontRender3.Draw(rc);
	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);

}

void Player::Death() {

	CameraPos.y = pos.y + 270;
	CameraPos.z = pos.z - 200;

	g_camera3D->SetPosition(CameraPos);

	effectEmitter = NewGO<EffectEmitter>(0);
	pos.y += 20;
	effectEmitter->SetPosition(pos);
	pos.y -= 20;
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
	effectEmitter->Play();

	SoundSource* se = NewGO<SoundSource>(0);

	se->Init(0);

	se->Play(false);

	pos = { -99999,-99999,-99999 };
	GameOver = 1;

}