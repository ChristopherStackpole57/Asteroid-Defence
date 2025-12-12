// Christopher Stackpole, 12/06/2025

#include <chrono>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Services/ServiceManager.h"
#include "Services/EngineServices/CallService/CallService.h"
#include "Services/EngineServices/RenderService/RenderService.h"
#include "Services/EngineServices/InputService/InputService.h"
#include "Services/EngineServices/ResourceService/ResourceService.h"

#include "GameObjects/ARC.h"
#include "GameObjects/World.h"

constexpr int WINDOW_WIDTH = 1440;
constexpr int WINDOW_HEIGHT = 1080;
constexpr int HALF_WIDTH = WINDOW_WIDTH / 2;
constexpr int HALF_HEIGHT = WINDOW_HEIGHT / 2;

void RegisterGameServices()
{
	// Register Game Services
	Services().RegisterService<CallService>();
	Services().RegisterService<RenderService>();
	Services().RegisterService<InputService>();
	Services().RegisterService<ResourceService>();
}
void SetRunPriorities()
{
	// Obtain pointers to registered services
	CallService* call_service = Services().Get<CallService>();
	RenderService* render_service = Services().Get<RenderService>();
	InputService* input_service = Services().Get<InputService>();
	ResourceService* resource_service = Services().Get<ResourceService>();

	// Set startup priorities
	call_service->SetServiceStartupPriority(render_service, CLST_PRELOAD_CACHE);
	call_service->SetServiceStartupPriority(input_service, CLST_BASIC_SERVICE);
	call_service->SetServiceStartupPriority(resource_service, CLST_PRELOAD_CACHE);

	// Set tick priorities
	call_service->SetServiceTickPriority(render_service, CLT_FRAMERENDER);
	call_service->SetServiceTickPriority(input_service, CLT_PREFRAME);
	call_service->SetServiceTickPriority(resource_service, CLT_BASIC);
}
void ConfigureGameWindow()
{
	RenderService* render_service = Services().Get<RenderService>();

	// Configure the game window
	render_service->SetWindowSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
	render_service->SetWindowTitle("Space Game");
	render_service->SetWindowBackground(sf::Color(10, 0, 10));
}

int main()
{
	// Setup Game
	RegisterGameServices();
	SetRunPriorities();
	ConfigureGameWindow();

	// Build Game Map
	World world;
	world.SetPosition(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));

	ARC arc;
	arc.SetPosition(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT - 15));

	// Obtain pointers to services
	CallService* call_service = Services().Get<CallService>();
	InputService* input_service = Services().Get<InputService>();
	RenderService* render_service = Services().Get<RenderService>();

	// Tell Service Manager to run start on all services, this kicks off proper game execution
	Services().Start();

	long long prev_time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	while (render_service->WindowOpen())
	{
		// Poll and handle all events
		while (const std::optional event = render_service->PollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				// TODO: Move this to Services().Shutdown() -> requires writing ServiceManager.Shutdown
				// TODO: This also means going throughout and implementing proper resource deallocation
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

		// Send off tick to services with registered time in ms between frames
		long long curr_time = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count();

		//std::cout << curr_time - prev_time << std::endl;
		Services().Tick(curr_time - prev_time);

		prev_time = curr_time;
	}

	return 0;
}