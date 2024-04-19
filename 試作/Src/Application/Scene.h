#pragma once
//#define DEBUG
#include "player.h"
#include "enemy.h"
class C_Title;
class Scene
{
private:
	POINT m_mouse;
	Math::Matrix m_mat;
	KdTexture m_tex;

	int m_nowScene;
	std::shared_ptr<C_Title> m_title;
	KdTexture m_titleTex;
	KdTexture m_startTex;
	KdTexture m_optionTex;


	KdTexture m_playerTex;
	C_player m_player;
	KdTexture m_bulletTex;
	std::vector<C_Enemy*> m_enemyList;
	C_Enemy m_enemy;
	KdTexture m_enemyTex;
public:

	void Init();

	void Release();

	void Update();

	void Draw2D();

	void ImGuiUpdate();

	void CalcMousePos();

	C_Enemy* GetEnemy();

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
