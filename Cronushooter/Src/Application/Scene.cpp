#include "main.h"
#include "Scene.h"
#include "Utility.h"
#include "title.h"
#include "back.h"
#include "bullet.h"
#include "cloud.h"
#include "ui.h"
#include "animation.h"
#include "text.h"
#include "option.h"

void Scene::Draw2D()
{
	switch (m_nowScene)
	{
	case Screen::Scene::INITIAL:
		m_back->DrawTitle();
		m_player.Draw();
		m_back->DrawFilter();
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
				for (decltype(auto) l_bullet : m_bulletList) l_bullet->DrawEne();
				for (decltype(auto) l_eneLis : m_enemyList) l_eneLis->Draw();
				for (decltype(auto) l_eneLis : m_lineEnemyList) l_eneLis->DrawLineEnemy();
				for (decltype(auto) l_anima : m_anima) { l_anima->DrawBra(); l_anima->DrawHit(); }
				m_player.Draw();
				if (m_player.Timer() > 19) m_cloud->Draw();
				if (breakNum > 19)m_cloud->Draw();
				m_ui->DrawTimer();
				m_ui->DrawBreakNum();
			}
			if (m_bUpdateFlg)
			{
				m_ui->DrawHp();
			}
		}
		break;
	case Screen::Scene::PAUSE:
		m_back->DrawGame();
		m_back->DrawFilter();
		DrawOption();
		m_txt->Draw();
		m_option->Draw();
		break;
	case Screen::Scene::RESULT:
		m_back->DrawGame();
		m_cloud->Draw();
		m_back->DrawFilter();
		m_number[0]->DrawNumber(true);
		m_number[1]->DrawNumber();
		break;
	}
	if (m_bCut) m_cut->DrawCut();
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex,Math::Rectangle(0,0,16,16),1.f);
}

void Scene::DrawOption()
{
	SHADER.m_spriteShader.SetMatrix(Def::Mat);
	SHADER.m_spriteShader.DrawTex(&m_escTex, -Screen::HalfWidth + 55, Screen::HalfHeight - 50, &m_escRec, &Def::Color);
	//SHADER.m_spriteShader.DrawTex(&m_arrowTex, , -Screen::HalfHeight+40 , &m_escRec, &Def::Color);

}

void Scene::Update()
{
	this->CalcMousePos();
	switch (m_nowScene)
	{
	case Screen::Scene::INITIAL:
		if (!m_bCut)
		{
			m_time = NULL;
			m_back->UpdateTitle();
			m_player.UpdatePlayerTitle(m_mouse);
			m_nextScene = m_title->Update(m_mouse);
		}
		break;
	case Screen::Scene::GAME:
		m_back->UpdateGame();
		if (!m_explFlg) m_explFlg = m_ui->UpdateExplanation();
		else
		{
			m_directorCount++;
			if (m_directorCount == Def::AnNull)
			{
				m_ui->Init();
				m_player.Init();
				m_cloud->MatrixSet();
				m_player.MatrixSet();
				//EnemyPop();
			}
			if (m_directorCount > 120 && !m_bUpdateFlg)
			{
				m_player.StartTimer();
				m_bUpdateFlg = true;
			}
			if (m_bUpdateFlg)
			{
				m_cloud->Update();
				m_ui->UpdateBreakNum();
				m_ui->UpdateTimer();
				m_ui->UpdateHp();
				m_player.Update(m_mouse);
				UpdateGame();
				for (decltype(auto) l_bullet : m_bulletList) l_bullet->Update({static_cast<float>(m_mouse.x),static_cast<float>(m_mouse.y) });
				for (decltype(auto) l_eneLis : m_enemyList) l_eneLis->Update();
				for (decltype(auto) l_eneLis : m_lineEnemyList) l_eneLis->UpdateLineEnemy(m_player.GetPos());
				for (decltype(auto) l_anima : m_anima) { l_anima->UpdateBra(); l_anima->UpdateHit(); }
				m_player.CheckHitBullet();
				m_player.CheckHitEnemy();
				if (m_ui->GetHp() <= NULL) m_nextScene = Screen::Scene::RESULT;
			}
		}
		break;
	case Screen::Scene::PAUSE:
		m_back->UpdateGame();
		m_txt->Update();
		m_option->Update(m_mouse,m_txt->GetPass());
		if (!m_option->GetCanLoad()) m_player.SetTexture(m_option->GetTempTex(),&m_hitTex);
		break;
	case Screen::Scene::RESULT:
		m_back->UpdateGame();
		m_cloud->Update();
		m_number[0]->UpdateNumber(m_time);
		m_number[1]->UpdateNumber(breakNum);
		break;
	}

	if (Key::IsPushing(Key::Esc)) m_nextScene = Screen::Scene::INITIAL;
	if (m_nowScene != Screen::Scene::GAME)
	{
		m_player.Stop();
	}

	if (m_nowScene != m_nextScene)
	{
		if (m_cutCount == NULL)
		{
			m_time = m_player.Timer();
			m_score += m_time + breakNum;
			m_cut->InitCut();
		}
		m_bCut = true;
		m_directorCount = NULL;
	}
	if (m_bCut)
	{
		m_cut->UpdateCut();
		if (m_cutCount > SceneSwitchCount) m_nowScene = m_nextScene;
		if (m_cutCount > SceneCutEndCount)
		{
			if (m_nowScene == Screen::Scene::GAME)
			{
				breakNum = NULL;
				m_ui->Init();
				m_player.Init();
			}
			else  DeleteEnemy();
			m_cut->SetPopFlg(m_bCut);
			m_bCut = m_cut->GetAlpFlg();
		}
		m_cutCount++;
		if (m_cutCount > 80)m_bCut = false;
	}
	else m_cutCount = NULL;

	if (Key::IsPushing(Key::Q) && Key::IsPushing(Key::L_Shift)) debag = true;
	if (Key::IsPushing(Key::Q) && Key::IsPushing(Key::L_Ctrl)) debag = false;

	m_mat = Math::Matrix::CreateTranslation( m_mouse.x,m_mouse.y , Def::Vec.z);
}

void Scene::UpdateGame()
{
	auto ait = m_anima.begin();

	while (ait != m_anima.end())
	{
		if ((*ait)->GetFlg() == false) ait = m_anima.erase(ait);
		else ait++;
	}

	auto it = m_enemyList.begin();

	while (it != m_enemyList.end())
	{
		if ((*it)->GetAlive() == false)
		{
			m_breInsSe->Play();
			++breakNum;
			std::shared_ptr<C_Anima> anima;
			anima = std::make_shared<C_Anima>();
			anima->SetTex(&m_hitTex, &m_breTex);
			anima->BreAnimaStart((*it)->GetPos());
			m_anima.emplace_back(anima);
			it = m_enemyList.erase(it);
		}
		else it++;
	}
	if (rand() % 1000 < m_enePop)
	{
		std::shared_ptr<C_Enemy> enemy;
		enemy = std::make_shared<C_Enemy>();

		enemy->Init();
		enemy->SetTexture(&m_enemyTex);

		m_enemyList.emplace_back(enemy);
	}

	if (m_player.Timer() > 2)
	{
		it = m_lineEnemyList.begin();
		auto l_count = NULL;
		while (it != m_lineEnemyList.end())
		{
			if ((*it)->GetLineTeamAlive() == false)
			{
				m_breInsSe->Play();
				++breakNum;
				std::shared_ptr<C_Anima> anima;
				anima = std::make_shared<C_Anima>();
				anima->SetTex(&m_hitTex, &m_breTex);
				anima->HitAnimaStart((*it)->GetLinePos());
				m_anima.emplace_back(anima);
				it = m_lineEnemyList.erase(it);
			}
			else
			{
				it++;
				l_count++;
			}
		}
		if (rand() % 1000 < m_lineEnePop && l_count < m_lineEnePopLim)
		{
			std::shared_ptr<C_Enemy> enemy;
			enemy = std::make_shared<C_Enemy>();

			enemy->InitLineEnemy(m_player.GetPos());
			enemy->SetTexture(&m_lineEnemyTex);

			m_lineEnemyList.emplace_back(enemy);
		}
	}

	if (m_player.Timer() > 7)
	{
		if (rand() % 1000 < m_bulletEnePop)
		{
			auto bullet = std::make_shared<C_Bullet>();

			bullet->Init();
			bullet->SetTexture(&m_eneBulletTex);
			bullet->Shot({ m_player.GetPos().x,Screen::HalfHeight + 8 }, { NULL,-5 });

			m_bulletList.emplace_back(bullet);
		}
	}

	if (breakNum > 9)
	{
		m_lineEnePopLim = 5;
		m_bulletEnePop = 150;
	}
}

void Scene::EnemyPop()
{
	auto it = m_enemyList.begin();

	while (it != m_enemyList.end())
	{
		if ((*it)->GetAlive() == false) it = m_enemyList.erase(it);
		else it++;
	}

	for(size_t l_i=NULL;l_i<10;++l_i)
	{
		std::shared_ptr<C_Enemy> enemy;
		enemy = std::make_shared<C_Enemy>();

		enemy->Init();
		enemy->SetTexture(&m_enemyTex);

		m_enemyList.emplace_back(enemy);
	}
}

void Scene::DeleteEnemy()
{
	auto it = m_enemyList.begin();

	while (it != m_enemyList.end())
	{
		it = m_enemyList.erase(it);
	}

	auto lit = m_lineEnemyList.begin();

	while (lit != m_lineEnemyList.end())
	{
		lit = m_lineEnemyList.erase(lit);
	}

	auto bit = m_bulletList.begin();

	while (bit!=m_bulletList.end())
	{
		bit = m_bulletList.erase(bit);
	}

	m_player.DeleteBullet();

	m_enePop = 10;
	m_lineEnePop = 5;
	m_lineEnePopLim = 3;
	m_bulletEnePop = 100;
}

void Scene::Init()
{

	srand(timeGetTime());

	m_breSe = std::make_shared<KdSoundEffect>();

	m_breSe->Load("Sound/damage.wav");
	m_breInsSe = m_breSe->CreateInstance(false);
	m_vol = 0.5f;
	m_breInsSe->SetVolume(m_vol);

	m_enePop = 10;
	m_lineEnePop = 5;
	m_lineEnePopLim = 3;
	m_bulletEnePop = 100;

	m_tex.Load("texture/cursor/cursor.png");

	m_title = std::make_unique<C_Title>();
	m_title->Init();
	m_titleTex.Load("texture/backTexture/title.png");
	m_startTex.Load("texture/cursor/START.png");
	m_optionTex.Load("texture/cursor/OPTION.png");
	m_title->SetTexture(&m_titleTex,&m_startTex,&m_optionTex);

	m_escTex.Load("texture/L00bkJ9fOafwGUG1715197114_1715197116.png");

	m_back = std::make_unique<C_Back>();
	m_back->Init();
	m_backTex.Load("texture/backTexture/back.png");
	m_filTex.Load("texture/backTexture/filter.png");
	m_back->SetTexture(&m_backTex, &m_filTex);

	m_playerTex.Load("texture/fly.png");
	m_playerHitTex.Load("texture/strawberry_moon.png");
	m_player.Init();
	m_player.SetTexture(&m_playerTex,&m_playerHitTex);
	m_player.SetBulletTextrure(&m_bulletTex);
	m_player.SetOwner(this);

	m_enemyTex.Load("texture/flyObj.png");
	m_lineEnemyTex.Load("texture/1enemy.png");

	m_bulletTex.Load("texture/nc.png");
	m_eneBulletTex.Load("texture/Enebullet.png");


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

	m_ui = std::make_shared<C_Ui>();
	m_explTex.Load("texture/cursor/CUI.png");
	m_lClickTex.Load("texture/ClickUi.png");
	m_timerTex.Load("texture/numbers.png");
	m_hpTex.Load("texture/backTexture/hp.png");
	m_textTex.Load("texture/textResult.png");
	m_breNumTex.Load("texture/number.png");
	m_ui->SetTex(&m_explTex, &m_lClickTex,&m_timerTex,&m_hpTex,&m_breNumTex);
	m_ui->Init();
	m_explFlg = false;
	m_bUpdateFlg = false;

	m_number[0]=std::make_shared<C_Ui>();
	m_number[1]=std::make_shared<C_Ui>();
	m_number[0]->SetTextTex(&m_textTex);
	m_number[1]->SetTextTex(&m_textTex);
	m_number[0]->SetTex(&m_explTex, &m_lClickTex, &m_timerTex, &m_hpTex,&m_breNumTex);
	m_number[1]->SetTex(&m_explTex, &m_lClickTex, &m_timerTex, &m_hpTex,&m_breNumTex);
	m_number[0]->InitNumber(200);
	m_number[1]->InitNumber(-100);

	m_score = NULL;

	m_hitTex.Load("texture/hitEf.png");
	m_breTex.Load("texture/explosion.png");

	m_txt = std::make_shared<C_Text>();
	m_txtTex.Load("texture/alphabet.png");
	m_markTex.Load("texture/VOJghqsEY0pb35e1715187123_1715187124.png");
	m_pngTex.Load("texture/4lI7xuTOnubV7Hx1715191277_1715191279.png");
	m_texTex.Load("texture/DuxwAPe1KHeM5eZ1715191194_1715191195.png");
	m_txt->Init();
	m_txt->SetTex(&m_txtTex,&m_timerTex,&m_markTex);
	m_txt->SetCuiTex(&m_pngTex,&m_texTex);

	m_option = std::make_shared<C_Option>();
	m_loadTex.Load("texture/load.png");
	m_option->SetTex(&m_loadTex);
	m_option->Init();
}

void Scene::Release()
{
	m_tex.      Release();
	m_playerTex.Release();
	m_bulletTex.Release();
	m_enemyTex. Release();
	m_lineEnemyTex.Release();
	m_cloudTex. Release();
	m_explTex.  Release();
	m_lClickTex.Release();
	m_timerTex. Release();
	m_backTex.  Release();
	m_eneBulletTex.Release();
	m_breNumTex.Release();
	m_textTex.Release();
}

void Scene::ImGuiUpdate()
{
	
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("%d", m_player.Timer());
		ImGui::Text("%d", breakNum);
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

std::vector<std::shared_ptr<C_Enemy>> Scene::GetLineEnemyList()
{
	return m_lineEnemyList;
}

std::vector<std::shared_ptr<C_Bullet>> Scene::GetBulletList()
{
	return m_bulletList;
}

int Scene::Timer()
{
	return (m_oneStageTime * m_stageNum) - m_player.Timer();
}

int Scene::GetBreakNumber()
{
	return breakNum;
}

void Scene::Hit()
{
	if (debag && 1 >= m_ui->GetHp())return;
	m_ui->DownHp();
}
