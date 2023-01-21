#include "stdafx.h"
#include "Sea.h"

namespace
{
	const char* seaModelPath = "Assets/modeldata/sea.tkm";
	const wchar_t* waveTexturePath[2] =
	{
		L"Assets/modelData/preset/SeaNormal1.dds",
		L"Assets/modelData/preset/SeaNormal2.dds" 
	};
}

Sea::Sea() {

	//���f���t�@�C���p�X�A�@���}�b�v�̃p�X�ŏ�����
	seaModelRender.Init(seaModelPath,
		waveTexturePath[0],
		waveTexturePath[1]
	);

	seaModelRender.SetPosition(pos);
}

Sea::~Sea() {


}

void Sea::Update() {
	seaModelRender.SetPosition(pos);

	seaModelRender.Update();

}

void Sea::Render(RenderContext& rc) {

	seaModelRender.Draw(rc);

}