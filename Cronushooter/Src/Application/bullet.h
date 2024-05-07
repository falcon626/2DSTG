#pragma once
class C_Bullet
{
public:
	C_Bullet();
	~C_Bullet();

	void Init();
	void Update(bool a_bTime);
	void UpdateReverse(bool a_bTime);
	void Update(Math::Vector2 a_mousePos);
	void Draw();
	void DrawReverse();
	void DrawEne();

	void Shot(Math::Vector2 a_shotPos,float a_targetRad);
	void Shot(Math::Vector2 a_shotPos,Math::Vector2 a_shotMove);
	void Hit();
	const bool GetAlive();
	const Math::Vector2 GetPos();
	const float GetRadius();

	void SetTexture(KdTexture* a_ptex);
private:
	Math::Matrix m_mat;
	KdTexture* m_pTex;
	Math::Vector2 m_pos;
	bool m_bAlive;
	bool m_bUpdate;
	bool m_bReverse;
	Math::Vector2 m_move;
	float m_rad;
	const float TEX_RADIUS = 8.0f;
};
