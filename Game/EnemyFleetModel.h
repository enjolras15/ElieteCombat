#pragma once
	class  EnemyFleetModel : public IGameObject
	{

	public:
		EnemyFleetModel();
		~EnemyFleetModel();

		void Update();

		void Render(RenderContext& rc);
		Vector3 pos[5];
		Quaternion rot[5];
		int Available[5] = { 0,0,0,0,0 };

		int num = 5;

	private:
		ModelRender modelRender[5];

	};

