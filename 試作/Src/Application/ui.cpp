#include "ui.h"
#include "Utility.h"

void C_Ui::Init()
{
	m_pos.fill(Math::Vector2::Zero);
	m_mat.fill(Math::Matrix::Identity);
	m_color.fill(Def::Color);
	m_color[Ui::Explanation].A(AlpCrr);
	m_rec[Ui::Hp] = {};
}

void C_Ui::Draw()
{
	for (size_t l_i = NULL; l_i < Ui::All; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTex, m_rec[l_i],m_color[l_i].A());
	}
}

void C_Ui::Update()
{
}