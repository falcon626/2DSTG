#pragma once
class C_cloud
{
public:
	C_cloud(){}
	~C_cloud(){}

	void Init();
	void Draw();
	void Update();
	void UpdateCut();

private:
	KdTexture* m_pTex;
	Math::Matrix m_mat;
	Math::Color m_color;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
};