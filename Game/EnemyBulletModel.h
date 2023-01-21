#pragma once
class EnemyBulletModel : public IGameObject
{
public:
	EnemyBulletModel();
	~EnemyBulletModel();

	void Render(RenderContext& rc);

	void Update();

	int available[30];
	int num = 30;

	Vector3 pos[30];
	Quaternion rot[30];

private:
	ModelRender modelRender[30];

};

