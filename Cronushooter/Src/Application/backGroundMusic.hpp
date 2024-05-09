#pragma once

class C_BackGroundMusic
{
private:
#define SOUND_LIST(_bgm) std::initializer_list<std::shared_ptr<KdSoundEffect>> _bgm
public:
	auto SetBGM(SOUND_LIST(a_sp_bgm), std::string a_name) noexcept 
	{ for (auto i_sp_bgm : a_sp_bgm) m_musica[a_name].emplace_back(i_sp_bgm->CreateInstance(false)); }

	auto Init(bool a_b_clear = false)                     noexcept 
	{ for (decltype(auto) i_pair : m_musica) { m_pattern.insert({ i_pair.first,(!a_b_clear) ? NULL : rand() % m_musica[i_pair.first].size() }); } }

	auto SetVol(float a_vol)                              noexcept 
	{ for (decltype(auto) i_pair : m_musica) m_musica[i_pair.first][m_pattern[i_pair.first]]->SetVolume(a_vol); }

	auto ExceptStop(std::string a_name = "")              noexcept 
	{ for (decltype(auto) i_pair : m_musica) { (i_pair.first == a_name) ? void() : m_musica[i_pair.first][m_pattern[i_pair.first]]->Stop(); } }

	auto Play(std::string a_name)                         noexcept 
	{ ExceptStop(a_name); if (!m_musica[a_name][m_pattern[a_name]]->IsPlay())m_musica[a_name][m_pattern[a_name]]->Play(true); }

	static auto& GetInstace()                             noexcept 
	{ static C_BackGroundMusic Instance; return Instance; }
private:
	C_BackGroundMusic()  noexcept = default;
	~C_BackGroundMusic() noexcept = default;
	std::unordered_map<std::string, std::vector<std::shared_ptr<KdSoundInstance>>> m_musica;
	std::unordered_map<std::string, size_t>                                        m_pattern;
};

#define BGM C_BackGroundMusic::GetInstace()