#pragma once
class BulletModel : public IGameObject
{
public:

	BulletModel();
		~BulletModel();

	void Update();

	void Render(RenderContext& rc);

	ModelRender modelRender[5];

	Vector3 pos[5];

	Quaternion rot[5];

	int available[5];

};

