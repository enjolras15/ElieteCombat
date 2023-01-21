#include "stdafx.h"
#include "bomb.h"
#include "BombModel.h"

Bomb::Bomb() {

	model = FindGO<BombModel>("bombModel");

	player= FindGO<Player>("Player");
	pos = player->pos;

	for (int i = 0; i < model->num; i++) {

		if (model->Available[i] == 0) {

			model->Available[i] = 1;
			num = i;
			break;

		}
	}
}

Bomb::~Bomb() {



}

void Bomb::Update() {

	pos.y -= (10+accel);

	accel += 0.1;

	if (pos.y <= -8000) {

		effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->SetPosition(pos);
		effectEmitter->Init(0);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->Play();

		SoundSource* se = NewGO<SoundSource>(0);

		se->Init(0);
		se->SetVolume(0.7);
		se->Play(false);

		model->Available[num] = 0;
		model->pos[num] = { 99999,99999,99999 };
		pos = { 99999,99999,99999 };
		DeleteGO(this);

	}

	model->pos[num] = pos;

}