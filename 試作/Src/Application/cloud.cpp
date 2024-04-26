#include"cloud.h"
#include"Utility.h"

C_Cloud::C_Cloud()
    : CloudNum(1000)
    , m_pTex(nullptr)
    , m_mat(Math::Matrix::Identity)
    , m_color(Def::Color)
    , m_pos(Def::Vec.x,Def::Vec.y)
    , m_move(Def::Vec.x,Def::Vec.y)
	, m_bFlg(false)
    , m_scale(Def::AnNull)
{}

int Rand(int a_min, int a_max)
{
	if (a_min == a_max) { return a_min; }
	if (a_min > a_max) { a_min = a_min + a_max; a_max = a_min - a_max; a_min = a_min - a_max; }
	return (rand() % (a_max - a_min) + a_min);
}

void C_Cloud::Init()
{

}

void C_Cloud::InitCut()
{

}

void C_Cloud::Draw()
{
}

void C_Cloud::Update()
{
}

void C_Cloud::UpdateCut()
{

}
