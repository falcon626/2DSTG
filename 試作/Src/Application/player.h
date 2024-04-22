#pragma once
#include"bullet.h"
class C_Timer;
class Scene;

class C_player
{
public:


	C_player();
	~C_player();

	void Init();
	void Update(const POINT a_mouse);
	void Draw();

	void CheckHitBullet();

	void StartTimer();
	int Timer();
	int Time();
	void TimeSum();

	void SetTexture(KdTexture* a_pTex);
	void SetBulletTextrure(KdTexture* a_pTex);
	void SetOwner(Scene* a_pOwner);

private:
	int m_frame;
	KdTexture* m_pTex;
	KdTexture* m_pBulletTex;
	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	std::vector<C_Bullet*> m_bulletList;
	Scene* m_pOwner;

	std::shared_ptr<C_Timer> m_timer;
	bool m_bTimeSun;
	
	int m_bulletInterval;
	int m_maxInterval;
	int m_time;
	bool m_bReload;
	bool m_bTime;
};
