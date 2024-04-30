#pragma once

class C_Ui
{
public:
	C_Ui() {}
	~C_Ui() {}

	void Init();
	void DrawExplanation();
	void UpdateExplanation();

	void SetTex(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:
	enum Ui
	{
		Hp,
		Timer,
		Explanation,
		All
	};
	enum Numbers
	{
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Zero,
		Max
	};
 	KdTexture* m_pTex;
	std::array<Math::Vector2, Ui::All> m_pos;
	std::array<Math::Vector2, Ui::All> m_scal;
	std::array<Math::Matrix, Ui::All> m_mat;
	std::array < Math::Color , Ui::All > m_color;
	std::array < Math::Rectangle , Ui::All > m_rec;
	Math::Vector2 m_timerRec;
	const float AlpCrr = 0.25f;
	const float ScalCrr = 0.25f;
	const int HpTexRad = 720;
	const Math::Vector2 TimerTexRad = { 45,95 };
};