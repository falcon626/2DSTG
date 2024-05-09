#pragma once
//#define DEBUG
#include "player.h"
#include "enemy.h"
class C_Title;
class C_Back;
class C_Cloud;
class C_Ui;
class C_Anima;
class C_Bullet;
class C_Text;
class C_Option;

class Scene
{
private:
	bool debag = false;

	POINT m_mouse;
	Math::Matrix m_mat;
	KdTexture m_tex;

	int m_nowScene;
	int m_nextScene;
	bool m_bCut;
	int m_cutCount;
	std::shared_ptr<C_Title> m_title;
	KdTexture m_titleTex;
	KdTexture m_startTex;
	KdTexture m_optionTex;

	std::shared_ptr<C_Back> m_back;
	KdTexture m_backTex;
	KdTexture m_filTex;

	std::shared_ptr<C_Cloud> m_cut;
	std::shared_ptr<C_Cloud> m_cloud;
	KdTexture m_cloudTex;

	const int SceneSwitchCount = 60;
	const int SceneCutEndCount = 65;

	std::shared_ptr<C_Ui> m_ui;
	KdTexture m_explTex;
	KdTexture m_lClickTex;
	KdTexture m_timerTex;
	KdTexture m_hpTex;
	bool m_explFlg;
	bool m_bUpdateFlg;
	int m_directorCount;
	int m_oneStageTime = 90;
	int m_stageNum = 1;

	KdTexture m_playerTex;
	KdTexture m_playerHitTex;
	C_Player m_player;
	KdTexture m_bulletTex;
	std::vector<std::shared_ptr<C_Enemy>> m_enemyList;
	KdTexture m_enemyTex;

	std::vector<std::shared_ptr<C_Enemy>> m_lineEnemyList;
	KdTexture m_lineEnemyTex;

	int breakNum;

	std::vector<std::shared_ptr<C_Anima>>m_anima;
	KdTexture m_hitTex;
	KdTexture m_breTex;
	KdTexture m_textTex;
	KdTexture m_breNumTex;

	KdTexture m_escTex;

	Math::Rectangle m_escRec = { 0, 5, 80, 50 };

	std::vector<std::string> m_strPass;

	float m_vol;

	int m_score;

	int m_time;
	int m_enePop;
	int m_lineEnePop;
	int m_lineEnePopLim;
	int m_bulletEnePop;

	std::array<std::shared_ptr<C_Ui>, 2> m_number;

	std::vector<std::shared_ptr<C_Bullet>> m_bulletList;
	KdTexture m_eneBulletTex;

	std::shared_ptr<C_Text> m_txt;
	KdTexture m_txtTex;
	KdTexture m_markTex;
	KdTexture m_pngTex;
	KdTexture m_texTex;
	KdTexture m_wavTex;
	KdTexture m_sudTex;


	std::shared_ptr<C_Option> m_option;
	KdTexture m_loadTex;
	KdTexture m_checkTex;
	KdTexture m_tagTex;
	KdTexture m_adTex;
	KdTexture m_seTex;

	Math::Rectangle m_a;
	Math::Rectangle m_d;

	std::shared_ptr<KdSoundEffect> m_bgm;
	std::shared_ptr<KdSoundEffect> m_bgm1;
	std::shared_ptr<KdSoundEffect> m_bgm2;
	std::shared_ptr<KdSoundEffect> m_bgm3;
	std::shared_ptr<KdSoundEffect> m_breSe;
	std::shared_ptr<KdSoundInstance> m_breInsSe;
	std::shared_ptr<KdSoundEffect> m_hitSe;
	std::shared_ptr<KdSoundInstance> m_hitInsSe;

	int m_lag;
	int m_gal;
	int m_i;

	bool m_bAllCre;
	KdTexture m_starTex;
	Math::Matrix m_starMat;
	Math::Vector2 m_starPos;
	int m_star;

	float m_y;
	float m_Ay;
	float m_Dy;
	float m_ySpd;


public:

	void Init();

	void Release();

	void Update();

	void EnemyPop();

	void DeleteEnemy();

	void UpdateGame();

	void Draw2D();

	void DrawEsc();

	void DrawPage();

	void ImGuiUpdate();

	void CalcMousePos();

	int Timer();

	int GetBreakNumber();

	void Hit();

	void DrawStar();
	void UpdateStar();

	std::vector<std::shared_ptr<C_Enemy>> GetEnemyList();
	std::vector<std::shared_ptr<C_Enemy>> GetLineEnemyList();

	std::vector<std::shared_ptr<C_Bullet>> GetBulletList();

	std::shared_ptr<C_Anima> GetAnima();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
