#include "ui.h"
#include "Scene.h"
#include "Utility.h"

void C_Ui::Init(int a_hp)
{
	m_pos.fill(Math::Vector2::Zero);
	m_scal.fill(Math::Vector2::One);
	m_mat.fill(Math::Matrix::Identity);
	m_color.fill(Def::Color);
	m_color[Ui::Explanation].A(AlpCrr);
	m_color[Ui::Lclick] = DefLclickColor;
	m_pos[Ui::Lclick] = LclickPos;
	m_pos[Ui::Timer] = { static_cast<float>(- Screen::HalfWidth + DistTimer/2),static_cast<float>(Screen::HalfHeight - DistTimer/2)};
	m_pos[Ui::BreakNumber] = { static_cast<float>(- Screen::HalfWidth + DistTimer/2),static_cast<float>(Screen::HalfHeight - DistTimer/2)};
	m_pos[Ui::Hp] = { static_cast<float>(- Screen::HalfWidth + DistTimer/2),static_cast<float>(Screen::HalfHeight - DistTimer*2)};
	m_scal[Ui::Explanation] = { ScalExplCrr,ScalExplCrr };
	m_scal[Ui::Lclick]      = { ScalLcliCrr,ScalLcliCrr };
	m_scal[Ui::Timer]       = { ScalTimer,ScalTimer };
	m_scal[Ui::BreakNumber]       = { ScalTimer,ScalTimer };
	m_scal[Ui::Hp]          = { ScalTimer,ScalTimer };
	m_rec[Ui::Hp]           = { NULL,NULL,HpTexRad,HpTexRad };
	m_rec[Ui::Lclick]       = { NULL,NULL,LclickTexW,LclickTexH };
	m_rec[Ui::Explanation]  = { NULL,NULL,Screen::HalfWidth,Screen::HalfHeight };
	m_frame = NULL;
	m_colorChanger = ColorChanger;
	m_rec[Ui::Timer] = { NULL,NULL,TimerW,TimerH };
	m_rec[Ui::BreakNumber] = { NULL,NULL,TimerW,TimerH };
	m_nowHp = a_hp;
	m_lag = NULL;
}

void C_Ui::DrawExplanation()
{
	SHADER.m_spriteShader.SetMatrix(m_mat[Ui::Explanation]);
	SHADER.m_spriteShader.DrawTex(m_pTex, m_rec[Ui::Explanation],m_color[Ui::Explanation].A());
	if (m_frame > FrameLimit &&  m_lag!=NULL)
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
		m_lag = 1;
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
	auto l_timer = SCENE.Timer();
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

void C_Ui::DrawBreakNum()
{
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_breMat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pBreNumTex, NULL, NULL, &m_breRec[l_i], &m_color[Ui::BreakNumber]);
	}
}

void C_Ui::UpdateBreakNum()
{
	auto l_timer = SCENE.GetBreakNumber();
	auto l_hundred = l_timer / 100;
	auto l_teen = (l_timer / 10) % 10;
	auto l_one = l_timer % 10;
	m_breRec[Digit::Hundreds] = { TimerW * l_hundred, NULL, TimerW, TimerH };
	m_breRec[Digit::Tens] = { TimerW * l_teen, NULL, TimerW, TimerH };
	m_breRec[Digit::Ones] = { TimerW * l_one, NULL, TimerW, TimerH };
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos[Ui::BreakNumber].x + (DistTimer * l_i) + 200, m_pos[Ui::BreakNumber].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::BreakNumber].x);
		m_breMat[l_i] = l_scaMat * l_traMat;
	}
}

void C_Ui::InitNumber(float a_y)
{
	m_pos.fill(Math::Vector2::Zero);
	m_scal.fill(Math::Vector2::One);
	m_mat.fill(Math::Matrix::Identity);
	m_color.fill(Def::Color);
	m_pos[Ui::Timer] = { -200,a_y };
	m_scal[Ui::Timer] = { 0.3f,0.3f };
}

void C_Ui::DrawNumber(bool a_b)
{
	Math::Rectangle l_rec;
	if (a_b) l_rec = { 0,0,155,80 };
	else l_rec = { 155,0,185,80 };
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_timerMat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTimerTex, NULL, NULL, &m_timerRec[l_i], &m_color[Ui::Timer]);
	}
	SHADER.m_spriteShader.SetMatrix(m_texMat);
	SHADER.m_spriteShader.DrawTex(m_pTextTex, NULL, NULL, &l_rec, &m_color[Ui::Timer]);
}

void C_Ui::UpdateNumber(int a_num, bool a_bFlg)
{
	if (a_bFlg)
	{
		m_scal[Ui::Timer].x = 0.1f;
		m_pos[Ui::Timer] = Math::Vector2{-Screen::HalfWidth + 200,m_pos[Ui::Timer].y};
	}
	auto l_hundred = a_num / 100;
	auto l_teen = (a_num / 10) % 10;
	auto l_one = a_num % 10;
	m_timerRec[Digit::Hundreds] = { TimerW * l_hundred, NULL, TimerW, TimerH };
	m_timerRec[Digit::Tens] = { TimerW * l_teen, NULL, TimerW, TimerH };
	m_timerRec[Digit::Ones] = { TimerW * l_one, NULL, TimerW, TimerH };
	for (size_t l_i = NULL; l_i < Digit::DigitMax; ++l_i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos[Ui::Timer].x + (100 * l_i), m_pos[Ui::Timer].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Timer].x);
		m_timerMat[l_i] = l_scaMat * l_traMat;
	}
	if (a_bFlg)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(300, m_pos[Ui::Timer].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Timer].x);
		m_texMat = l_scaMat * l_traMat;
	}
	else m_texMat = Math::Matrix::CreateTranslation(300, m_pos[Ui::Timer].y, Def::Vec.z);
}

void C_Ui::DrawHp()
{
	if (m_nowHp == HpNum)
	{
		for (size_t l_i = NULL; l_i < HpNum; ++l_i)
		{
			SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
			SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
		}
	}
	if (m_nowHp == 5)
	{
		for (size_t l_i = NULL; l_i < 5; ++l_i)
		{
			SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
			SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
		}
	}
	if (m_nowHp == 4)
	{
		for (size_t l_i = NULL; l_i < 4; ++l_i)
		{
			SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
			SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
		}
	}
	if (m_nowHp==3)
	{
		for (size_t l_i = NULL; l_i < 3; ++l_i)
		{
			SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
			SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
		}
	}
	else if (m_nowHp == 2)
	{
		for (size_t l_i = NULL; l_i < 2; ++l_i)
		{
			SHADER.m_spriteShader.SetMatrix(m_hpMat[l_i]);
			SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
		}
	}
	else if (m_nowHp == 1)
	{
		SHADER.m_spriteShader.SetMatrix(m_hpMat[0]);
		SHADER.m_spriteShader.DrawTex(m_pHpTex, NULL, NULL, &m_rec[Ui::Hp], &m_color[Ui::Hp]);
	}
	
}

void C_Ui::UpdateHp()
{
	for (size_t l_i = NULL; l_i < HpNum; ++l_i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos[Ui::Hp].x + (DistTimer * l_i), m_pos[Ui::Hp].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal[Ui::Hp].x);
		m_hpMat[l_i] = l_scaMat * l_traMat;
	}
}

void C_Ui::DownHp()
{
	m_nowHp--;
}

void C_Ui::SetTex(KdTexture* a_pTex, KdTexture* a_plClickTex, KdTexture* a_pTimerTex, KdTexture* a_pHpTex, KdTexture* a_pBreNumTex)
{
	m_pTex       = a_pTex;
	m_plClickTex = a_plClickTex;
	m_pTimerTex  = a_pTimerTex;
	m_pHpTex     = a_pHpTex;
	m_pBreNumTex = a_pBreNumTex;
}