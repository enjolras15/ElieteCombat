#pragma once

namespace nsK2Engine
{
	/**
	 * @brief 波のモデルを描画するためのクラス。
	 * めちゃくちゃ適当に書いてるのであまり参考にはしないでください。　by 錦織
	*/
	class SeaModelRender
	{
	public:
		/**
		 * @brief モデルの初期化
		 * @param modelFilePath モデルのファイルパス
		 * @param normalMapFilePath1 波の法線マップ0
		 * @param normalMapFilePath2 波の法線マップ1
		*/
		void Init(const char* modelFilePath,const wchar_t* normalMapFilePath1,const wchar_t* normalMapFilePath2)
		{
			//法線マップを初期化
			m_normalTextures[0].InitFromDDSFile(normalMapFilePath1);
			m_normalTextures[1].InitFromDDSFile(normalMapFilePath2);

			//モデルの初期化
			m_modelRender.InitSeaModel(modelFilePath,m_normalTextures,static_cast<void*>(&m_scrollValue),sizeof(m_scrollValue));
		}

		/**
		 * @brief 座標セット
		 * @param pos 
		*/
		void SetPosition(const Vector3& pos)
		{
			m_modelRender.SetPosition(pos);
		}

		/**
		 * @brief 更新処理
		*/
		void Update();

		/**
		 * @brief 描画
		 * @param rc レンダーコンテキスト
		*/
		void Draw(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	private:
		/**
		 * @brief 波のUVをスクロールさせる値
		*/
		struct WaveUVScrollValue
		{
		public:
			float Wave1 = 0.0f;
			float Wave2 = 0.0f;
		};

		ModelRender m_modelRender;					//海のモデル
		std::array<Texture, 2> m_normalTextures;	//海の表面の法線マップ(2枚)
		WaveUVScrollValue m_scrollValue;			//波のUVをスクロールさせる値
	};
}

