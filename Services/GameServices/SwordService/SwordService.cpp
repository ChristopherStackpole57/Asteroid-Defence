// Christopher Stackpole, 12/15/2025

#include "SwordService.h"

#include "GameObjects/SWORD.h"

void SwordService::Start()
{
	// Bind Callback to create starts
	InputService* input_service = Services().Get<InputService>();
	input_service->RegisterInputListener(sf::Keyboard::Scancode::S,
		[this]()
		{
			// Create SWORD and hold it in list
			PoolService* pool_service = Services().Get<PoolService>();
			SWORD* sword = pool_service->Get<SWORD>();
			sword->ResetHealth();

			swords.insert(sword);

			this->UpdateSwordPositions();
		}
	);
}
void SwordService::Shutdown()
{

}
void SwordService::Tick(float dt)
{

}

void SwordService::UpdateSwordPositions()
{
	RenderService* render_service = Services().Get<RenderService>();
	sf::Vector2u size = render_service->GetWindowSize();
	sf::Vector2f half{ size.x / 2.f, size.y / 2.f };

	// Identify Active Swords
	std::vector<SWORD*> active_swords;
	for (SWORD* sword : swords)
	{
		if (sword->GetActive())
		{
			active_swords.push_back(sword);
		}
	}

	float delta_angle = 360.f / active_swords.size();
	sf::Vector2f offset{ 0.f, -300.f };

	int index = 0;
	for (SWORD* sword : active_swords)
	{
		sf::Angle rot = sf::Angle(sf::degrees(delta_angle * (float)index));
		sf::Vector2f rotated = offset.rotatedBy(rot);

		sword->SetPosition(half + rotated);
		sword->SetRotation(rot);
		
		index++;
	}
}