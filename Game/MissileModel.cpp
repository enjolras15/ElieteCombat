#include "stdafx.h"
#include "MissileModel.h"

MissileModel::MissileModel() {

	for (int i = 0; i < num; i++) {

		pos[i] = { 99999,99999,99999 };
		modelRender[i].Init("Assets/modelData/Missile.tkm");
	}

}

MissileModel::~MissileModel() {



}

void MissileModel::Update() {


	for (int i = 0; i < num; i++) {

		modelRender[i].SetPosition(pos[i]);
		modelRender[i].SetRotation(rot[i]);
		modelRender[i].Update();

	}

}

void MissileModel::Render(RenderContext& rc) {

	for (int i = 0; i < num; i++) {

		modelRender[i].Draw(rc);

	}

}