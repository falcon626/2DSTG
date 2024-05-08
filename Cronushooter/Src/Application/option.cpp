#include "option.h"
#include "Utility.h"

void C_Option::Init()
{
	m_bEntKey = false;
	m_bLclickKey = false;
	m_bLoad = false;
	m_bSetTex = false;
	m_bNotLoad = true;
	m_pos = {NULL,-75};
	m_rec = {0,0,64,64};
	m_notRec = {64,0,64,64};
}

void C_Option::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_rec, &Def::Color);
	if(m_bNotLoad) 
		SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_notRec, &Def::Color);
}

void C_Option::Update(const POINT a_mouse, std::string a_pass)
{
	if (Key::IsPushing(Key::L_Click))
	{
		if (!m_bLclickKey)
		{
			auto x = m_pos.x - a_mouse.x;
			auto y = m_pos.y - a_mouse.y;
			auto dist = sqrt(x * x + y * y);
			if (dist <= 40)
			{
				m_bSetTex = true;
				m_bLoad = m_tempTex.Load("OriginalTexture/" + a_pass + ".png");
			}
			m_bLclickKey = true;
		}
	}
	else if(Key::IsPushing(Key::Enter))
	{
		if (!m_bLclickKey)
		{
			m_bSetTex = true;
			m_bLclickKey = true;
			m_bLoad = m_tempTex.Load("OriginalTexture/" + a_pass + ".png");
		}
	}
	else m_bLclickKey = false;
	if (m_bSetTex)
	{
		if (!m_bLoad) m_bNotLoad = true;
		else m_bNotLoad = false;
	}
	auto l_traMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	m_mat = l_traMat;
}

void C_Option::SetTex(KdTexture* a_pLoadTex)
{
	m_pLoadTex = a_pLoadTex;
}

KdTexture* C_Option::GetTempTex()
{
	return &m_tempTex;
}

bool C_Option::GetBoolTex()
{
	return m_bSetTex;
}

bool C_Option::GetCanLoad()
{
	return m_bNotLoad;
}
