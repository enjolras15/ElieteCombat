#include "stdafx.h"
#include "BombModel.h"

BombModel::BombModel() {

	for (int i = 0; i < num; i++) {

		modelRender[i].Init("Assets/modeldata/bomb.tkm");
		pos[i] = { 99999,99999,99999 };
	}

}

BombModel::~BombModel() {

}

void BombModel::Update() {

	for (int i = 0; i < num; i++) {

		modelRender[i].SetPosition(pos[i]);
		modelRender[i].Update();

	}

}

void BombModel::Render(RenderContext& rc) {

	for (int i = 0; i < num; i++) {

		modelRender[i].Draw(rc);

	}

}