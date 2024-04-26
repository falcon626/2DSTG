#include "player.h"
#include "timer.h"
#include "Scene.h"

C_player::C_player()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_mat = Math::Matrix::Identity;
}

C_player::~C_player()
{
	
}
void C_player::Init()
{
	m_timer = std::make_shared<C_Timer>();
	m_pos.x = 0;
	m_pos.y = -150;
}

void C_player::Update(const POINT a_mouse)
{
	if (GetAsyncKeyState(0x41) & 0x8000)
	{
		m_pos.x -= 10;
		m_bTime = true;
		TimeSum();
		m_timer->resume();
	}else if (GetAsyncKeyState(0x44) & 0x8000)
	{
		m_pos.x += 10;
		m_bTime = true;
		TimeSum();
		m_timer->resume();
	}else if (GetAsyncKeyState(0x53) & 0x8000)
	{
		m_pos.y -= 10;
		m_bTime = true;
		TimeSum();
		m_timer->resume();
	}else if (GetAsyncKeyState(0x57) & 0x8000)
	{
		m_pos.y += 10;
		m_bTime = true;
		TimeSum();
		m_timer->resume();
	}else
	{
		m_bTime = false;
		m_timer->stop();
	}
	if (GetAsyncKeyState(VK_LBUTTON)&0x8000&&m_bulletInterval<=0)
	{
		m_bulletInterval = 30;
		const float x = a_mouse.x - m_pos.x;
		const float y = a_mouse.y - m_pos.y;
		const float radian = atan2(y, x);
		C_Bullet* tempBullet = new C_Bullet();
		tempBullet->Init();
		tempBullet->SetTexture(m_pBulletTex);
		tempBullet->Shot(m_pos, radian);
		m_bulletList.push_back(tempBullet);
	}
	else
	{
		m_bulletInterval--;
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{

	}
	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update(m_bTime);
	}

	std::vector<C_Bullet*>::iterator it;
	it = m_bulletList.begin();
	while (it!=m_bulletList.end())
	{
		const bool bAlive = (*it)->GetAlive();
		if (!bAlive)
		{
			delete (*it);
			it = m_bulletList.erase(it);
		}
		else
		{
			it++;
		}
	}
	m_frame++;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_player::Draw()
{
	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_player::CheckHitBullet()
{
	auto enemy = m_pOwner->GetEnemy();
	if (!enemy->GetAlive())return;
	for (size_t b = 0; b < m_bulletList.size(); b++)
	{
		const auto x = enemy->GetPos().x-m_bulletList[b]->GetPos().x;
		const auto y = enemy->GetPos().y-m_bulletList[b]->GetPos().y;
		const auto z = sqrt(x * x + y * y);
		const auto hitDist = enemy->GetRadius() + m_bulletList[b]->GetRadius();
		if (z < hitDist)
		{
			enemy->Hit();
			m_bulletList[b]->Hit();
		}
	}
}

void C_player::StartTimer()
{
	m_timer->start();
}

int C_player::Timer()
{
	return m_timer->elapsedSeconds();
}

int C_player::Time()
{
	return m_time;
}

void C_player::TimeSum()
{
	if (m_bTimeSun) return;
	m_time += m_time;
	m_bTimeSun = true;
}

void C_player::SetTexture(KdTexture* a_pTex)
{
	m_pTex = a_pTex;
}

void C_player::SetBulletTextrure(KdTexture* a_pTex)
{
	m_pBulletTex = a_pTex;
}

void C_player::SetOwner(Scene* a_pOwner)
{
	m_pOwner = a_pOwner;
}
