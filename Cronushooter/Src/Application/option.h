#pragma once

class C_Option
{
public:
	C_Option(){}
	~C_Option(){}

	void Init();
	void Draw();
	void Update(const POINT a_mouse,std::string a_pass);

	void SetTex(KdTexture* a_pLoadTex);

	KdTexture* GetTempTex();
	bool GetBoolTex();
	bool GetCanLoad();
private:
	KdTexture* m_pLoadTex;
	KdTexture m_tempTex;
	Math::Matrix m_mat;
	Math::Vector2 m_pos;
	Math::Rectangle m_rec;
	Math::Rectangle m_notRec;
	bool m_bLoad;
	bool m_bEntKey;
	bool m_bLclickKey;
	bool m_bSetTex;
	bool m_bNotLoad;
};