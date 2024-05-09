#include "text.h"
#include "Utility.h"

void C_Text::Init()
{
	m_pos = {0,0};
	m_count = NULL;
	m_j = NULL;
}

void C_Text::DrawT()
{
	Math::Rectangle l_rec = { 0,0,600,100 };
	SHADER.m_spriteShader.SetMatrix(m_cuiMat);
	SHADER.m_spriteShader.DrawTex(m_pTexTex, NULL, 75, &l_rec, &Def::Color);
	l_rec = { 0,0,150,100 };
	SHADER.m_spriteShader.DrawTex(m_pPngTex, 350, -50, &l_rec, &Def::Color);
	if (m_text.size() == NULL)return;
	for (size_t i = NULL; i < m_text.size(); ++i)
	{
		if (m_CharNum[i] == Key::Slash)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(m_pMarkTex, (500 * i) - (m_text.size() / 2 * 500), 50, &m_rec[i], &Def::Color);
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(m_pTextTex, (500 * i) - (m_text.size() / 2 * 500), NULL, &m_rec[i], &Def::Color);
		}
	}
}

void C_Text::DrawS()
{
	Math::Rectangle l_rec = { 0,0,600,100 };
	SHADER.m_spriteShader.SetMatrix(m_cuiMat);
	SHADER.m_spriteShader.DrawTex(m_pSudTex, NULL, 75, &l_rec, &Def::Color);
	l_rec = { 0,0,150,100 };
	SHADER.m_spriteShader.DrawTex(m_pWavTex, 350, -50, &l_rec, &Def::Color);
	if (m_text.size() == NULL)return;
	for (size_t i = NULL; i < m_text.size(); ++i)
	{
		if (m_CharNum[i] == Key::Slash)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(m_pMarkTex, (500 * i) - (m_text.size() / 2 * 500), 50, &m_rec[i], &Def::Color);
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(m_pTextTex, (500 * i) - (m_text.size() / 2 * 500), NULL, &m_rec[i], &Def::Color);
		}
	}
}

void C_Text::Update()
{
	if (Key::IsPushing(Key::A))
	{
		if (!m_bKey[0])
		{
			m_text.push_back('a');
			m_CharNum.emplace_back(Key::A);
			m_rec.emplace_back(500 * 0, 0, 500, 500);
			m_bKey[0] = true;
		}
	}
	else m_bKey[0] = false;
	if (Key::IsPushing(Key::B))
	{
		if (!m_bKey[1])
		{
			m_text.push_back('b');
			m_CharNum.emplace_back(Key::B);
			m_rec.emplace_back(500 * 1, 0, 500, 500);
			m_bKey[1] = true;
		}
	}
	else m_bKey[1] = false;
	if (Key::IsPushing(Key::C))
	{
		if (!m_bKey[2])
		{
			m_text.push_back('c');
			m_CharNum.emplace_back(Key::C);
			m_rec.emplace_back(500 * 2, 0, 500, 500);
			m_bKey[2] = true;
		}
	}
	else m_bKey[2] = false;
	if (Key::IsPushing(Key::D))
	{
		if (!m_bKey[3])
		{
			m_text.push_back('d');
			m_CharNum.emplace_back(Key::D);
			m_rec.emplace_back(500 * 3, 0, 500, 500);
			m_bKey[3] = true;
		}
	}
	else m_bKey[3] = false;
	if (Key::IsPushing(Key::E))
	{
		if (!m_bKey[4])
		{
			m_text.push_back('e');
			m_CharNum.emplace_back(Key::E);
			m_rec.emplace_back(500 * 4, 0, 500, 500);
			m_bKey[4] = true;
		}
	}
	else m_bKey[4] = false;
	if (Key::IsPushing(Key::F))
	{
		if (!m_bKey[5])
		{
			m_text.push_back('f');
			m_CharNum.emplace_back(Key::F);
			m_rec.emplace_back(500 * 5, 0, 500, 500);
			m_bKey[5] = true;
		}
	}
	else m_bKey[5] = false;
	if (Key::IsPushing(Key::G))
	{
		if (!m_bKey[6])
		{
			m_text.push_back('g');
			m_CharNum.emplace_back(Key::G);
			m_rec.emplace_back(500 * 6, 0, 500, 500);
			m_bKey[6] = true;
		}
	}
	else m_bKey[6] = false;
	if (Key::IsPushing(Key::H))
	{
		if (!m_bKey[7])
		{
			m_text.push_back('h');
			m_CharNum.emplace_back(Key::H);
			m_rec.emplace_back(500 * 7, 0, 500, 500);
			m_bKey[7] = true;
		}
	}
	else m_bKey[7] = false;
	if (Key::IsPushing(Key::I))
	{
		if (!m_bKey[8])
		{
			m_text.push_back('i');
			m_CharNum.emplace_back(Key::I);
			m_rec.emplace_back(500 * 8, 0, 500, 500);
			m_bKey[8] = true;
		}
	}
	else m_bKey[8] = false;
	if (Key::IsPushing(Key::J))
	{
		if (!m_bKey[9])
		{
			m_text.push_back('j');
			m_CharNum.emplace_back(Key::J);
			m_rec.emplace_back(500 * 9, 0, 500, 500);
			m_bKey[9] = true;
		}
	}
	else m_bKey[9] = false;
	if (Key::IsPushing(Key::K))
	{
		if (!m_bKey[10])
		{
			m_text.push_back('k');
			m_CharNum.emplace_back(Key::K);
			m_rec.emplace_back(500 * 10, 0, 500, 500);
			m_bKey[10] = true;
		}
	}
	else m_bKey[10] = false;
	if (Key::IsPushing(Key::L))
	{
		if (!m_bKey[11])
		{
			m_text.push_back('l');
			m_CharNum.emplace_back(Key::L);
			m_rec.emplace_back(500 * 11, 0, 500, 500);
			m_bKey[11] = true;
		}
	}
	else m_bKey[11] = false;
	if (Key::IsPushing(Key::N))
	{
		if (!m_bKey[12])
		{
			m_text.push_back('n');
			m_CharNum.emplace_back(Key::M);
			m_rec.emplace_back(500 * 12, 0, 500, 500);
			m_bKey[12] = true;
		}
	}
	else m_bKey[12] = false;
	if (Key::IsPushing(Key::M))
	{
		if (!m_bKey[13])
		{
			m_text.push_back('m');
			m_CharNum.emplace_back(Key::N);
			m_rec.emplace_back(500 * 13, 0, 500, 500);
			m_bKey[13] = true;
		}
	}
	else m_bKey[13] = false;
	if (Key::IsPushing(Key::O))
	{
		if (!m_bKey[14])
		{
			m_text.push_back('o');
			m_CharNum.emplace_back(Key::O);
			m_rec.emplace_back(500 * 14, 0, 500, 500);
			m_bKey[14] = true;
		}
	}
	else m_bKey[14] = false;
	if (Key::IsPushing(Key::P))
	{
		if (!m_bKey[15])
		{
			m_text.push_back('p');
			m_CharNum.emplace_back(Key::P);
			m_rec.emplace_back(500 * 15, 0, 500, 500);
			m_bKey[15] = true;
		}
	}
	else m_bKey[15] = false;
	if (Key::IsPushing(Key::Q))
	{
		if (!m_bKey[16])
		{
			m_text.push_back('q');
			m_CharNum.emplace_back(Key::Q);
			m_rec.emplace_back(500 * 16, 0, 500, 500);
			m_bKey[16] = true;
		}
	}
	else m_bKey[16] = false;
	if (Key::IsPushing(Key::R))
	{
		if (!m_bKey[17])
		{
			m_text.push_back('r');
			m_CharNum.emplace_back(Key::R);
			m_rec.emplace_back(500 * 17, 0, 500, 500);
			m_bKey[17] = true;
		}
	}
	else m_bKey[17] = false;
	if (Key::IsPushing(Key::S))
	{
		if (!m_bKey[18])
		{
			m_text.push_back('s');
			m_CharNum.emplace_back(Key::S);
			m_rec.emplace_back(500 * 18, 0, 500, 500);
			m_bKey[18] = true;
		}
	}
	else m_bKey[18] = false;
	if (Key::IsPushing(Key::T))
	{
		if (!m_bKey[19])
		{
			m_text.push_back('t');
			m_CharNum.emplace_back(Key::T);
			m_rec.emplace_back(500 * 19, 0, 500, 500);
			m_bKey[19] = true;
		}
	}
	else m_bKey[19] = false;
	if (Key::IsPushing(Key::U))
	{
		if (!m_bKey[20])
		{
			m_text.push_back('u');
			m_CharNum.emplace_back(Key::U);
			m_rec.emplace_back(500 * 20, 0, 500, 500);
			m_bKey[20] = true;
		}
	}
	else m_bKey[20] = false;
	if (Key::IsPushing(Key::V))
	{
		if (!m_bKey[21])
		{
			m_text.push_back('v');
			m_CharNum.emplace_back(Key::V);
			m_rec.emplace_back(500 * 21, 0, 500, 500);
			m_bKey[21] = true;
		}
	}
	else m_bKey[21] = false;
	if (Key::IsPushing(Key::W))
	{
		if (!m_bKey[22])
		{
			m_text.push_back('w');
			m_CharNum.emplace_back(Key::W);
			m_rec.emplace_back(500 * 22, 0, 500, 500);
			m_bKey[22] = true;
		}
	}
	else m_bKey[22] = false;
	if (Key::IsPushing(Key::X))
	{
		if (!m_bKey[23])
		{
			m_text.push_back('x');
			m_CharNum.emplace_back(Key::X);
			m_rec.emplace_back(500 * 23, 0, 500, 500);
			m_bKey[23] = true;
		}
	}
	else m_bKey[23] = false;
	if (Key::IsPushing(Key::Y))
	{
		if (!m_bKey[24])
		{
			m_text.push_back('y');
			m_CharNum.emplace_back(Key::Y);
			m_rec.emplace_back(500 * 24, 0, 500, 500);
			m_bKey[24] = true;
		}
	}
	else m_bKey[24] = false;
	if (Key::IsPushing(Key::Z))
	{
		if (!m_bKey[25])
		{
			m_text.push_back('z');
			m_CharNum.emplace_back(Key::Z);
			m_rec.emplace_back(500 * 25, 0, 500, 500);
			m_bKey[25] = true;
		}
	}
	else m_bKey[25] = false;
	if (Key::IsPushing(Key::Slash) && (Key::IsPushing(Key::L_Shift) || Key::IsPushing(Key::R_Shift)))
	{
		if (!m_bKey[26])
		{
			m_text.push_back('/');
			m_CharNum.emplace_back(Key::Slash);
			m_rec.emplace_back(500 * 0, 0, 500, 500);
			m_bKey[26] = true;
		}
	}
	else m_bKey[26] = false;
	if (Key::IsPushing(Key::BackSpace) && m_text.size() != NULL)
	{
		if (!m_bKey[27])
		{
			m_text.pop_back();
			m_CharNum.pop_back();
			m_rec.pop_back();
			m_bKey[27] = true;
		}
	}
	else m_bKey[27] = false;

	auto l_traMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
	m_cuiMat = l_traMat;

	if (m_text.size() == NULL)return;
	for (size_t i = 0; i < m_text.size(); ++i)
	{
		auto l_traMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, Def::Vec.z);
		auto l_scaMat = Math::Matrix::CreateScale(m_scal);
		auto l_mat = l_scaMat * l_traMat;
		m_mat.emplace_back(l_mat);
	}
}

void C_Text::CreateStr()
{
	m_str.emplace_back(m_text);
}

size_t C_Text::GetSize()
{
	return m_str.size();
}

std::string C_Text::GetPass(int a_i)
{
	return m_str[a_i];
}

std::string C_Text::GetPass()
{
	return m_text;
}

void C_Text::SetTex(KdTexture* a_pTextTex, KdTexture* a_pNumberTex, KdTexture* a_pMarkTex)
{
	m_pTextTex = a_pTextTex;
	m_pNumberTex = a_pNumberTex;
	m_pMarkTex = a_pMarkTex;
}

void C_Text::SetCuiSTex(KdTexture* a_pWavTex, KdTexture* a_pSudTex)
{
	m_pSudTex = a_pSudTex;
	m_pWavTex = a_pWavTex;
}

void C_Text::SetCuiTTex(KdTexture* a_pPngTex, KdTexture* a_pTexTex)
{
	m_pTexTex = a_pTexTex;
	m_pPngTex = a_pPngTex;
}
