#pragma once

class C_Ui
{
public:
	C_Ui() {}
	~C_Ui() {}

	void Init();
	void Draw();
	void Update();

	void SetTex(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:
	enum Ui
	{
		Hp,
		Timer,
		Explanation,
		All
	};
 	KdTexture* m_pTex;
	std::array<Math::Vector2, All> m_pos;
	std::array<Math::Matrix, All> m_mat;
	std::array < Math::Color , All > m_color;
	std::array < Math::Rectangle , All > m_rec;
	const float AlpCrr = 0.25f;
};