// Christopher Stackpole, 12/15/2025

#ifndef SWORD_SERVICE_H
#define SWORD_SERVICE_H

#include <memory>
#include <set>
#include <deque>

#include "ServiceControl.h"
#include "Services.h"

constexpr float SWORD_COST = 30.f;

constexpr float SWORD_BASE_MODIFIER_DAMAGE = 1.f;
constexpr float SWORD_BASE_MODIFIER_FIRERATE = 1.f;

constexpr float SWORD_UPGRADE_COST_GROWTH = 0.25f;
constexpr float SWORD_UPGRADE_BASE_DAMAGE_COST = 20.f;
constexpr float SWORD_UPGRADE_BASE_FIRERATE_COST = 20.f;
constexpr float SWORD_UPGRADE_INCREMENT_DAMAGE = 1.f;
constexpr float SWORD_UPGRADE_INCREMENT_FIRERATE = 0.25f;

class SWORD;
class SwordService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

	void UpdateSwordPositions();
	void AddOreAmount(float amount);
	float GetDamageModifier();
	float GetFirerateModifier();
private:
	float damage_modifier = SWORD_BASE_MODIFIER_DAMAGE;
	float firerate_modifier = SWORD_BASE_MODIFIER_FIRERATE;
	float ore = 0.f;
	std::set<SWORD*> swords;

	// Upgrade icons
	std::string icon_sword_path = "Resources/icon_sword.bmp";
	std::string icon_damage_path = "Resources/icon_damage.bmp";
	std::string icon_firerate_path = "Resources/icon_firerate.bmp";

	std::unique_ptr<sf::Sprite> icon_sword;
	std::unique_ptr<sf::Sprite> icon_damage;
	std::unique_ptr<sf::Sprite> icon_firerate;

	std::deque<RenderObject> render_objects;

	std::unique_ptr<sf::Sprite> MakeSprite(std::string path, sf::Vector2f position);
};

#endif