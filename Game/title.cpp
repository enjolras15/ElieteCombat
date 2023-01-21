#include "stdafx.h"
#include "title.h"
#include "Game.h"

title::title() {

	spriteRender.Init("Assets/image/title.dds",1920,1080);
	spriteRender2.Init("Assets/image/UI.dds", 120, 120);
	spriteRender3.Init("Assets/image/load.dds", 1920, 1080);
	spriteRender4.Init("Assets/image/explain.dds", 1920, 1080);
	fontRender.SetPosition({ -350.0f,-380.0f,0.0f });
	fontRender.SetScale(1);
	fontRender.SetColor({ 0.0f,1.0f,0.0f,1.0f });

	spriteRender3.SetPosition({ 99999,99999,0.0f });
	spriteRender4.SetPosition({ 99999,99999,0.0f });
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/AlteKameraden.wav");

	bgm = NewGO<SoundSource>(3);
	bgm->Init(3);
	bgm->Play(true);
}

title::~title() {


}

void title::Update() {

	if (g_pad[0]->IsTrigger(enButtonDown) && Selected==0) {

		Select++;
		if (Select == 3) Select = 0;

	}

	if (g_pad[0]->IsTrigger(enButtonUp) && Selected == 0) {

		Select--;

		if (Select == -1) Select = 2;

	}

	if (Select == 0) {

		spriteRender2.SetPosition({ -655.0f, -180.0f, 0.0f });
		fontRender.SetText(L"十字キーで選択 Aで決定　ゲームを開始します。");
	}


	else if (Select == 1) {

		if (Selected == 0) {

			spriteRender2.SetPosition({ -655.0f, -260.0f, 0.0f });
			fontRender.SetText(L"十字キーで選択 Aで決定　ゲームの説明です。");

		}

		else {

			spriteRender2.SetPosition({ -655.0f, -260.0f, 0.0f });

			if (num <= 30) {

				fontRender.SetText(L"　　　 Bで戻る");

			}

			else fontRender.SetText(L"");

			num++;

			if (num >= 61) num = 0;

		}

	}

	else if (Select == 2) {

		spriteRender2.SetPosition({ -655.0f, -340.0f, 0.0f });
		fontRender.SetText(L"十字キーで選択 Aで決定　練習モードを開始します。");

	}

	Frame1++;

	if (Frame1 >= 60) {

		spriteRender2.SetPosition({ 99999, 99999, 0.0f });

		if (Frame1 >= 70) {

			Frame1 = 0;

		}

	}

	if (IsStart == 1) {

		if (Selected == 0) {

			NewGO<Game>(0, "Game");
			IsStart = 2;
			DeleteGO(this);


		}

		else if (Selected == 2) {

			Game* g=NewGO<Game>(0, "Game");
			g->mode = 1;
			IsStart = 2;
			DeleteGO(this);

		}

		DeleteGO(bgm);

	}

	if (g_pad[0]->IsPress(enButtonA)) {

		if (Select != 1) {
			fontRender.SetText(L"");
			Selected = Select;
			Select = 3;
			if (IsStart == 0) IsStart = 1;
			spriteRender3.SetPosition({ 0.0f,0.0f,0.0f });

		}

		else {

				Selected = 1;
				spriteRender4.SetPosition({ 0.0f,0.0f,0.0f });

		}
		
	}

	if (g_pad[0]->IsPress(enButtonB)) {

		if (Selected = 1) {
			num = 0;
			Selected = 0;
			spriteRender4.SetPosition({ 99999.0f,99999.0f,0.0f });

		}
	}

	spriteRender2.Update();
	spriteRender3.Update();
	spriteRender4.Update();
}

void title::Render(RenderContext& rc) {

	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);
	spriteRender3.Draw(rc);
	spriteRender4.Draw(rc);
	fontRender.Draw(rc);

}