#include "k2EnginePreCompile.h"
#include "SeaModelRender.h"

namespace
{
	float waveTextureSize = 512.0f;		//波の法線テクスチャのサイズ

	//////////調整用の値//////////
	float Wave1ScrollValue = 0.0004f;	//1つ目の波のUVを1フレームに進める値
	float Wave2ScrollValue = 0.0005f;	//2つ目の波のUVを1フレームに進める値
	//////////調整用の値//////////
}

namespace nsK2Engine
{
	void SeaModelRender::Update()
	{
		//各波のUV座標をスクロールさせる。

		//スクロールさせる値を加算
		m_scrollValue.Wave1 += Wave1ScrollValue;
		//値が1を超えたら0に戻す。
		if (m_scrollValue.Wave1 >= waveTextureSize)
		{
			m_scrollValue.Wave1 = 0.0f;
		}

		//波2も同様
		m_scrollValue.Wave2 += Wave2ScrollValue;
		if (m_scrollValue.Wave2 >= waveTextureSize)
		{
			m_scrollValue.Wave2 = 0.0f;
		}

		//モデルのアップデート
		m_modelRender.Update();
	}
}
