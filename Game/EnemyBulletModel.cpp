#include "stdafx.h"
#include "EnemyBulletModel.h"

EnemyBulletModel::EnemyBulletModel() {

	for (int i = 0; i < num; i++) {


		modelRender[i].Init("Assets/modeldata/bullet.tkm");

		modelRender[i].SetScale(Vector3{ 6.0f,6.0f,6.0f });

		pos[i] = { 99999,99999,99999 };

		available[i] = 0;

	}

}

EnemyBulletModel::~EnemyBulletModel() {


}

void EnemyBulletModel::Update() {

	for (int i = 0; i < num; i++) {

		modelRender[i].SetPosition(pos[i]);
		modelRender[i].SetRotation(rot[i]);
		modelRender[i].Update();

	}

}

void EnemyBulletModel::Render(RenderContext& rc) {

	for (int i = 0; i < num; i++) {

		modelRender[i].Draw(rc);

	}

}
