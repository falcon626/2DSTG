#pragma once

class C_Ui
{
public:
	C_Ui() {}
	~C_Ui() {}

	void Init(int a_hp=4);
	void DrawExplanation();
	bool UpdateExplanation();

	void DrawTimer();
	void UpdateTimer();

	void DrawBreakNum();
	void UpdateBreakNum();

	void InitNumber(float a_y=NULL);
	void DrawNumber(bool a_b=false);
	void UpdateNumber(int a_num);

	void DrawHp();
	void UpdateHp();

	void DownHp();

	int GetHp() { return m_nowHp; }

	void SetTex(KdTexture* a_pTex, KdTexture* a_plClickTex, KdTexture* a_pTimerTex, KdTexture* a_pHpTex, KdTexture* a_pBreNumTex);

	void SetTextTex(KdTexture* a_pTex) { m_pTextTex = a_pTex; }

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
	static const int HpNum = 6;

	enum Ui
	{
		Hp,
		Timer,
		Explanation,
		Lclick,
		BreakNumber,
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
 	KdTexture* m_pTextTex;
 	KdTexture* m_pBreNumTex;
	std::array<Math::Vector2, Ui::All> m_pos;
	std::array<Math::Vector2, Ui::All> m_scal;
	std::array<Math::Vector2, Digit::DigitMax> m_timerPos;
	std::array<Math::Vector2, Digit::DigitMax> m_brePos;
	std::array<Math::Matrix, Ui::All> m_mat;
	Math::Matrix m_texMat;
	std::array<Math::Matrix , Digit::DigitMax> m_timerMat;
	std::array<Math::Matrix , Digit::DigitMax> m_breMat;
	std::array<Math::Matrix , HpNum> m_hpMat;
	std::array<Math::Color , Ui::All > m_color;
	std::array<Math::Rectangle , Ui::All > m_rec;
	std::array<Math::Rectangle , Digit::DigitMax> m_timerRec;
	std::array<Math::Rectangle , Digit::DigitMax> m_breRec;
	int m_lag;
	int m_frame;
	int m_nowHp;
	float m_redChanger;
	float m_colorChanger;
};