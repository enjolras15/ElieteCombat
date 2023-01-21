#pragma once
#include "../k2Engine/graphics/SeaModelRender.h"

class Sea : public IGameObject
{

public:
	Sea();
	~Sea();

	void Update();

	void Render(RenderContext& rc);

	Vector3 pos = { 0.0f,-8000.0f,0.0f };

	SeaModelRender seaModelRender;

};

