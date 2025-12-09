// Christopher Stackpole, 12/06/2025

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Services/ServiceManager.h"
#include "Services/EngineServices/CallService/CallService.h"
#include "Services/EngineServices/RenderService/RenderService.h"
#include "Services/EngineServices/InputService/InputService.h"
#include "Services/EngineServices/ResourceService/ResourceService.h"

#include "Services/EngineServices/RenderService/RenderObject.h"

int main()
{
	// Register Game Services
	Services().RegisterService<CallService>();
	Services().RegisterService<RenderService>();
	Services().RegisterService<InputService>();
	Services().RegisterService<ResourceService>();

	// Obtain pointers to registered services
	CallService* call_service = Services().Get<CallService>();
	RenderService* render_service = Services().Get<RenderService>();
	InputService* input_service = Services().Get<InputService>();
	ResourceService* resource_service = Services().Get<ResourceService>();

	// Set startup priorities
	call_service->SetServiceStartupPriority(render_service, 1);
	call_service->SetServiceStartupPriority(input_service, 0);
	call_service->SetServiceStartupPriority(resource_service, 1);

	// Set tick priorities

	call_service->SetServiceTickPriority(render_service, -1);				// Should generally be the last service to run
	call_service->SetServiceTickPriority(input_service, 1);					// Should generally be the first service to run
	call_service->SetServiceTickPriority(resource_service, 0);				// This can be removed if we choose to not invoke ResourceService.Tick (which doesn't do anything) if we want to squeeze out minimally more performance

	// Configure the game window
	render_service->SetWindowSize(sf::Vector2u(1440, 1080));				// Standard 4:3 ratio
	render_service->SetWindowTitle("Space Game");							// Game title, doesn't matter if fullscreen mode is chosen
	render_service->SetWindowBackground(sf::Color(10, 0, 10));

	// IMAGE RESOURCE TEST
	// Fetch world texture from path
	std::string path = "Resources/planet.bmp";
	sf::Texture& world_texture = resource_service->Load<sf::Texture>(path);

	sf::Sprite world_sprite(world_texture);
	world_sprite.move(sf::Vector2f(770 - 128, 540 - 128));

	RenderObject render_object;
	render_object.drawable = &world_sprite;

	render_service->RegisterRenderObject(render_object);

	// INPUT SERVICE TEST
	// Register Input Event
	auto pressed = []() {
		std::cout << "key pressed" << std::endl;
		};

	auto released = []() {
		std::cout << "key released" << std::endl;
		};

	input_service->RegisterInputListener(sf::Keyboard::Scancode::W, pressed);
	input_service->RegisterInputListener(sf::Keyboard::Scancode::W, released, false);

	// Tell Service Manager to run start on all services, this kicks off proper game execution
	Services().Start();

	while (render_service->WindowOpen())
	{
		// Poll and handle all events
		while (const std::optional event = render_service->PollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				// TODO: Move this to Services().Shutdown() -> requires writing ServiceManager.Shutdown
				render_service->CloseWindow();
			}

			// Input Service does not manage all types of events, so we only want to pass on the managed event types
			if (
				event.has_value() && (
				event->is<sf::Event::KeyPressed>() ||
				event->is<sf::Event::KeyReleased>() ||
				event->is<sf::Event::MouseButtonPressed>() ||
				event->is<sf::Event::MouseButtonReleased>()
				))
			{
				input_service->ProcessEvent(event.value());
			}
		}

		// Send off tick to services with registered time between frames
		Services().Tick(0.1f);
	}

	return 0;
}