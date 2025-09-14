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

	std::string jsonString = j.dump(4);

	std::string encrypted = XOREncryptDecrypt(jsonString, m_key);
	
	std::ofstream file(path, std::ios::binary);
	if (file.is_open())
	{
		file.write(encrypted.c_str(), encrypted.size());
	}
}

void GameManager::LoadGame(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) return;

	std::string encrypted((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	std::string decrypted = XOREncryptDecrypt(encrypted, m_key);

	json j = json::parse(decrypted);

	m_Level = j.value("Level", 0);
	m_Coins = j.value("Coins", 0);

	float totalTime = j.value("TotalTime", 0.0f);
	float playTime = j.value("PlayTime", 0.0f);

	Time::GetInstance().SetTotalTime(totalTime);
	Time::GetInstance().SetPlayTime(playTime);

	m_SkillData.clear();
	for (auto& skill : j["Skills"])
		m_SkillData.push_back({ static_cast<Skill>(skill["skill"].get<int>()), skill["level"].get<int>() });
}

// 암호화 & 복호화
std::string GameManager::XOREncryptDecrypt(const std::string& data, char key)
{
	std::string result = data;

	for (size_t i = 0; i < result.size(); i++)
	{
		result[i] ^= key;
	}

	return result;
}
