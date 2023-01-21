#include "stdafx.h"
#include "BulletModel.h"

BulletModel::BulletModel() {

	for (int i = 0; i < 5; i++) {


		modelRender[i].Init("Assets/modeldata/bullet.tkm");

		modelRender[i].SetScale(Vector3{ 6.0f,6.0f,6.0f });
		
		pos[i] = {99999,99999,99999};

		available[i] = 0;

	}

}

BulletModel::~BulletModel() {


}

void BulletModel::Update() {

	for (int i = 0; i < 5; i++) {

		modelRender[i].SetPosition(pos[i]);
		modelRender[i].SetRotation(rot[i]);
		modelRender[i].Update();

	}

}

void BulletModel::Render(RenderContext& rc) {

	for (int i = 0; i < 5; i++) {

		modelRender[i].Draw(rc);

	}

}