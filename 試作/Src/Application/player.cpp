#include "player.h"
#include "Utility.h"
#include "timer.h"
#include "Scene.h"

C_Player::C_Player()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_mat = Math::Matrix::Identity;
}

C_Player::~C_Player()
{
	
}
void C_Player::Init()
{
	m_timer = std::make_shared<C_Timer>();
	m_pos.x = 0;
	m_pos.y = -150;
}

void C_Player::Update(const POINT a_mouse)
{
	if (Key::IsPushing(Key::A))
	{
		m_pos.x -= 10;
		m_bTime = true;
		TimeSum();
		m_timer->Resume();
	}else if (Key::IsPushing(Key::D))
	{
		m_pos.x += 10;
		m_bTime = true;
		TimeSum();
		m_timer->Resume();
	}else if (Key::IsPushing(Key::S))
	{
		m_pos.y -= 10;
		m_bTime = true;
		TimeSum();
		m_timer->Resume();
	}else if (Key::IsPushing(Key::W))
	{
		m_pos.y += 10;
		m_bTime = true;
		TimeSum();
		m_timer->Resume();
	}else
	{
		m_bTime = false;
		m_timer->Stop();
	}
	if (Key::IsPushing(Key::L_Click) && m_bulletInterval <= 0)
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
	else m_bulletInterval--;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{

	}
	for (int b = 0; b < m_bulletList.size(); b++) m_bulletList[b]->Update(m_bTime);

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
		else it++;
	}
	m_frame++;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Player::Draw()
{
	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Player::CheckHitBullet()
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

void C_Player::StartTimer()
{
	m_timer->Start();
}

int C_Player::Timer()
{
	return m_timer->ElapsedSeconds();
}

int C_Player::Time()
{
	return m_time;
}

void C_Player::TimeSum()
{
	if (m_bTimeSun) return;
	m_time += m_time;
	m_bTimeSun = true;
}

void C_Player::SetTexture(KdTexture* a_pTex)
{
	m_pTex = a_pTex;
}

void C_Player::SetBulletTextrure(KdTexture* a_pTex)
{
	m_pBulletTex = a_pTex;
}

void C_Player::SetOwner(Scene* a_pOwner)
{
	m_pOwner = a_pOwner;
}
