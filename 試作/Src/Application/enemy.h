#pragma once
class C_Enemy
{
public:
	C_Enemy();
	~C_Enemy();

	void Init();
	void Update();
	void Draw();

	const Math::Vector2 GetPos();
	const float GetRadius();
	const bool GetAlive();
	void Hit();
	int GetBreakNum();

	void SetTexture(KdTexture* a_ptex);

private:
	Math::Matrix m_mat;
	KdTexture* m_pTex;
	Math::Vector2 m_pos;
	bool m_eAlive;
	Math::Vector2 m_move;
	int m_breakCount;
	const float TEX_RADIUS = 32.0f;
};