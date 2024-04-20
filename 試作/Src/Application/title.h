#pragma once

class C_Title
{
public:
	void SetTexture(KdTexture* a_pTitleTex, KdTexture* a_pStartTex, KdTexture* a_pOptionTex);
	void Init();
	void Draw();
	size_t Update(POINT a_mouse);

	C_Title(){}
	~C_Title(){}

private:
	enum Title
	{
		TITLE,
		START,
		OPTION,
		ALL
	};
	std::array<bool, ALL> m_bFlg;
	std::array<KdTexture*, ALL> m_tex;
	std::array<Math::Matrix, ALL> m_mat;
	std::array < Math::Color, ALL > m_color;
	std::array < Math::Vector2, ALL > m_pos;
	std::array < Math::Rectangle, ALL > m_rec;
	const Math::Color DefColor = { 1.f,1.f,1.f,1.f };
	const Math::Color StaSelColor = { 0.2f,1.f,1.f,1.f };
	const Math::Color OptSelColor = { 1.f,0.2f,0.2f,1.f };
};