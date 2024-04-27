#pragma once
class C_Cloud
{
public:
	C_Cloud();
	~C_Cloud(){}

	void Init();
	void InitCut();
	void Draw();
	void Update();
	void UpdateCut();

	void SetTex(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetPopFlg(bool a_bFlg) { m_bFlg = a_bFlg; }

	auto GetAlpFlg() { return m_bFlg; }

private:
	static const int CloudNum = 250;
	const float AlpSpd;
	const float AlpBorder;
	const float ScaSpd;
	const int TexRadi;
	const int CloudPatternNum;
	KdTexture* m_pTex;
	std::array<Math::Matrix, CloudNum>   m_mat;
	std::array <Math::Color, CloudNum>   m_color;
	std::array <Math::Vector2, CloudNum> m_scale;
	std::array <Math::Vector2, CloudNum> m_pos;
	std::array <Math::Vector2, CloudNum> m_move;
	std::array <int, CloudNum>           m_cloudPattern;
	float m_alp;
	bool m_bFlg;
};