#include "k2EnginePreCompile.h"
#include "SeaModelRender.h"

namespace
{
	float waveTextureSize = 512.0f;		//�g�̖@���e�N�X�`���̃T�C�Y

	//////////�����p�̒l//////////
	float Wave1ScrollValue = 0.0004f;	//1�ڂ̔g��UV��1�t���[���ɐi�߂�l
	float Wave2ScrollValue = 0.0005f;	//2�ڂ̔g��UV��1�t���[���ɐi�߂�l
	//////////�����p�̒l//////////
}

namespace nsK2Engine
{
	void SeaModelRender::Update()
	{
		//�e�g��UV���W���X�N���[��������B

		//�X�N���[��������l�����Z
		m_scrollValue.Wave1 += Wave1ScrollValue;
		//�l��1�𒴂�����0�ɖ߂��B
		if (m_scrollValue.Wave1 >= waveTextureSize)
		{
			m_scrollValue.Wave1 = 0.0f;
		}

		//�g2�����l
		m_scrollValue.Wave2 += Wave2ScrollValue;
		if (m_scrollValue.Wave2 >= waveTextureSize)
		{
			m_scrollValue.Wave2 = 0.0f;
		}

		//���f���̃A�b�v�f�[�g
		m_modelRender.Update();
	}
}
