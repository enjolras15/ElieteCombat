#pragma once
#include "nature/SkyCube.h"
#include "Level3DRender/LevelRender.h"

class Player;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void InitSky();

	bool mode = 0;

private:
	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Day;
	SpriteRender spriteRender;
	Vector3 m_pos;
	bool GameOver = 0;
	SoundSource* se;
};

