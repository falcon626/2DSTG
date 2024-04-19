#include"player.h"
#include"Scene.h"

C_player::C_player()
{
	m_pos[0].x = 0;
	m_pos[0].y = 0;
	m_mat = Math::Matrix::Identity;
}

C_player::~C_player()
{
	
}
void C_player::Init()
{
	m_pos[0].x = 0;
	m_pos[0].y = -150;
}

void C_player::Update(const POINT a_mouse)
{
	if (GetAsyncKeyState(0x41) & 0x8000)
	{
		m_pos[0].x -= 10;
		m_bTime = true;
	} else if (GetAsyncKeyState(0x44) & 0x8000)
	{
		m_pos[0].x += 10;
		m_bTime = true;
	}
	else if (GetAsyncKeyState(0x53) & 0x8000)
	{
		m_pos[0].y -= 10;
		m_bTime = true;
	}
	else if (GetAsyncKeyState(0x57) & 0x8000)
	{
		m_pos[0].y += 10;
		m_bTime = true;
	}
	else
	{
		m_bTime = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON)&0x8000&&m_bulletInterval<=0)
	{
		m_bulletInterval = 30;
		const float x = a_mouse.x - m_pos[0].x;
		const float y = a_mouse.y - m_pos[0].y;
		const float radian = atan2(y, x);
		C_Bullet* tempBullet = new C_Bullet();
		tempBullet->Init();
		tempBullet->SetTexture(m_pBulletTex);
		tempBullet->Shot(m_pos[0], radian);
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
	m_mat = Math::Matrix::CreateTranslation(m_pos[0].x, m_pos[0].y, 0);
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

void C_player::PastPosMemory(Math::Vector2& a_pos)
{
	static Math::Vector2 prevPos = { 0, 0 };
	if (m_frame % 30 == 0 && (m_pos[0].x != prevPos.x || m_pos[0].y != prevPos.y)) {
		if (m_counter < 20) {
			m_pastPos[m_counter] = m_pos[0];
			m_counter++;
			prevPos = m_pos[0];
		}
		else
		{
			m_counter = 0;
		}
	}
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
