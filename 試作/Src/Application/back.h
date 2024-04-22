#pragma once

class C_Back
{
public:

	void SetTexture(KdTexture* a_pTex, KdTexture* a_pfilTex);
	void Init();
	void Draw();
	void Update(int a_nowScene);

	C_Back() {}
	~C_Back() {}

private:

	KdTexture*      m_pTex;
	Math::Matrix    m_mat;
	Math::Rectangle m_rec;
	Math::Color     m_color;
	Math::Vector2   m_sca;

	KdTexture*      m_pfilTex;
	Math::Matrix    m_filmat;
	Math::Rectangle m_filrec;
	Math::Color     m_filcolor;
};