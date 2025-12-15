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
			std::unique_ptr<SWORD> sword = std::make_unique<SWORD>();
			SWORD* raw = sword.get();
			swords.emplace_back(std::move(sword));

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

	float delta_angle = 360.f / swords.size();
	sf::Vector2f offset{ 0.f, -300.f };

	int index = 0;
	for (auto&& sword : swords)
	{
		sf::Angle rot = sf::Angle(sf::degrees(delta_angle * (float)index));
		sf::Vector2f rotated = offset.rotatedBy(rot);

		sword->SetPosition(half + rotated);
		sword->SetRotation(rot);
		
		index++;
	}
}