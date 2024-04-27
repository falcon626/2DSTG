#include "main.h"
#include "Scene.h"
#include "Utility.h"
#include "title.h"
#include "back.h"
#include "cloud.h"

void Scene::Draw2D()
{
	switch (m_nowScene)
	{
	case Screen::Scene::INITIAL:
		m_back->DrawTitle();
		m_title->Draw();
		break;
	case Screen::Scene::GAME:
		m_back->DrawGame();
		m_enemy.Draw();
		m_player.Draw();
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}
	if (m_bCut)
	{
		m_cloud->Draw();
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
		if (!m_bCut)
		{
			m_back->UpdateTitle();
			m_nextScene = m_title->Update(m_mouse);
		}
		break;
	case Screen::Scene::GAME:
		m_back->UpdateGame();
		m_player.Update(m_mouse);
		m_enemy.Update();
		m_player.CheckHitBullet();
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}
	if (m_nowScene != m_nextScene) m_bCut = true;
	if (m_bCut)
	{
		m_cloud->UpdateCut();
		if (m_cutCount > 60) m_nowScene = m_nextScene;
		if (m_cutCount > 65)
		{
			m_cloud->SetPopFlg(m_bCut);
			m_bCut = m_cloud->GetAlpFlg();
		}
		m_cutCount++;
	}
	else m_cutCount = NULL;

	m_mat = Math::Matrix::CreateTranslation( m_mouse.x,m_mouse.y , Def::Vec.z);
}

void Scene::Init()
{
	m_tex.Load("texture/cursor/cursor.png");

	m_title = std::make_shared<C_Title>();
	m_title->Init();
	m_titleTex.Load("texture/backTexture/title.png");
	m_startTex.Load("texture/cursor/START.png");
	m_optionTex.Load("texture/cursor/OPTION.png");
	m_title->SetTexture(&m_titleTex,&m_startTex,&m_optionTex);

	m_back = std::make_shared<C_Back>();
	m_back->Init();
	m_backTex.Load("texture/backTexture/back.png");
	m_filTex.Load("texture/backTexture/filter.png");
	m_back->SetTexture(&m_backTex, &m_filTex);

	m_playerTex.Load("texture/player.png");
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetBulletTextrure(&m_bulletTex);
	m_player.SetOwner(this);

	m_enemyTex.Load("texture/enemy.png");
	m_enemy.Init();
	m_enemy.SetTexture(&m_enemyTex);

	m_bulletTex.Load("texture/bullet.png");

	m_player.StartTimer();

	m_nowScene = m_nextScene = Screen::Scene::INITIAL;
	m_cloud = std::make_shared<C_Cloud>();
	m_cloudTex.Load("texture/backTexture/cloud_9.png");
	m_cloud->SetTex(&m_cloudTex);
	m_cloud->InitCut();
	m_cutCount = NULL;
	m_bCut = false;

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
		ImGui::Text("%d", m_player.Timer());
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
