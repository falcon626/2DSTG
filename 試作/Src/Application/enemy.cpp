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
	switch (rand()%4)
	{
	case 0:
		for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
		{
			m_linePos[l_i] = { Screen::HalfWidth + TEX_LINERAD*l_i,Screen::HalfHeight + TEX_LINERAD*l_i };
			const float x = a_vec.x - m_linePos[l_i].x;
			const float y = a_vec.y - m_linePos[l_i].y;
			radian = atan2(y, x);
		}
		break;
	case 1:
		for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
		{
			m_linePos[l_i] = { -Screen::HalfWidth - TEX_LINERAD*l_i,Screen::HalfHeight + TEX_LINERAD*l_i };
			const float x = a_vec.x - m_linePos[l_i].x;
			const float y = a_vec.y - m_linePos[l_i].y;
			radian = atan2(y, x);
		}
		break;
	case 2:
		for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
		{
			m_linePos[l_i] = { Screen::HalfWidth + TEX_LINERAD*l_i,-Screen::HalfHeight - TEX_LINERAD*l_i };
			const float x = a_vec.x - m_linePos[l_i].x;
			const float y = a_vec.y - m_linePos[l_i].y;
			radian = atan2(y, x);
		}
		break;
	case 3:
		for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
		{
			m_linePos[l_i] = { -Screen::HalfWidth - TEX_LINERAD*l_i,-Screen::HalfHeight - TEX_LINERAD*l_i };
			const float x = a_vec.x - m_linePos[l_i].x;
			const float y = a_vec.y - m_linePos[l_i].y;
			radian = atan2(y, x);
		}
		break;
	}
	m_lag = NULL;
	m_eAlive[Line] = true;
	m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
}

void C_Enemy::DrawLineEnemy()
{
	if (!m_eAlive[Line]&&m_lag!=1)return;
	for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
	{
		if (!m_eLineAlive[l_i])continue;
		SHADER.m_spriteShader.SetMatrix(m_lineMat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTex[Normal], Math::Rectangle(TEX_RADIUS, Def::Vec.y, TEX_LINESIZE, TEX_LINESIZE), Def::Color.A());
	}
}

void C_Enemy::UpdateLineEnemy(Math::Vector2 a_vec)
{
	if (!m_eAlive[Line]) return;
	for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
	{
		m_linePos[l_i] += m_move[Line];
		if (!m_bInScreen)
		{
			if ((m_linePos[l_i].x < Screen::HalfWidth && m_linePos[l_i].x > -Screen::HalfWidth) || (m_linePos[l_i].y < Screen::HalfHeight && m_linePos[l_i].y > -Screen::HalfHeight))m_bInScreen = true;
		}
		else
		{
			if (m_linePos[l_i].x > Screen::HalfWidth - TEX_RADIUS || m_linePos[l_i].x < -Screen::HalfWidth + TEX_RADIUS)
			{
				const auto x = a_vec.x - m_linePos[l_i].x;
				const auto y = a_vec.y - m_linePos[l_i].y;
				const auto radian = atan2(y, x);
				m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
			}
			if (m_linePos[l_i].y > Screen::HalfHeight - TEX_RADIUS || m_linePos[l_i].y < -Screen::HalfHeight + TEX_RADIUS)
			{
				const auto x = a_vec.x - m_linePos[l_i].x;
				const auto y = a_vec.y - m_linePos[l_i].y;
				const auto radian = atan2(y, x);
				m_move[Line] = { cos(radian) * 5,sin(radian) * 5 };
			}
		}
		auto l_tarMat = Math::Matrix::CreateTranslation(m_linePos[l_i].x, m_linePos[l_i].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(Scale);
		m_lineMat[l_i] = l_scaMat * l_tarMat;
	}
	
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

const Math::Vector2 C_Enemy::GetLinePos(int a_i)
{
	return m_linePos[a_i];
}

const float C_Enemy::GetLineRadius()
{
	return TEX_LINERAD;
}

const bool C_Enemy::GetLineAlive(int a_i)
{
	return m_eLineAlive[a_i];
}

const bool C_Enemy::GetLineTeamAlive()
{
	auto l_flgCount=NULL;
	for (size_t l_i = NULL; l_i < LINETEAM; ++l_i)
	{
		if (m_eLineAlive[l_i])l_flgCount++;
	};
	if (l_flgCount != NULL) m_eAlive[Line]=true;
	else m_eAlive[Line] = false;
	return m_eAlive[Line];
}

void C_Enemy::LineHit(int a_i)
{
	m_eLineAlive[a_i] = false;
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