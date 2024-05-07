#include "animation.h"
#include "Utility.h"

void C_Anima::HitAnimaStart(Math::Vector2 a_pos)
{
	m_hitFre=NULL;
	m_hitVec = a_pos;
	m_hitSca = 0.5f;
	m_bHitTrigger = true;
	m_bAlive = true;
}

void C_Anima::DrawHit()
{
	if (!m_bHitTrigger)return;
	SHADER.m_spriteShader.SetMatrix(m_hitMat);
	SHADER.m_spriteShader.DrawTex(m_pHitTex, Math::Rectangle(128*m_hitFre,0,128,128), Def::Color.A());
}

void C_Anima::UpdateHit()
{
	if (!m_bHitTrigger)return;
	auto l_tarMat = Math::Matrix::CreateTranslation(m_hitVec.x, m_hitVec.y, Def::Vec.z);
	auto l_scaMat = Math::Matrix::CreateScale(m_hitSca);
	m_hitMat = l_scaMat * l_tarMat;
	if(m_hitFre<LimHitFre)m_hitFre++;
	else
	{
		m_hitFre = NULL;
		m_bHitTrigger = false;
		m_bAlive = false;
	}
}

void C_Anima::BreAnimaStart(Math::Vector2 a_pos)
{
	m_breFre = NULL;
	m_breVec = a_pos;
	m_breSca = 2.0f;
	m_bBraTrigger = true;
	m_bAlive = true;
}

void C_Anima::DrawBra()
{
	if (!m_bBraTrigger)return;
	SHADER.m_spriteShader.SetMatrix(m_breMat);
	SHADER.m_spriteShader.DrawTex(m_pBreTex, Math::Rectangle(32*m_breFre, 0, 32, 32), Def::Color.A());
}

void C_Anima::UpdateBra()
{
	if (!m_bBraTrigger)return;
	auto l_tarMat = Math::Matrix::CreateTranslation(m_breVec.x, m_breVec.y, Def::Vec.z);
	auto l_scaMat = Math::Matrix::CreateScale(m_breSca);
	m_breMat = l_scaMat * l_tarMat;
	if(m_breFre<LimBreFre)m_breFre++;
	else
	{
		m_breFre = NULL;
		m_bBraTrigger = false;
		m_bAlive = false;
	}
}

bool C_Anima::GetFlg()
{
	return m_bAlive;
}

void C_Anima::SetFlg(bool a_bflg)
{
	m_bAlive = a_bflg;
}

void C_Anima::SetTex(KdTexture* a_pHitTex, KdTexture* a_pBreTex)
{
	m_pHitTex = a_pHitTex;
	m_pBreTex = a_pBreTex;
}