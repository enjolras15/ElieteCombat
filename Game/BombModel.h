#pragma once
class BombModel : public IGameObject
{
public:
	BombModel();
	~BombModel();

	void Update();
	void Render(RenderContext& rc);



	Vector3 pos[3];
	int Available[3]={0,0};
	int num = 3;

private:
	ModelRender modelRender[3];


};

