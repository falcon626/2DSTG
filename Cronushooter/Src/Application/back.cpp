#include "back.h"
#include "Utility.h"

void C_Back::SetTexture(KdTexture* a_pTex,KdTexture* a_pfilTex)
{
	m_pTex    = a_pTex;
	m_pfilTex = a_pfilTex;
}

void C_Back::Init()
{
	m_color    = Def::Color;
	m_sca      = TitleSca;
	m_filcolor = Def::Color;
	m_filcolor.A(FilAlp);
}

void C_Back::DrawFilter()
{
	SHADER.m_spriteShader.SetMatrix(m_filmat);
	SHADER.m_spriteShader.DrawTex(m_pfilTex, Def::Vec.x, Def::Vec.y, &FullRec, &m_filcolor);
}

void C_Back::DrawTitle()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Def::Vec.x, Def::Vec.y, &FullRec, &m_color);
}

void C_Back::UpdateTitle()
{
	auto l_scaMat = Math::Matrix::CreateScale(m_sca.x, m_sca.y, Def::Vec.z);
	auto l_tarMat = Math::Matrix::CreateTranslation(Def::Vec.x, Def::Vec.y, Def::Vec.z);
	m_mat = l_scaMat * l_tarMat;
	m_filmat = Math::Matrix::CreateTranslation(Def::Vec.x, Def::Vec.y, Def::Vec.z);
}

void C_Back::DrawGame()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Def::Vec.x, Def::Vec.y, &m_rec, &m_color);
}

void C_Back::UpdateGame()
{
	m_rec = Math::Rectangle(Screen::Width, Def::Vec.y, Screen::Width, Screen::Height);
	m_mat = Math::Matrix::CreateTranslation(Def::Vec.x, Def::Vec.y, Def::Vec.z);
}

C_Back::C_Back()
	:FullRec(Def::Vec.x,Def::Vec.y,Screen::Width,Screen::Height)
	,TitleSca(1.5f,1.5f)
	,FilAlp(0.7f)
{}
