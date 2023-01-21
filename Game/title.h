#pragma once
	
class title : public IGameObject
{
public:
	title();
	~title();

	void Update();

	void Render(RenderContext& rc);

private:

	int Select=0;

	int Selected = 0;

	int Frame1 = 0;

	int IsStart = 0;

	int num = 0;

	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	SpriteRender spriteRender3;
	SpriteRender spriteRender4;
	FontRender fontRender;
	SoundSource* bgm;
	SoundSource* se;
};

