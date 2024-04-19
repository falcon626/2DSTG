#pragma once
//#define DEBUG
#include "player.h"
#include "enemy.h"
class Scene
{
private:
	POINT m_mouse;
	Math::Matrix m_mat;
	KdTexture m_tex;


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
