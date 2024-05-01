#include "bullet.h"
#include "Utility.h"

C_Bullet::C_Bullet()
{
	m_pos = Math::Vector2::Zero;
	m_move = Math::Vector2::Zero;
	m_rad = 0.0f;
	m_bAlive = false;
	m_mat = Math::Matrix::Identity;
	m_pTex = nullptr;
}

C_Bullet::~C_Bullet()
{
}

void C_Bullet::Init()
{
	m_move.x = 7.0f;
	m_move.y = 7.0f;
	m_bAlive = false;
	m_bUpdate = false;
}

void C_Bullet::Update(bool a_bTime)
{
	if (!m_bAlive || !a_bTime) return;
	m_bUpdate = true;
	m_pos.x += cos(m_rad) * m_move.x;
	m_pos.y += sin(m_rad) * m_move.y;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	if (m_pos.x>=Screen::Width||m_pos.y>=Screen::Height||m_pos.x<=-Screen::Width||m_pos.y<=-Screen::Height)
	{
		m_bAlive = false;
		m_bUpdate = false;
	}
}

void C_Bullet::Draw()
{
	if (!m_bUpdate)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, 16, 16), 1.0f);
}

void C_Bullet::Shot(Math::Vector2 a_shotPos, float a_targetRad)
{
	m_bAlive = true;
	m_pos = a_shotPos;
	m_rad = a_targetRad;
}

void C_Bullet::Hit()
{
	m_bAlive = false;
	m_bUpdate = false;
}

const bool C_Bullet::GetAlive()
{
	return m_bAlive;
}

const Math::Vector2 C_Bullet::GetPos()
{
	return m_pos;
}

const float C_Bullet::GetRadius()
{
	return TEX_RADIUS;
}

void C_Bullet::SetTexture(KdTexture*a_ptex)
{
	m_pTex = a_ptex;
}
