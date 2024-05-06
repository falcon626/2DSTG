#pragma once

class C_Enemy
{
public:
	C_Enemy();
	~C_Enemy();

	void Init();
	void Update();
	void Draw();

	void InitLineEnemy(Math::Vector2 a_vec);
	void DrawLineEnemy();
	void UpdateLineEnemy(Math::Vector2 a_vec);

	const Math::Vector2 GetPos();
	const float GetRadius();
	const bool GetAlive();
	void Hit();

	const Math::Vector2 GetLinePos(int a_i);
	const float GetLineRadius();
	const bool GetLineAlive(int a_i);
	const bool GetLineTeamAlive();
	void LineHit(int a_i);

	void MatrixSet();

	void SetTexture(KdTexture* a_ptex);
	void SetLineEnemyTex(KdTexture* a_pLineEnemyTex);

private:
	enum Enemy
	{
		Normal,
		Line,
		AllRange
	};
	enum Line
	{
		Fast,
		Second,
		Third,
		Forth,
		Fifth,
		Team
	};
	static const int LINETEAM = Forth;
	int m_lag=NULL;
	bool m_bInScreen;
	std::array<Math::Matrix, AllRange> m_mat;
	std::array<Math::Matrix, Team> m_lineMat;
	std::array<KdTexture*, AllRange> m_pTex;
	std::array<Math::Vector2, AllRange> m_pos;
	std::array<Math::Vector2, Team> m_linePos;
	std::array<bool, AllRange> m_eAlive;
	std::array<bool, Team> m_eLineAlive;
	std::array<Math::Vector2, AllRange> m_move;
	std::array<int, AllRange> m_hp;
	std::array<int, Team> m_lineHp;
	const float Scale=1.f;
	const float TEX_RADIUS = 32.0f;
	const float TEX_LINERAD = 64.0f;
	const int TEX_SIZE = 64;
	const float TEX_LINESIZE = 64.0f;
};