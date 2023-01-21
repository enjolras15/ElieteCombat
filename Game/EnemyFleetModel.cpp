#include "stdafx.h"
#include "EnemyFleetModel.h"

EnemyFleetModel::EnemyFleetModel() {

	for (int i = 0; i < num; i++) {
		pos[i] = { 99999,-8000,99999 };
		modelRender[i].Init("Assets/modelData/cruiser.tkm");
		modelRender[i].SetScale(2.0, 2.0, 2.0);
	}

}

EnemyFleetModel::~EnemyFleetModel() {



}

void EnemyFleetModel::Update() {

	for (int i = 0; i < num; i++) {

		modelRender[i].SetRotation(rot[i]);
		modelRender[i].SetPosition(pos[i]);
		modelRender[i].Update();

	}

}

void EnemyFleetModel::Render(RenderContext& rc) {

	for (int i = 0; i < num; i++) {

		modelRender[i].Draw(rc);

	}

}