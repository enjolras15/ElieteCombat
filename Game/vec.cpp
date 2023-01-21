#include "stdafx.h"
#include "vec.h"

vec::vec() {

	modelRender.Init("Assets/modelData/preset/vector.tkm");
	modelRender.SetScale(50.0, 50.0, 110.0);
}


vec::~vec() {



}

void vec::Update() {

	modelRender.SetPosition(pos);
	rot.SetRotation(Vector3::Front, V);
	modelRender.SetRotation(rot);

	modelRender.Update();
}

void vec::Render(RenderContext& rc) {

	modelRender.Draw(rc);


}