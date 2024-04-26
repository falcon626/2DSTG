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

private:
	static const int CloudNum = 1000;
	KdTexture* m_pTex;
	std::array<Math::Matrix, CloudNum>   m_mat;
	std::array <Math::Color, CloudNum>   m_color;
	std::array <Math::Vector2, CloudNum> m_scale;
	std::array <Math::Vector2, CloudNum> m_pos;
	std::array <Math::Vector2, CloudNum> m_move;
	bool m_bFlg;
};