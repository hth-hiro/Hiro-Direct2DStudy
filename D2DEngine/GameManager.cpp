#include "pch.h"
#include "GameManager.h"
#include <fstream>

void GameManager::Initialize()
{

}

void GameManager::Update()
{

}

void GameManager::AddItem(Item item)
{
}

void GameManager::UseItem(Item item)
{
}

bool GameManager::HasItem(Item item)
{
	return false;
}

void GameManager::UnlockSkill(Skill skill)
{

}

void GameManager::UpgradeSkill(Skill skill)
{

}

bool GameManager::HasSkill(Skill skill)
{
	return false;
}

void GameManager::AddCoins(int amount)
{
}

bool GameManager::SpendCoins(int amount)
{
	return false;
}

void GameManager::SaveGame(const std::string& path)
{
	json j;
	j["Level"] = m_Level;
	j["Coins"] = m_Coins;

	j["TotalTime"] = Time::GetInstance().GetTotalTime();
	j["PlayTime"] = Time::GetInstance().GetPlayTime();

	// 아이템은 보류
	//j["Items"] = json::array();

	j["Skills"] = json::array();
	for (auto& skillData : m_SkillData)
		j["Skills"].push_back({ {"skill", static_cast<int>(skillData.skill)},{"level", skillData.level} });

	std::ofstream file(path);
	if (file.is_open())
	{
		file << j.dump(4);
	}
}

void GameManager::LoadGame(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open()) return;

	json j;
	file >> j;

	m_Level = j.value("Level", 0);
	m_Coins = j.value("Coins", 0);

	float totalTime = j.value("TotalTime", 0.0f);
	float playTime = j.value("PlayTime", 0.0f);

	Time::GetInstance()->SetTotalTime(totalTime);
	Time::GetInstance()->SetPlayTime(playTime);

	m_SkillData.clear();
	for (auto& skill : j["Skills"])
		m_SkillData.push_back({ static_cast<Skill>(skill["skill"].get<int>()), skill["level"].get<int>() });
}
