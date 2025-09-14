#pragma once
#include "Singleton.h"
#include "json.hpp"
#include "Time.h"

using json = nlohmann::json;

// GameManager 안에서 플레이 기록을 저장할 예정
enum class Item
{
	Potion
};

enum class Skill
{
	Runner,
	Teleporter,
	Hunter,
	Elf,
	Bomber,
	ShadowMage,
	Warlock,
	Shaman
};

struct SkillData
{
	Skill skill;
	int level = 0;
};

struct ItemData
{
	Item item;
	int count = 0;
};

class GameManager : public Singleton<GameManager>
{
public:
	GameManager() = default;
	~GameManager() = default;

	void Initialize();
	void Update();

	// Item
	void AddItem(Item item);
	void UseItem(Item item);
	bool HasItem(Item item);

	// Skill
	void UnlockSkill(Skill skill);
	void UpgradeSkill(Skill skill);
	bool HasSkill(Skill skill);

	// Coins
	void AddCoins(int amount);
	bool SpendCoins(int amount);

	// Level
	int GetLevel() const { return m_Level; }
	void SetLevel(int level) { m_Level = level; }

	// Progress
	float GetProgress() const { return m_Progress; }
	void SetProgress(float value) { m_Progress = value; }

	// Save & Load
	void SaveGame(const std::string& path);
	void LoadGame(const std::string& path);


private:
	// PlayerData
	int m_Level = 0;
	int m_Coins = 0;
	float m_Progress;

	std::vector<ItemData>  m_Items;
	std::vector<SkillData>  m_SkillData;

	char m_key = 0x5A;
	std::string XOREncryptDecrypt(const std::string& data, char key);
};

