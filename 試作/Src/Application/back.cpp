#include "back.h"

void C_Back::SetTexture(KdTexture* a_pTex,KdTexture* a_pfilTex)
{
	m_pTex    = a_pTex;
	m_pfilTex = a_pfilTex;
}

void C_Back::Init()
{
	m_color    = { 1, 1, 1, 1 };
	m_rec      = { 0, 150, 1024, 1024 };
	m_sca      = { 1.5f, 1.5f };
	m_filcolor = { 1, 1, 1, 0.6f };
	m_filrec   = { 0, 0, 1280, 720 };
}

void C_Back::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, NULL, NULL, &m_rec, &m_color);
	SHADER.m_spriteShader.SetMatrix(m_filmat);
	SHADER.m_spriteShader.DrawTex(m_pfilTex, NULL, NULL, &m_filrec, &m_filcolor);
}

void C_Back::Update(int a_nowScene)
{
	auto l_scaMat = Math::Matrix::CreateScale(m_sca.x, m_sca.y, 0);
	auto l_tarMat = Math::Matrix::CreateTranslation(0,0,0);
	m_mat = l_scaMat * l_tarMat;
	m_filmat = Math::Matrix::CreateTranslation(0,0,0);
}
