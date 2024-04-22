#include "enemy.h"
#include "Utility.h"
C_Enemy::C_Enemy()
{
	m_eAlive = true;
	m_pTex   = nullptr;
	m_pos.x  = 0;
	m_pos.y  = 0;
	m_move.x = 0;
	m_move.y = 0;
}

C_Enemy::~C_Enemy()
{

}

void C_Enemy::Init()
{
	m_eAlive = false;
	m_pos.x  = 0;
	m_pos.y  = 250;
	m_move.x = 0;
	m_move.y = 5;
}

void C_Enemy::Update()
{
	if (!m_eAlive)
	{
		m_pos.x = rand() % 1217 - 608;
		m_pos.y = 392;
		m_eAlive = true;
	}
	if (!m_eAlive)return;
	m_pos -= m_move;
	if (m_pos.y <= -Screen::HalfHeight)
	{
		m_eAlive = false;
	}
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Enemy::Draw()
{
	if (!m_eAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

const Math::Vector2 C_Enemy::GetPos()
{
	return m_pos;
}

const float C_Enemy::GetRadius()
{
	return TEX_RADIUS;
}

const bool C_Enemy::GetAlive()
{
	return m_eAlive;
}

void C_Enemy::Hit()
{
	m_eAlive = false;
}

void C_Enemy::SetTexture(KdTexture* a_ptex)
{
	m_pTex = a_ptex;
}
