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

void C_Bullet::UpdateReverse(bool a_bTime)
{
	if (!m_bAlive || a_bTime) return;
	m_bUpdate = true;
	m_pos.x += cos(m_rad) * m_move.x;
	m_pos.y += sin(m_rad) * m_move.y;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	if (m_pos.x >= Screen::Width || m_pos.y >= Screen::Height || m_pos.x <= -Screen::Width || m_pos.y <= -Screen::Height)
	{
		m_bAlive = false;
		m_bUpdate = false;
	}
}

void C_Bullet::Update(Math::Vector2 a_mousePos)
{
	if (!m_bAlive) return;
	m_bUpdate = true;
	const auto l_vec = m_pos - a_mousePos;
	const auto l_dist = sqrt(l_vec.x * l_vec.x + l_vec.y * l_vec.y);
	if (l_dist < 80)
	{
		if (a_mousePos.x > m_pos.x) m_move.x = -5;
		if (a_mousePos.x < m_pos.x) m_move.x = 5;
	}
	else m_move.x = NULL;
	m_pos += m_move;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	if (m_pos.x >= Screen::Width || m_pos.y >= Screen::Height || m_pos.x <= -Screen::Width || m_pos.y <= -Screen::Height)
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

void C_Bullet::DrawReverse()
{
	if (!m_bUpdate)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle l_rec = { 0,0,16,16 };
	Math::Color l_color = { 1,0,1,1 };
	SHADER.m_spriteShader.DrawTex(m_pTex, NULL, NULL, &l_rec, &l_color);
}

void C_Bullet::DrawEne()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, 16, 16), 1.0f);
}

void C_Bullet::Shot(Math::Vector2 a_shotPos, float a_targetRad)
{
	m_bAlive = true;
	m_pos = a_shotPos;
	m_rad = a_targetRad;
}

void C_Bullet::Shot(Math::Vector2 a_shotPos, Math::Vector2 a_shotMove)
{
	m_bAlive = true;
	m_pos = a_shotPos;
	m_move = a_shotMove;
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
