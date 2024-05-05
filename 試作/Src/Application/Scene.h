#pragma once
#define DEBUG
#include "player.h"
#include "enemy.h"
class C_Title;
class C_Back;
class C_Cloud;
class C_Ui;

class Scene
{
private:
	POINT m_mouse;
	Math::Matrix m_mat;
	KdTexture m_tex;

	int m_nowScene;
	int m_nextScene;
	bool m_bCut;
	int m_cutCount;
	std::shared_ptr<C_Title> m_title;
	KdTexture m_titleTex;
	KdTexture m_startTex;
	KdTexture m_optionTex;

	std::shared_ptr<C_Back> m_back;
	KdTexture m_backTex;
	KdTexture m_filTex;

	std::shared_ptr<C_Cloud> m_cut;
	std::shared_ptr<C_Cloud> m_cloud;
	KdTexture m_cloudTex;

	const int SceneSwitchCount = 60;
	const int SceneCutEndCount = 65;

	std::shared_ptr<C_Ui> m_ui;
	KdTexture m_explTex;
	KdTexture m_lClickTex;
	KdTexture m_timerTex;
	KdTexture m_hpTex;
	bool m_explFlg;
	bool m_bUpdateFlg;
	int m_directorCount;

	KdTexture m_playerTex;
	C_Player m_player;
	KdTexture m_bulletTex;
	std::vector<std::shared_ptr<C_Enemy>> m_enemyList;
	KdTexture m_enemyTex;

	std::vector<std::shared_ptr<C_Enemy>> m_lineEnemyList;
	KdTexture m_lineEnemyTex;

	int breakNum;
public:

	void Init();

	void Release();

	void Update();

	void EnemyPop();

	void UpdateGame();

	void Draw2D();

	void ImGuiUpdate();

	void CalcMousePos();

	int Timer();

	void Hit();

	std::vector<std::shared_ptr<C_Enemy>> GetEnemyList();
	std::vector<std::shared_ptr<C_Enemy>> GetLineEnemyList();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
