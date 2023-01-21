#pragma once
class MissileModel : public IGameObject
{
public:
	MissileModel();
	~MissileModel();

	void Update();
	void Render(RenderContext& rc);

	Vector3 pos[4];
	Quaternion rot[4];

	int Available[4] = { 0,0,0,0 };
	int num = 4;

private:

	ModelRender modelRender[4];


};

