#include "ui.h"
#include "Utility.h"

void C_Ui::Init()
{
	m_pos.fill(Math::Vector2::Zero);
	m_scal.fill(Math::Vector2::One);
	m_mat.fill(Math::Matrix::Identity);
	m_color.fill(Def::Color);
	m_color[Ui::Explanation].A(AlpCrr);
	m_scal[Ui::Explanation] = { ScalCrr,ScalCrr };
	//m_rec[Ui::Hp] = { Def::Vec.x,Def::Vec.y,HpTexRad,HpTexRad };
	//m_rec[Ui::Timer] = { Def::Vec.x,Def::Vec.y,TimerTexRad.x,TimerTexRad.y };
}

void C_Ui::DrawExplanation()
{
	SHADER.m_spriteShader.SetMatrix(m_mat[Ui::Explanation]);
	SHADER.m_spriteShader.DrawTex(m_pTex, m_rec[Ui::Explanation],m_color[Ui::Explanation].A());
}

void C_Ui::UpdateExplanation()
{
	auto l_tarMat = Math::Matrix::CreateTranslation(m_pos[Ui::Explanation].x, m_pos[Ui::Explanation].y, Def::Vec.z);
	auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Explanation].x);
	m_mat[Ui::Explanation] = l_scaMat * l_tarMat;
}