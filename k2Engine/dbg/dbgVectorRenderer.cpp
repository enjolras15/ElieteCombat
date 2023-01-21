#include "k2EnginePreCompile.h"
#include "dbg/dbgVectorRenderer.h"

namespace nsK2Engine {
	namespace nsDbg {
		
		bool VectorRenderer::Start()
		{
			m_modelRender.Init(
				"Assets/modelData/preset/vector.tkm",
				nullptr,
				0,
				enModelUpAxisZ,
				true,
				MAX_VECTOR
			);
			return true;
		}
		bool VectorRenderer::IsRenderVector(const SRenderData& renderData) const
		{
			return true;

			if (m_renderVectorNameList.empty() == true) {
				//�`�悷��x�N�g���̖��O���w�肳��Ă��Ȃ��B
				return true;
			}
			//��ł͂Ȃ��B
			auto it = std::find(
				m_renderVectorNameList.begin(),
				m_renderVectorNameList.end(),
				renderData.name
			);
			//�I�[�܂ōs���Ȃ������B
			return it != m_renderVectorNameList.end();

		}
		void VectorRenderer::Update()
		{

			if (m_isRender == false) {
				return;
			}

			int instanceNum = 0;

			// �C���X�^���V���O�f�[�^���X�V�B
			for (const auto& renderData : m_renderData) {

				if (IsRenderVector(renderData) ){
					Quaternion rot;
					rot.SetRotation(g_vec3AxisZ, renderData.vector);
					float s = renderData.vector.Length();
					m_modelRender.UpdateInstancingData(
						instanceNum,
						renderData.origin,
						rot,
						{ s * 0.2f, s * 0.2f, s }
					);
				}

				instanceNum++;

			}

		}
		
		void VectorRenderer::Render(RenderContext& rc)
		{

			if (m_isRender) {
				m_modelRender.Draw(rc);
			}
			// todo �t�H�g�̕`�揈���͂������񖳌��B
			// �`��f�[�^�̓N���A�B
			m_renderData.clear();

		}
	}
}

