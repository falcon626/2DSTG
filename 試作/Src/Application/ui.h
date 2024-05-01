#pragma once

class C_Ui
{
public:
	C_Ui() {}
	~C_Ui() {}

	void Init();
	void DrawExplanation();
	bool UpdateExplanation();

	void SetTex(KdTexture* a_pTex, KdTexture* a_plClickTex);

private:
	enum Ui
	{
		Hp,
		Timer,
		Explanation,
		Lclick,
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
 	KdTexture* m_plClickTex;
	std::array<Math::Vector2, Ui::All> m_pos;
	std::array<Math::Vector2, Ui::All> m_scal;
	std::array<Math::Matrix, Ui::All> m_mat;
	std::array < Math::Color , Ui::All > m_color;
	std::array < Math::Rectangle , Ui::All > m_rec;
	Math::Vector2 m_timerRec;
	int m_frame;
	float m_redChanger;
	float m_colorChanger;
	const int FrameLimit = 10;
	const float AlpCrr = 0.50f;
	const float ScalExplCrr = 1.2f;
	const float ScalLcliCrr = 0.7f;
	const float ColorChanger = 0.05f;
	const int HpTexRad = 720;
	const int LclickTexW = 384;
	const int LclickTexH = 106;
	const Math::Vector2 LclickPos = { 250,-185 };
	const Math::Vector2 TimerTexRad = { 45,95 };
	const Math::Color DefLclickColor = { 0,0,0,AlpCrr };
};