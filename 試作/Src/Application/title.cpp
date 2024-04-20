#include"title.h"
#include"Utility.h"

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
		m_color[l_count] = DefColor;
	}
	m_pos[TITLE]  = { -165, 150 };
	m_pos[START]  = { 50, -300 };
	m_pos[OPTION] = { 150, -300 };
	m_rec[TITLE]  = { 0, 0, 607, 84 };
	m_rec[START]  = { 0, 0, 500, 500 };
	m_rec[OPTION] = { 0, 0, 500, 500 };
}

void C_Title::Draw()
{
	for (size_t l_count = NULL; l_count < ALL; l_count++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[l_count]);
		SHADER.m_spriteShader.DrawTex(m_tex[l_count], m_pos[l_count].x, m_pos[l_count].y, &m_rec[l_count], &m_color[l_count]);
	}
}

size_t C_Title::Update(POINT a_mouse)
{
	for (size_t l_count = NULL; l_count < ALL; l_count++)
	{
		auto x = m_pos[l_count].x - a_mouse.x;
		auto y = m_pos[l_count].y - a_mouse.y;
		auto dist = sqrt(x * x + y * y);
		if (dist <= 50) m_bFlg[l_count] = true;
		else m_bFlg[l_count] = false;
	}
	if (m_bFlg[TITLE])
	{
		m_pos[TITLE].y += 10;
		if (m_pos[TITLE].y < 410) m_pos[TITLE].y = 410;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{

		}
	}
	if (m_bFlg[START])
	{
		m_color[START] = StaSelColor;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			return Screen::Scene::GAME;
		}
	}
	if (m_bFlg[OPTION])
	{
		m_color[OPTION] = OptSelColor;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			return Screen::Scene::PAUSE;
		}
	}
	for (size_t l_count = NULL; l_count < ALL; l_count++) m_mat[l_count] = Math::Matrix::CreateTranslation(m_pos[l_count].x, m_pos[l_count].y, NULL);

	return Screen::Scene::INITIAL;
}