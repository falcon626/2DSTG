#pragma once
class C_Anima
{
public:
	C_Anima() {}
	~C_Anima() {}

	void HitAnimaStart(Math::Vector2 a_pos);
	void DrawHit();
	void UpdateHit();

	void BreAnimaStart(Math::Vector2 a_pos);
	void DrawBra();
	void UpdateBra();

	bool GetFlg();
	void SetFlg(bool a_bflg);

	void SetTex(KdTexture* a_pHitTex, KdTexture* a_pBreTex);

private:
	KdTexture* m_pHitTex;
	KdTexture* m_pBreTex;
	Math::Matrix m_hitMat;
	Math::Matrix m_breMat;
	Math::Vector2 m_hitVec;
	Math::Vector2 m_breVec;
	float m_hitSca;
	float m_breSca;
	int m_hitFre;
	int m_breFre;
	const int LimHitFre=5;
	const int LimBreFre=6;
	bool m_bHitTrigger=false;
	bool m_bBraTrigger=false;

	bool m_bAlive;
};