#pragma once
#include "sound/SoundSource.h"
#include "camera/SpringCamera.h"
#include "stage.h"
#include "vec.h"

class Stage;
class vec;

class Player : public IGameObject
{

public:
	Player();
	~Player();

	void Update();

	void Move();

	void Render(RenderContext& rc);

	void Death();

	float Xrad = 0;
	float Zrad = 0;

	int GameOver = 0;

	float spd =10.0;

	Vector3 pos;

	Quaternion rot;

	Vector3 Front, Right, Up;

	Vector3 ToEnemy;

	int p = 0;
	int f = 0;

private:

	int HP = 20;

	const float criterion_height = 8000.0f;

	wchar_t Text[256];

	wchar_t Result[256];

	int mode = 0;

	const int MaxcoolDown[2] = { 10,35 };

	int coolDown[2] = { 0,0 };

	int weapon[2] = {4,3};

	float stall = 0;

	int num = 0;

	int frame = 0;

	int buffer1 = 0;
	int buffer2 = 0;

	Vector3 m_toCameraPos = Vector3::One;

	Vector3 moveSpeed;

	Vector3 target;

	Vector3 CameraPos;

	FontRender fontRender;

	FontRender fontRender2;

	FontRender fontRender3;

	SpriteRender spriteRender;

	SpriteRender spriteRender2;

	ModelRender modelRender;

	SoundSource* BGM;

	EffectEmitter* effectEmitter;

	Stage* stage;

	vec* Vec;
};

