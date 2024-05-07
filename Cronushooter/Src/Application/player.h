#pragma once
class C_Timer;
class C_Bullet;
class Scene;

class C_Player
{
public:


	C_Player();
	~C_Player();

	void Init();
	void Update(const POINT a_mouse);
	void Draw();

	void CheckHitBullet();
	void CheckHitEnemy();

	void StartTimer();
	int Timer();
	void Stop();

	void MatrixSet();

	void SetTexture(KdTexture* a_pTex,KdTexture* a_pHitTex);
	void SetBulletTextrure(KdTexture* a_pTex);
	void SetOwner(Scene* a_pOwner);

	Math::Vector2 GetPos();

private:
	int m_frame;
	KdTexture* m_pTex;
	KdTexture* m_pHitTex;
	KdTexture* m_pBulletTex;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
	Math::Color m_color = {1,1,1,1};
	std::vector<C_Bullet*> m_bulletList;
	std::vector<C_Bullet*> m_bulletReverseList;
	Scene* m_pOwner;

	std::shared_ptr<C_Timer> m_timer;
	bool m_bTimeSun;

	int m_bulletInterval;
	int m_bulletReverseInterval;
	int m_maxInterval;
	int m_time;
	int m_muteki;
	int m_radi;
	bool m_bAlive;
	bool m_bReload;
	bool m_bTime;
	bool m_bSlow;

	const float PlayerRad = 16.0f;
	const float NormalSpd = 10.0f;
	const float SlowSpd = 3.0f;
};
