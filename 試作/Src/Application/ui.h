#pragma once

class C_Ui
{
public:
	C_Ui() {}
	~C_Ui() {}

	void Init();
	void DrawExplanation();
	bool UpdateExplanation();

	void DrawTimer();
	void UpdateTimer();

	void DrawHp();
	void UpdateHp();

	void DownHp();

	void SetTex(KdTexture* a_pTex, KdTexture* a_plClickTex, KdTexture* a_pTimerTex, KdTexture* a_pHpTex);

private:
	const int FrameLimit = 10;
	const float AlpCrr = 0.50f;
	const float ScalExplCrr = 1.2f;
	const float ScalLcliCrr = 0.7f;
	const float ScalTimer = 0.1f;
	const float ColorChanger = 0.05f;
	const int HpTexRad = 720;
	const int LclickTexW = 384;
	const int LclickTexH = 106;
	const int TimerW = 500;
	const int TimerH = 500;
	const int DistTimer = 50;
	const Math::Vector2 LclickPos = { 250,-185 };
	const Math::Color DefLclickColor = { 0,0,0,AlpCrr };
	static const int HpNum = 3;

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
	enum Digit
	{
		Hundreds,
		Tens,
		Ones,
		DigitMax
	};
 	KdTexture* m_pTex;
 	KdTexture* m_plClickTex;
 	KdTexture* m_pTimerTex;
 	KdTexture* m_pHpTex;
	std::array<Math::Vector2, Ui::All> m_pos;
	std::array<Math::Vector2, Ui::All> m_scal;
	std::array<Math::Vector2, Digit::DigitMax> m_timerPos;
	std::array<Math::Matrix, Ui::All> m_mat;
	std::array<Math::Matrix , Digit::DigitMax> m_timerMat;
	std::array<Math::Matrix , HpNum> m_hpMat;
	std::array<Math::Color , Ui::All > m_color;
	std::array<Math::Rectangle , Ui::All > m_rec;
	std::array<Math::Rectangle , Digit::DigitMax> m_timerRec;
	int m_frame;
	int m_nowHp;
	float m_redChanger;
	float m_colorChanger;
};