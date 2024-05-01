#include "main.h"
#include "Scene.h"
#include "Utility.h"
#include "title.h"
#include "back.h"
#include "cloud.h"
#include "ui.h"

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
		if (!m_explFlg) m_ui->DrawExplanation();
		else
		{
			if (m_directorCount > 30)
			{
				m_cloud->Draw();
			}
			if (m_directorCount > 60)
			{
				for (decltype(auto) l_eneLis : m_enemyList) l_eneLis->Draw();
				m_player.Draw();
			}
		}
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}
	if (m_bCut) m_cut->DrawCut();
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
		if (!m_explFlg) m_explFlg = m_ui->UpdateExplanation();
		else
		{
			m_directorCount++;
			if (m_directorCount > Def::AnNull)
			{
				m_cloud->MatrixSet();
				m_player.MatrixSet();
				for (decltype(auto) l_eneLis : m_enemyList) l_eneLis->MatrixSet();
			}
			if (m_directorCount > 120)
			{
				m_cloud->Update();
				m_player.Update(m_mouse);
				for (decltype(auto) l_eneLis : m_enemyList) l_eneLis->Update();
				UpdateGame();
				m_player.CheckHitBullet();
			}
		}
		break;
	case Screen::Scene::PAUSE:
		break;
	case Screen::Scene::RESULT:
		break;
	}

	if (m_nowScene != m_nextScene) m_bCut = true;
	if (m_bCut)
	{
		m_cut->UpdateCut();
		if (m_cutCount > SceneSwitchCount) m_nowScene = m_nextScene;
		if (m_cutCount > SceneCutEndCount)
		{
			m_cut->SetPopFlg(m_bCut);
			m_bCut = m_cut->GetAlpFlg();
		}
		m_cutCount++;
	}
	else m_cutCount = NULL;

	m_mat = Math::Matrix::CreateTranslation( m_mouse.x,m_mouse.y , Def::Vec.z);
}

void Scene::UpdateGame()
{
	auto it = m_enemyList.begin();

	while (it != m_enemyList.end())
	{
		if ((*it)->GetAlive() == false) it = m_enemyList.erase(it);
		else it++;
	}

	if (rand() % 100 < 3)
	{
		std::shared_ptr<C_Enemy> enemy;
		enemy = std::make_shared<C_Enemy>();

		enemy->Init();
		enemy->SetTexture(&m_enemyTex);

		m_enemyList.emplace_back(enemy);
	}
}

void Scene::Init()
{
	m_tex.Load("texture/cursor/cursor.png");

	m_title = std::make_unique<C_Title>();
	m_title->Init();
	m_titleTex.Load("texture/backTexture/title.png");
	m_startTex.Load("texture/cursor/START.png");
	m_optionTex.Load("texture/cursor/OPTION.png");
	m_title->SetTexture(&m_titleTex,&m_startTex,&m_optionTex);

	m_back = std::make_unique<C_Back>();
	m_back->Init();
	m_backTex.Load("texture/backTexture/back.png");
	m_filTex.Load("texture/backTexture/filter.png");
	m_back->SetTexture(&m_backTex, &m_filTex);

	m_playerTex.Load("texture/fly.png");
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetBulletTextrure(&m_bulletTex);
	m_player.SetOwner(this);

	m_enemyTex.Load("texture/flyObj.png");

	m_bulletTex.Load("texture/nc.png");

	m_player.StartTimer();

	m_nowScene = m_nextScene = Screen::Scene::INITIAL;
	m_cut = std::make_unique<C_Cloud>();
	m_cloudTex.Load("texture/backTexture/cloud_9.png");
	m_cut->SetTex(&m_cloudTex);
	m_cut->InitCut();
	m_cutCount = NULL;
	m_bCut = false;

	m_cloud = std::make_unique<C_Cloud>();
	m_cloud->SetTex(&m_cloudTex);
	m_cloud->Init();

	m_ui = std::make_unique<C_Ui>();
	m_explTex.Load("texture/cursor/CUI.png");
	m_lClickTex.Load("texture/ClickUi.png");
	m_ui->SetTex(&m_explTex, &m_lClickTex);
	m_ui->Init();
	m_explFlg = false;

}

void Scene::Release()
{
	m_tex.      Release();
	m_playerTex.Release();
	m_bulletTex.Release();
	m_enemyTex. Release();
	m_cloudTex. Release();
	m_backTex.  Release();
}

void Scene::ImGuiUpdate()
{
	
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("%d", m_player.Timer());
		ImGui::Text("%d", m_player.GetBreakNum());
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

std::vector<std::shared_ptr<C_Enemy>> Scene::GetEnemyList()
{
	return m_enemyList;
}
