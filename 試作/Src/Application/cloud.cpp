#include"cloud.h"
#include"Utility.h"

C_Cloud::C_Cloud()
	: AlpSpd(0.85f)
	, AlpBorder(0.001f)
	, AlpBack(0.5f)
	, ScaSpd(0.250f)
	, TexRadi(32)
	, BackCloudNum(8)
	, BackCloudSizMax(4)
	, BackCloudSizMin(1)
	, CloudPatternNum(8)
	, CloudSpdMax(20)
	, CloudSpdMin(5)
	, m_pTex(nullptr)
    , m_mat()
    , m_color()
    , m_scale()
    , m_pos()
    , m_move()
	, m_cloudPattern()
	, m_alp(Def::AnNull)
	, m_bFlg(false)
{}

int Rand(int a_min, int a_max) noexcept
{
	if (a_min == a_max) { return a_min; }
	if (a_min > a_max) { a_min = a_min + a_max; a_max = a_min - a_max; a_min = a_min - a_max; }
	return (rand() % (a_max - a_min) + a_min);
}

void C_Cloud::Init()
{
	for (size_t l_i = NULL; l_i < CloudNum / BackCloudNum; ++l_i)
	{
		m_pos[l_i].x = Rand(-Screen::HalfWidth, Screen::HalfWidth);
		m_pos[l_i].y = Rand(-Screen::HalfHeight, Screen::HalfHeight);
		m_move[l_i]  = Math::Vector2{ NULL, static_cast<float>(Rand(CloudSpdMin, CloudSpdMax)) };
		m_color[l_i] = Def::Color;
		m_scale[l_i].x = static_cast<float>(Rand(BackCloudSizMin, BackCloudSizMax));
		m_cloudPattern[l_i] = TexRadi * (Rand(Def::Vec.x, CloudPatternNum));
	}
	m_alp = AlpBack;
}

void C_Cloud::InitCut()
{
	for (size_t l_i = NULL; l_i < CloudNum; ++l_i)
	{
		m_pos[l_i].x        = Rand(-Screen::HalfWidth, Screen::HalfWidth);
		m_pos[l_i].y        = Rand(-Screen::HalfHeight, Screen::HalfHeight);
		m_scale[l_i]        = Math::Vector2::Zero;
		m_move[l_i]         = Math::Vector2{ ScaSpd, ScaSpd};
		m_color[l_i]        = Def::Color;
		m_cloudPattern[l_i] = TexRadi * (Rand(Def::Vec.x, CloudPatternNum));
	}
	m_alp = Def::AnNull;
	m_bFlg = false;
}

void C_Cloud::Draw()
{
	for (size_t l_i = NULL; l_i < CloudNum / BackCloudNum; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(m_cloudPattern[l_i], Def::Vec.y, TexRadi, TexRadi), m_alp);
	}
}

void C_Cloud::DrawCut()
{
	if (m_bFlg)
	{
		m_alp *= AlpSpd;
		if (m_alp <= AlpBorder)
		{
			m_bFlg = false;
			m_alp  = NULL;
		}
	}
	for (size_t l_i = NULL; l_i < CloudNum; ++l_i)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[l_i]);
		SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle( m_cloudPattern[l_i], Def::Vec.y, TexRadi, TexRadi), m_alp);
	}
}

void C_Cloud::Update()
{
	for (size_t l_i = NULL; l_i < CloudNum / BackCloudNum; ++l_i)
	{
		m_pos[l_i] -= m_move[l_i];
		if (m_pos[l_i].y < (-Screen::HalfHeight - TexRadi))
		{
			m_scale[l_i].x = static_cast<float>(Rand(Def::AnNull, BackCloudNum));
			m_pos[l_i] = Math::Vector2(static_cast<float>( Rand(- Screen::HalfWidth, Screen::HalfWidth)), Screen::HalfHeight + TexRadi);
		}
		auto l_tarMat = Math::Matrix::CreateTranslation(m_pos[l_i].x, m_pos[l_i].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scale[l_i].x);
		m_mat[l_i] = l_scaMat * l_tarMat;
	}
}

void C_Cloud::UpdateCut()
{
	for (size_t l_i = NULL; l_i < CloudNum; ++l_i)
	{
		m_scale[l_i] += m_move[l_i];
		auto l_tarMat = Math::Matrix::CreateTranslation(m_pos[l_i].x, m_pos[l_i].y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scale[l_i].x);
		m_mat[l_i]    = l_scaMat * l_tarMat;
	}
}