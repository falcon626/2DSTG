#include"cloud.h"
#include"Utility.h"

C_Cloud::C_Cloud()
    : m_pTex(nullptr)
    , m_mat(Math::Matrix::Identity)
    , m_color(Def::Color)
    , m_pos(Def::Vec.x,Def::Vec.y)
    , m_move(Def::Vec.x,Def::Vec.y)
	, m_bFlg(false)
    , m_scale(Def::AnNull)
{}

void C_Cloud::Init()
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
