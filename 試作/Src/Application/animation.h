#pragma once
class C_Anima
{
public:
	C_Anima() {}
	~C_Anima() {}

	void Draw();
	void Update();

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
};