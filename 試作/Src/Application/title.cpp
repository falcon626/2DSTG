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
	for (size_t l_count = 0; l_count < ALL; l_count++) m_mat[l_count] = Math::Matrix::Identity;
	m_pos[TITLE] = { -300,400 };
	m_pos[START] = { 50,-300 };
	m_pos[OPTION] = { 150,-300 };
}

void C_Title::Draw()
{
	SHADER.m_spriteShader.DrawTex(&m_tex[TITLE], nullptr, 1.0f);
}

size_t C_Title::Update(POINT a_mouse)
{
	for (size_t l_count = 0; l_count < ALL; l_count++)
	{
		auto x = m_pos[l_count].x - a_mouse.x;
		auto y = m_pos[l_count].y - a_mouse.y;
		auto dist = sqrt(x * x + y * y);
		if (dist <= 50) m_bFlg[l_count] = true;
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
	return Screen::Scene::INITIAL;
}