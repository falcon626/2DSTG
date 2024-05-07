#include "enemy.h"
#include "animation.h"
#include "Utility.h"
C_Enemy::C_Enemy()
{
	m_eAlive[Normal] = true;
	m_pTex[Normal] = nullptr;
	m_pos[Normal].x  = 0;
	m_pos[Normal].y  = 0;
	m_move[Normal].x = 0;
	m_move[Normal].y = 0;
}

C_Enemy::~C_Enemy()
{
}

void C_Enemy::Init()
{
	m_eAlive[Normal] = false;
	m_pos[Normal].x  = 0;
	m_pos[Normal].y  = 250;
	m_move[Normal].x = 0;
	m_move[Normal].y = 5;
	m_hp[Normal] = 2;
}

void C_Enemy::Update()
{
	if (!m_eAlive[Normal])
	{
		m_pos[Normal].x = rand() % 1217 - 608;
		m_pos[Normal].y = 392;
		m_eAlive[Normal] = true;
	}
	if (!m_eAlive[Normal])return;
	m_pos[Normal] -= m_move[Normal];
	if (m_pos[Normal].y <= -Screen::HalfHeight - TEX_RADIUS)
	{
		m_pos[Normal].x = rand() % 1217 - 608;
		m_pos[Normal].y = 392;
		//m_eAlive = true;
	}
	m_mat[Normal] = Math::Matrix::CreateTranslation(m_pos[Normal].x, m_pos[Normal].y, Def::Vec.z);
}

void C_Enemy::Draw()
{
	if (!m_eAlive[Normal])return;
	SHADER.m_spriteShader.SetMatrix(m_mat[Normal]);
	SHADER.m_spriteShader.DrawTex(m_pTex[Normal], Math::Rectangle(Def::Vec.x, Def::Vec.y, TEX_SIZE, TEX_SIZE), Def::Color.A());
}

void C_Enemy::InitLineEnemy(Math::Vector2 a_vec)
{
	m_bInScreen = false;
	float radian=NULL;
	float x = NULL;
	float y = NULL;
	switch (rand()%4)
	{
	case 0:
		m_pos[Line] = { Screen::HalfWidth + TEX_LINERAD,Screen::HalfHeight + TEX_LINERAD };
		x = a_vec.x - m_pos[Line].x;
		y = a_vec.y - m_pos[Line].y;
		radian = atan2(y, x);
		break;
	case 1:
		
		m_pos[Line] = { -Screen::HalfWidth - TEX_LINERAD,Screen::HalfHeight + TEX_LINERAD };
		x = a_vec.x - m_pos[Line].x;
		y = a_vec.y - m_pos[Line].y;
		radian = atan2(y, x);
		break;
	case 2:
		m_pos[Line] = { Screen::HalfWidth + TEX_LINERAD,-Screen::HalfHeight - TEX_LINERAD };
		x = a_vec.x - m_pos[Line].x;
		y = a_vec.y - m_pos[Line].y;
		radian = atan2(y, x);
		break;
	case 3:
		m_pos[Line] = { -Screen::HalfWidth - TEX_LINERAD,-Screen::HalfHeight - TEX_LINERAD };
		x = a_vec.x - m_pos[Line].x;
		y = a_vec.y - m_pos[Line].y;
		radian = atan2(y, x);
		break;
	}
	m_lag = NULL;
	m_eAlive[Line] = true;
	m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
}

void C_Enemy::DrawLineEnemy()
{
	if (!m_eAlive[Line]&&m_lag!=1)return;
	SHADER.m_spriteShader.SetMatrix(m_mat[Line]);
	SHADER.m_spriteShader.DrawTex(m_pTex[Normal], Math::Rectangle(TEX_RADIUS, Def::Vec.y, TEX_LINESIZE, TEX_LINESIZE), Def::Color.A());
}

void C_Enemy::UpdateLineEnemy(Math::Vector2 a_vec)
{
	if (!m_eAlive[Line]) return;
	m_pos[Line] += m_move[Line];
	if (!m_bInScreen)
	{
		if ((m_pos[Line].x < Screen::HalfWidth && m_pos[Line].x > -Screen::HalfWidth) || (m_pos[Line].y < Screen::HalfHeight && m_pos[Line].y > -Screen::HalfHeight))m_bInScreen = true;
	}
	else
	{
		if (m_pos[Line].x > Screen::HalfWidth || m_pos[Line].x < -Screen::HalfWidth)
		{
			const auto x = a_vec.x - m_pos[Line].x;
			const auto y = a_vec.y - m_pos[Line].y;
			const auto radian = atan2(y, x);
			m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
		}
		if (m_pos[Line].y > Screen::HalfHeight || m_pos[Line].y < -Screen::HalfHeight)
		{
			const auto x = a_vec.x - m_pos[Line].x;
			const auto y = a_vec.y - m_pos[Line].y;
			const auto radian = atan2(y, x);
			m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
		}
	}
	auto l_tarMat = Math::Matrix::CreateTranslation(m_pos[Line].x, m_pos[Line].y, Def::Vec.z);
	auto l_scaMat = Math::Matrix::CreateScale(Scale);
	m_mat[Line] = l_scaMat * l_tarMat;
	m_lag = 1;
}

const Math::Vector2 C_Enemy::GetPos()
{
	return m_pos[Normal];
}

const float C_Enemy::GetRadius()
{
	return TEX_RADIUS;
}

const bool C_Enemy::GetAlive()
{
	return m_eAlive[Normal];
}

void C_Enemy::Hit()
{
	if (m_hp[Normal] != 1)
	{
		m_hp[Normal]--;
	}
	else
	{
		m_eAlive[Normal] = false;
	}
}

const Math::Vector2 C_Enemy::GetLinePos()
{
	return m_pos[Line];
}

const float C_Enemy::GetLineRadius()
{
	return TEX_LINERAD;
}

const bool C_Enemy::GetLineAlive()
{
	return m_eAlive[Line];
}

const bool C_Enemy::GetLineTeamAlive()
{
	return m_eAlive[Line];
}

void C_Enemy::LineHit()
{
	m_eAlive[Line] = false;
}

void C_Enemy::MatrixSet()
{
	SHADER.m_spriteShader.SetMatrix(m_mat[Normal]);
	SHADER.m_spriteShader.DrawTex(m_pTex[Normal], Math::Rectangle(Def::Vec.x, Def::Vec.y, TEX_SIZE, TEX_SIZE), Def::Color.A());
}

void C_Enemy::SetTexture(KdTexture* a_ptex)
{
	m_pTex[Normal] = a_ptex;
}