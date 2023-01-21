#include "stdafx.h"
#include "EnemyPlaneModel.h"


EnemyPlaneModel::EnemyPlaneModel() {

	for (int i = 0; i < 5;i++) {
		pos[i] = { 99999,99999,99999 };
		modelRender[i].Init("Assets/modeldata/EnemyPlane.tkm", nullptr, 0, nsK2EngineLow::enModelUpAxisY);

	}

}

EnemyPlaneModel::~EnemyPlaneModel() {



}

void EnemyPlaneModel::Update() {

	for (int i = 0; i < 5; i++) {

		modelRender[i].SetRotation(rot[i]);
		modelRender[i].SetPosition(pos[i]);
		modelRender[i].Update();

	}

}

void EnemyPlaneModel::Render(RenderContext& rc) {

	for (int i = 0; i < 5; i++) {

			modelRender[i].Draw(rc);

	}

}