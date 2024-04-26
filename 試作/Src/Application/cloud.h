#pragma once
class C_Cloud
{
public:
	C_Cloud();
	~C_Cloud(){}

	void Init();
	void Draw();
	void Update();
	void UpdateCut();

	void SetPopFlg(bool a_bFlg) { m_bFlg = a_bFlg; }

private:
	KdTexture* m_pTex;
	Math::Matrix m_mat;
	Math::Color m_color;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	bool m_bFlg;
	float m_scale;
};