#pragma once

class C_Option
{
public:
	C_Option(){}
	~C_Option(){}

	void Init();

	void Draw();
	void Update(const POINT a_mouse, std::string a_pass);

	void DrawTexture();
	void UpdateTexture(const POINT a_mouse,std::string a_pass);

	void DrawSound();
	void UpdateSound(const POINT a_mouse, std::string a_pass);

	void DrawStatus();
	void UpdateStatus(const POINT a_mouse, std::string a_pass);

	void SetTex(KdTexture* a_pLoadTex,KdTexture* a_pTagTex,KdTexture* a_pCheckTex);
	void SetSeTex(KdTexture* a_pLoadTex,KdTexture* a_pTagTex,KdTexture* a_pCheckTex);
	std::string GetPass();

	KdTexture* GetTempTex();
	std::shared_ptr<KdSoundEffect> GetTempSe();
	bool GetBoolTex();
	bool GetCanLoad();
	bool GetSeCanLoad();
	int GetTexPattern();
	int GetSePattern();

	int GetPg();
private:
	KdTexture* m_pLoadTex;
	KdTexture* m_pTagTex;
	KdTexture* m_pCheckTex;
	KdTexture* m_pSeLoadTex;
	KdTexture* m_pSeTagTex;
	KdTexture* m_pSeCheckTex;
	KdTexture m_tempTex;
	std::shared_ptr<KdSoundEffect> m_tempSe;
	Math::Matrix m_mat;
	std::array<Math::Matrix, 3>m_chMat;
	std::array<Math::Vector2, 3>m_chPos;
	std::array<Math::Rectangle, 3>m_chRec;
	std::array<Math::Rectangle, 3>m_tgRec;
	std::array<Math::Rectangle, 2>m_tgSeRec;
	Math::Vector2 m_pos;
	Math::Rectangle m_rec;
	Math::Rectangle m_notRec;
	std::string m_pass;
	bool m_bLoad;
	bool m_bSeLoad;
	bool m_bEntKey;
	bool m_bLclickKey;
	bool m_bSetTex;
	bool m_bNotLoad;
	bool m_bKey;
	int m_pattern;
	int m_pat;
	int m_pg;
};