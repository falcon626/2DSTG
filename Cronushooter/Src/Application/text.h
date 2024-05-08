#pragma once
class C_Text
{
public:
	C_Text() {}
	~C_Text() {}

	void Init();
	void Draw();
	void Update();

	void CreateStr();

	size_t GetSize();

	std::string GetPass(int a_i);

	std::string GetPass();
	
	void SetTex(KdTexture* a_pTextTex, KdTexture* a_pNumberTex, KdTexture* a_pMarkTex);
	void SetCuiTex(KdTexture* a_pPngTex, KdTexture* a_pTexTex);
private:
	std::string m_text;
	std::vector<std::string> m_str;
	std::vector<size_t> m_CharNum;
	KdTexture* m_pTextTex;
	KdTexture* m_pNumberTex;
	KdTexture* m_pMarkTex;
	KdTexture* m_pTexTex;
	KdTexture* m_pPngTex;

	Math::Matrix m_cuiMat;

	std::vector<Math::Matrix> m_mat;
	Math::Vector2 m_pos;

	std::vector<Math::Rectangle> m_rec;

	float m_scal = 0.1f;

	int m_count;
	int m_j;

	std::array<bool, 100> m_bKey;
};