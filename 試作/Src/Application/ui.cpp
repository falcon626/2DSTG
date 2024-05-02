#include "ui.h"
#include "Scene.h"
#include "Utility.h"

void C_Ui::Init()
{
	m_pos.fill(Math::Vector2::Zero);
	m_scal.fill(Math::Vector2::One);
	m_mat.fill(Math::Matrix::Identity);
	m_color.fill(Def::Color);
	m_color[Ui::Explanation].A(AlpCrr);
	m_color[Ui::Lclick] = DefLclickColor;
	m_pos[Ui::Lclick] = LclickPos;
	m_pos[Ui::Timer] = { static_cast<float>(- Screen::HalfWidth + DistTimer/2),static_cast<float>(Screen::HalfHeight - DistTimer/2)};
	m_pos[Ui::Hp] = { static_cast<float>(- Screen::HalfWidth + DistTimer/2),static_cast<float>(Screen::HalfHeight - DistTimer*2)};
	m_scal[Ui::Explanation] = { ScalExplCrr,ScalExplCrr };
	m_scal[Ui::Lclick]      = { ScalLcliCrr,ScalLcliCrr };
	m_scal[Ui::Timer]       = { ScalTimer,ScalTimer };
	m_scal[Ui::Hp]          = { ScalTimer,ScalTimer };
	m_rec[Ui::Hp]           = { NULL,NULL,HpTexRad,HpTexRad };
	m_rec[Ui::Lclick]       = { NULL,NULL,LclickTexW,LclickTexH };
	m_rec[Ui::Explanation]  = { NULL,NULL,Screen::HalfWidth,Screen::HalfHeight };
	m_frame = NULL;
	m_colorChanger = ColorChanger;
	m_rec[Ui::Timer] = { NULL,NULL,TimerW,TimerH };
}

void C_Ui::DrawExplanation()
{
	SHADER.m_spriteShader.SetMatrix(m_mat[Ui::Explanation]);
	SHADER.m_spriteShader.DrawTex(m_pTex, m_rec[Ui::Explanation],m_color[Ui::Explanation].A());
	if (m_frame >= FrameLimit)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[Ui::Lclick]);
		SHADER.m_spriteShader.DrawTex(m_plClickTex, NULL, NULL, &m_rec[Ui::Lclick], &m_color[Ui::Lclick]);
	}
}

bool C_Ui::UpdateExplanation()
{
	auto l_flg = false;
	if (Key::IsPushing(Key::L_Click) && m_frame >= FrameLimit) l_flg = true;
	auto l_tarMat = Math::Matrix::CreateTranslation(m_pos[Ui::Explanation].x, m_pos[Ui::Explanation].y, Def::Vec.z);
	auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Explanation].x);
	m_mat[Ui::Explanation] = l_scaMat * l_tarMat;
	if (m_frame <= FrameLimit) m_frame++;
	else
	{
		m_redChanger += m_colorChanger;
		if (m_color[Ui::Lclick].R() < NULL)
		{
			m_redChanger = NULL;
			m_colorChanger *= -Def::AnNull;
		}
		if (m_color[Ui::Lclick].R() > Def::AnNull)
		{
			m_redChanger = Def::AnNull;
			m_colorChanger *= -Def::AnNull;
		}
		m_color[Ui::Lclick].R(m_redChanger);
		l_tarMat = Math::Matrix::CreateTranslation(m_pos[Ui::Lclick].x, m_pos[Ui::Lclick].y, Def::Vec.z);
		l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Lclick].x);
		m_mat[Ui::Lclick] = l_scaMat * l_tarMat;
	}
	return l_flg;
}

void C_Ui::DrawTimer()
{
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_timerMat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTimerTex, NULL, NULL, &m_timerRec[l_i], &m_color[Ui::Timer]);
	}
}

void C_Ui::UpdateTimer()
{
	auto l_timer = 300 - SCENE.Timer();
	auto l_hundred = l_timer / 100;
	auto l_teen = (l_timer / 10) % 10;
	auto l_one = l_timer % 10;
	m_timerRec[Digit::Hundreds] = { TimerW * l_hundred, NULL, TimerW, TimerH };
	m_timerRec[Digit::Tens] = { TimerW * l_teen, NULL, TimerW, TimerH };
	m_timerRec[Digit::Ones] = { TimerW * l_one, NULL, TimerW, TimerH };
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos[Ui::Timer].x + (DistTimer * l_i), m_pos[Ui::Timer].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Timer].x);
		m_timerMat[l_i] = l_scaMat * l_traMat;
	}
}

void C_Ui::DrawHp()
{
	for (size_t l_i = NULL; l_i < HpNum - m_lostHp; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
	}
	
}

void C_Ui::UpdateHp()
{
	for (size_t l_i = NULL; l_i < HpNum - m_lostHp; ++l_i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos[Ui::Hp].x + (DistTimer * l_i), m_pos[Ui::Hp].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Hp].x);
		m_hpMat[l_i] = l_scaMat * l_traMat;
	}
}

void C_Ui::SetTex(KdTexture* a_pTex, KdTexture* a_plClickTex, KdTexture* a_pTimerTex, KdTexture* a_pHpTex)
{
	m_pTex = a_pTex;
	m_plClickTex = a_plClickTex;
	m_pTimerTex = a_pTimerTex;
	m_pHpTex = a_pHpTex;
}