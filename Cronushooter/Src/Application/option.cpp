#include "option.h"
#include "Utility.h"

void C_Option::Init()
{
	m_bEntKey = false;
	m_bLclickKey = false;
	m_bLoad = false;
	m_bSeLoad = false;
	m_bSetTex = false;
	m_bNotLoad = true;
	m_pattern = 1;
	m_pat = 1;
	m_pg = 0;
	m_pos = { NULL,-75 };
	m_rec = { 0,0,64,64 };
	m_notRec = { 64,0,64,64 };
	m_chRec.fill({0, 0, 48, 48});
	m_tgSeRec[0] = { 0,0,55,40 };
	m_tgSeRec[1] = { 55,0,35,40 };
	auto l_i = NULL;
	for (decltype(auto) i_pair : m_chPos)
	{
		i_pair = { static_cast<float>(- 150 + (150 * l_i)),static_cast<float>(- 250)};
		l_i++;
	}
	l_i = NULL;

	for (decltype(auto) i_pair : m_tgRec)
	{
		i_pair = { 105 * l_i,0,105,40 };
		l_i++;
	}
	m_tempSe = std::make_shared<KdSoundEffect>();
}

void C_Option::Draw()
{
	switch (m_pg)
	{
	case 0:
		DrawTexture();
		break;

	case 1:
		DrawSound();
		break;

	case 2:

		break;

	case 3:

		break;

	default:

		break;
	}
}

void C_Option::Update(const POINT a_mouse, std::string a_pass)
{
	if (Key::IsPushing(Key::Uno))
	{
		if (!m_bKey)
		{
			++m_pg;
			if (m_pg > 1)m_pg = 0;
		}
		m_bKey = true;
	}
	else if (Key::IsPushing(Key::Dos))
	{
		if (!m_bKey)
		{
			--m_pg;
			if (m_pg < 0)m_pg = 1;
		}
		m_bKey = true;
	}
	else m_bKey = false;
	switch (m_pg)
	{
	case 0:
		UpdateTexture(a_mouse, a_pass);
		break;

	case 1:
		UpdateSound(a_mouse,a_pass);
		break;

	case 2:

		break;

	case 3:

		break;

	default:

		break;
	}
}

void C_Option::DrawTexture()
{
	for (size_t i = NULL; i < m_chMat.size(); ++i)
	{
		SHADER.m_spriteShader.SetMatrix(m_chMat[i]);
		SHADER.m_spriteShader.DrawTex(m_pCheckTex, NULL, NULL, &m_chRec[i], &Def::Color);
		SHADER.m_spriteShader.DrawTex(m_pTagTex, NULL, -48, &m_tgRec[i], &Def::Color);
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_rec, &Def::Color);
	if(m_bNotLoad) 
		SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_notRec, &Def::Color);
}

void C_Option::UpdateTexture(const POINT a_mouse, std::string a_pass)
{
	auto x = m_pos.x - a_mouse.x;
	auto y = m_pos.y - a_mouse.y;
	auto dist = sqrt(x * x + y * y);
	if (dist <= 40)
	{
		m_pos.y = -70;
		if (Key::IsPushing(Key::L_Click))
		{
			if (!m_bLclickKey)
			{
				m_bSetTex = true;
				m_pass = "OriginalTexture/" + a_pass + ".png";
				m_bLoad = m_tempTex.Load(m_pass);
			}
			m_bLclickKey = true;
		}
		else m_bLclickKey = false;
	}
	else m_pos.y = -75;
	if(Key::IsPushing(Key::Enter))
	{
		if (!m_bEntKey)
		{
			m_bSetTex = true;
			m_pass = "OriginalTexture/" + a_pass + ".png";
			m_bLoad = m_tempTex.Load(m_pass);
		}
		m_bEntKey = true;
	}
	else m_bEntKey = false;
	if (m_bSetTex)
	{
		if (!m_bLoad) m_bNotLoad = true;
		else m_bNotLoad = false;
		m_bSetTex = false;
	}

	for (size_t i = NULL; i < m_chPos.size(); ++i)
	{
		x = m_chPos[i].x - a_mouse.x;
		y = m_chPos[i].y - a_mouse.y;
		dist = sqrt(x * x + y * y);
		if (dist < 48)
		{
			if (Key::IsPushing(Key::L_Click))
			{
				if (!m_bLclickKey)
				{
					m_pattern = i + 1;
				}
				m_bLclickKey = true;
			}
			else m_bLclickKey = false;
		}
	}
	switch (m_pattern)
	{
	case 1:
		m_chRec[0] = { 48, 0, 48, 48 };
		m_chRec[1] = { 0, 0, 48, 48 };
		m_chRec[2] = { 0, 0, 48, 48 };
		break;
	case 2:
		m_chRec[0] = { 0, 0, 48, 48 };
		m_chRec[1] = { 48, 0, 48, 48 };
		m_chRec[2] = { 0, 0, 48, 48 };
		break;
	case 3:
		m_chRec[0] = { 0, 0, 48, 48 };
		m_chRec[1] = { 0, 0, 48, 48 };
		m_chRec[2] = { 48, 0, 48, 48 };
		break;
	default:
		break;
	}

	auto l_traMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	m_mat = l_traMat;
	for (size_t i=NULL;i<m_chMat.size();++i)
		m_chMat[i] = Math::Matrix::CreateTranslation(m_chPos[i].x, m_chPos[i].y, Def::Vec.z);
}

void C_Option::DrawSound()
{
	for (size_t i = NULL; i < m_chMat.size() - 1; ++i)
	{
		SHADER.m_spriteShader.SetMatrix(m_chMat[i]);
		SHADER.m_spriteShader.DrawTex(m_pCheckTex, NULL, NULL, &m_chRec[i], &Def::Color);
		SHADER.m_spriteShader.DrawTex(m_pSeTagTex, NULL, -48, &m_tgSeRec[i], &Def::Color);
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_rec, &Def::Color);
	if (m_bNotLoad)
		SHADER.m_spriteShader.DrawTex(m_pLoadTex, NULL, NULL, &m_notRec, &Def::Color);
}

void C_Option::UpdateSound(const POINT a_mouse, std::string a_pass)
{
	auto x = m_pos.x - a_mouse.x;
	auto y = m_pos.y - a_mouse.y;
	auto dist = sqrt(x * x + y * y);
	if (dist <= 40)
	{
		m_pos.y = -70;
		if (Key::IsPushing(Key::L_Click))
		{
			if (!m_bLclickKey)
			{
				m_bSetTex = true;
				m_pass = "OriginalSound/" + a_pass + ".wav";
				m_bSeLoad = m_tempSe->Load(m_pass);
			}
			m_bLclickKey = true;
		}
		else m_bLclickKey = false;
	}
	else m_pos.y = -75;
	if (Key::IsPushing(Key::Enter))
	{
		if (!m_bEntKey)
		{
			m_bSetTex = true;
			m_pass = "OriginalSound/" + a_pass + ".wav";
			m_bSeLoad = m_tempSe->Load(m_pass);
		}
		m_bEntKey = true;
	}
	else m_bEntKey = false;
	if (m_bSetTex)
	{
		if (!m_bSeLoad) m_bNotLoad = true;
		else m_bNotLoad = false;
		m_bSetTex = false;
	}

	for (size_t i = NULL; i < m_chPos.size() - 1; ++i)
	{
		x = m_chPos[i].x - a_mouse.x;
		y = m_chPos[i].y - a_mouse.y;
		dist = sqrt(x * x + y * y);
		if (dist < 48)
		{
			if (Key::IsPushing(Key::L_Click))
			{
				if (!m_bLclickKey)
				{
					m_pat = i + 1;
				}
				m_bLclickKey = true;
			}
			else m_bLclickKey = false;
		}
	}
	switch (m_pat)
	{
	case 1:
		m_chRec[0] = { 48, 0, 48, 48 };
		m_chRec[1] = { 0, 0, 48, 48 };
		m_chRec[2] = { 0, 0, 48, 48 };
		break;
	case 2:
		m_chRec[0] = { 0, 0, 48, 48 };
		m_chRec[1] = { 48, 0, 48, 48 };
		m_chRec[2] = { 0, 0, 48, 48 };
		break;
	default:
		break;
	}

	auto l_traMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	m_mat = l_traMat;
	for (size_t i = NULL; i < m_chMat.size() - 1; ++i)
		m_chMat[i] = Math::Matrix::CreateTranslation(m_chPos[i].x, m_chPos[i].y, Def::Vec.z);
}

void C_Option::DrawStatus()
{

}

void C_Option::UpdateStatus(const POINT a_mouse, std::string a_pass)
{

}

void C_Option::SetTex(KdTexture* a_pLoadTex, KdTexture* a_pTagTex, KdTexture* a_pCheckTex)
{
	m_pLoadTex = a_pLoadTex;
	m_pTagTex = a_pTagTex;
	m_pCheckTex = a_pCheckTex;
}

void C_Option::SetSeTex(KdTexture* a_pLoadTex, KdTexture* a_pTagTex, KdTexture* a_pCheckTex)
{
	m_pSeLoadTex = a_pLoadTex;
	m_pSeCheckTex = a_pCheckTex;
	m_pSeTagTex = a_pTagTex;
}

std::string C_Option::GetPass()
{
	return m_pass;
}

KdTexture* C_Option::GetTempTex()
{
	return &m_tempTex;
}

std::shared_ptr<KdSoundEffect> C_Option::GetTempSe()
{
	return m_tempSe;
}

bool C_Option::GetBoolTex()
{
	return m_bSetTex;
}

bool C_Option::GetCanLoad()
{
	return m_bLoad;
}

bool C_Option::GetSeCanLoad()
{
	return m_bSeLoad;
}

int C_Option::GetTexPattern()
{
	return m_pattern;
}

int C_Option::GetSePattern()
{
	return m_pat;
}

int C_Option::GetPg()
{
	return m_pg;
}
