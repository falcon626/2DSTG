#pragma once
#include"bullet.h"
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

	void PastPosMemory(Math::Vector2& a_pos);

	void SetTexture(KdTexture* a_pTex);
	void SetBulletTextrure(KdTexture* a_pTex);
	void SetOwner(Scene* a_pOwner);

private:
	int m_counter;
	int m_frame;
	int wait;
	int arrayNum;
	static const int PastPosNum = 20;
	KdTexture* m_pTex;
	KdTexture* m_pBulletTex;
	std::array<Math::Vector2, PastPosNum> m_pos;
	std::array<Math::Vector2, PastPosNum>m_pastPos;
	Math::Matrix m_mat;
	std::vector<C_Bullet*> m_bulletList;
	Scene* m_pOwner;
	int m_bulletInterval;
	int m_maxInterval;
	int m_reload;
	bool m_bReload;
	bool m_bTime;
};
