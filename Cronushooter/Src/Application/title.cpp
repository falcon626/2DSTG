#include"title.h"
#include"Utility.h"

static float RndFunc() noexcept { return static_cast<float>(rand()) / RAND_MAX; }
float (*Rnd)() = RndFunc;

void C_Title::SetTexture(KdTexture* a_pTitleTex, KdTexture* a_pStartTex, KdTexture* a_pOptionTex)
{
	m_tex[TITLE] = a_pTitleTex;
	m_tex[START] = a_pStartTex;
	m_tex[OPTION] = a_pOptionTex;
}

void C_Title::Init()
{
	for (size_t l_count = NULL; l_count < ALL; l_count++)
	{
		m_mat[l_count] = Math::Matrix::Identity;
		m_color[l_count] = Def::Color;
	}
	m_pos[TITLE]    = { -330, 300 };
	m_pos[START]    = { 270, -150 };
	m_pos[OPTION]   = { 500, -200 };
	m_rec[TITLE]    = { 0, 0, 607, 84 };
	m_rec[START]    = { 0, 0, 500, 500 };
	m_rec[OPTION]   = { 0, 0, 500, 500 };
	m_scale[TITLE]  = { 1, 1 };
	m_scale[START]  = { 0.5f, 0.5f };
	m_scale[OPTION] = { 0.3f, 0.3f };
}

void C_Title::Draw()
{
	for (size_t l_count = NULL; l_count < ALL; l_count++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[l_count]);
		SHADER.m_spriteShader.DrawTex(m_tex[l_count], NULL, NULL, &m_rec[l_count], &m_color[l_count]);
	}
}

size_t C_Title::Update(POINT a_mouse)
{
	for (size_t l_count = NULL; l_count < ALL; l_count++)
	{
		auto x = m_pos[l_count].x - a_mouse.x;
		auto y = m_pos[l_count].y - a_mouse.y;
		auto dist = sqrt(x * x + y * y);
		if (dist <= 65)
		{
			m_bFlg[l_count] = true;
		}
		else m_bFlg[l_count] = false;
	}
	if (m_bFlg[TITLE])
	{
		if (Key::IsPushing(Key::L_Click))
		{
			if (!m_bKey[TITLE])
			{
				m_bKey[TITLE]  = true;
				m_color[TITLE] = { Rnd(), Rnd(), Rnd(), 1.f };
			}
		}
		else m_bKey[TITLE] = false;
	}
	if (m_bFlg[START])
	{
		m_color[START] = StaSelColor;
		if (Key::IsPushing(Key::L_Click))
		{
			return Screen::Scene::GAME;
		}
	}
	else m_color[START] = Def::Color;
	if (m_bFlg[OPTION])
	{
		m_color[OPTION] = OptSelColor;
		if (Key::IsPushing(Key::L_Click))
		{
			return Screen::Scene::PAUSE;
		}
	}
	else m_color[OPTION] = Def::Color;
	for (size_t l_count = NULL; l_count < ALL; l_count++) 
	{
		m_scaMat[l_count] = Math::Matrix::CreateScale(m_scale[l_count].x, m_scale[l_count].y, NULL);
		m_traMat[l_count] = Math::Matrix::CreateTranslation(m_pos[l_count].x, m_pos[l_count].y, NULL);
		m_mat[l_count]    = m_scaMat[l_count] * m_traMat[l_count];
	}

	return Screen::Scene::INITIAL;
}