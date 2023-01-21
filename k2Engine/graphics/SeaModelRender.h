#pragma once

namespace nsK2Engine
{
	/**
	 * @brief �g�̃��f����`�悷�邽�߂̃N���X�B
	 * �߂��Ⴍ����K���ɏ����Ă�̂ł��܂�Q�l�ɂ͂��Ȃ��ł��������B�@by �ѐD
	*/
	class SeaModelRender
	{
	public:
		/**
		 * @brief ���f���̏�����
		 * @param modelFilePath ���f���̃t�@�C���p�X
		 * @param normalMapFilePath1 �g�̖@���}�b�v0
		 * @param normalMapFilePath2 �g�̖@���}�b�v1
		*/
		void Init(const char* modelFilePath,const wchar_t* normalMapFilePath1,const wchar_t* normalMapFilePath2)
		{
			//�@���}�b�v��������
			m_normalTextures[0].InitFromDDSFile(normalMapFilePath1);
			m_normalTextures[1].InitFromDDSFile(normalMapFilePath2);

			//���f���̏�����
			m_modelRender.InitSeaModel(modelFilePath,m_normalTextures,static_cast<void*>(&m_scrollValue),sizeof(m_scrollValue));
		}

		/**
		 * @brief ���W�Z�b�g
		 * @param pos 
		*/
		void SetPosition(const Vector3& pos)
		{
			m_modelRender.SetPosition(pos);
		}

		/**
		 * @brief �X�V����
		*/
		void Update();

		/**
		 * @brief �`��
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void Draw(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	private:
		/**
		 * @brief �g��UV���X�N���[��������l
		*/
		struct WaveUVScrollValue
		{
		public:
			float Wave1 = 0.0f;
			float Wave2 = 0.0f;
		};

		ModelRender m_modelRender;					//�C�̃��f��
		std::array<Texture, 2> m_normalTextures;	//�C�̕\�ʂ̖@���}�b�v(2��)
		WaveUVScrollValue m_scrollValue;			//�g��UV���X�N���[��������l
	};
}

