#pragma once

class vec : public IGameObject
{

public:

	vec();
	~vec();

	void Update();

	void Render(RenderContext& rc);

	Vector3 V;
	Vector3 pos;

private:

	Quaternion rot;

	ModelRender modelRender;

};

