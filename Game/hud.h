#pragma once
class hud: public IGameObject
{

public:
	hud();
	~hud();

	void Render(RenderContext& rc);
	void Update();

	bool LockON=0;

private:
	SpriteRender spriteRender;
	Player* player;

};

