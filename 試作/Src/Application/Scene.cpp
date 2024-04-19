#include "main.h"
#include "Scene.h"
#include "Utility.h"
#include "title.h"

void Scene::Draw2D()
{
	switch (m_nowScene)
	{
	case Screen::Scene::INITIAL:
		m_title->Draw();
		break;
	case Screen::Scene::GAME:
		m_enemy.Draw();
		m_player.Draw();
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex,Math::Rectangle(0,0,16,16),1.f);
}

void Scene::Update()
{
	this->CalcMousePos();
	switch (m_nowScene)
	{
	case Screen::Scene::INITIAL:
		m_nowScene = m_title->Update(m_mouse);
		break;
	case Screen::Scene::GAME:
		m_player.Update(m_mouse);
		m_enemy.Update();
		m_player.CheckHitBullet();
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}

	m_mat = Math::Matrix::CreateTranslation( m_mouse.x,m_mouse.y , 0);
}

void Scene::Init()
{
	m_title = std::make_shared<C_Title>();
	m_tex.Load("texture/cursor/cursor.png");
	m_playerTex.Load("texture/player.png");
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_enemyTex.Load("texture/enemy.png");
	m_enemy.Init();
	m_bulletTex.Load("texture/bullet.png");
	m_enemy.SetTexture(&m_enemyTex);
	m_player.SetBulletTextrure(&m_bulletTex);
	m_titleTex.Load("texture/backTexture/title.png");
	m_startTex.Load("texture/cursor/download.png");
	m_optionTex.Load("texture/cursor/download.png");
	m_title->SetTexture(&m_titleTex,&m_startTex,&m_optionTex);
	m_player.SetOwner(this);
}

void Scene::Release()
{
	m_tex.Release();
	m_playerTex.Release();
	m_bulletTex.Release();
	m_enemyTex.Release();
}

void Scene::ImGuiUpdate()
{
	
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::CalcMousePos()
{
	GetCursorPos(&m_mouse);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse);
	m_mouse.x -= Screen::HalfWidth;
	m_mouse.y -= Screen::HalfHeight;
	m_mouse.y *= -1;
}

C_Enemy* Scene::GetEnemy()
{
	return &m_enemy;
}
