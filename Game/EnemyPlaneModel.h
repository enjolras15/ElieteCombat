#pragma once
class EnemyPlaneModel : public IGameObject
{

public:
	EnemyPlaneModel();
	~EnemyPlaneModel();

	void Update();

	void Render(RenderContext& rc);

	ModelRender modelRender[5];
	Vector3 pos[5];
	Quaternion rot[5];
	int Available[5] = { 0,0,0,0,0 };

};

