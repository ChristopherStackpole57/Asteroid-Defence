// Christopher Stackpole, 12/06/2025

#include <iostream>

#include "InputService.h"

void InputService::Start()
{

}
void InputService::Shutdown()
{

}
void InputService::Tick(float dt)
{

}

// Input Service Registration
void InputService::RegisterInputListener(sf::Keyboard::Scancode bind_target, ISCallback action, bool on_press)
{
	if (on_press)
	{
		key_press_bindings[bind_target].push_back(std::move(action));
		return;
	}
	key_release_bindings[bind_target].push_back(std::move(action));
	return;
}
void InputService::UnregisterInputListener(sf::Keyboard::Scancode bind_target, ISCallback action)
{
	// TODO: Implement unregistering
}
void InputService::RegisterInputListener(sf::Mouse::Button bind_target, ISMCallback action, bool on_press)
{
	if (on_press)
	{
		mouse_press_bindings[bind_target].push_back(std::move(action));
		return;
	}
	mouse_release_bindings[bind_target].push_back(std::move(action));
	return;
}
void InputService::UnregisterInputListener(sf::Mouse::Button bind_target, ISMCallback action)
{
	// TODO: Implement unregistering
}

// Input Service Processing
void InputService::ProcessEvent(const sf::Event& event)
{
	if (const auto* key_pressed = event.getIf<sf::Event::KeyPressed>())
	{
		ProcessInput(key_pressed->scancode, true);
	}
	else if (const auto* key_released = event.getIf<sf::Event::KeyReleased>())
	{
		ProcessInput(key_released->scancode, false);
	}
	else if (const auto* mouse_pressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		ProcessInput(mouse_pressed->button, mouse_pressed->position, true);
	}
	else if (const auto* mouse_released = event.getIf<sf::Event::MouseButtonReleased>())
	{
		ProcessInput(mouse_released->button, mouse_released->position, false);
	}

}
void InputService::ProcessInput(sf::Keyboard::Scancode scancode, bool pressed)
{
	// One liner to determine what the correct binding map is
	std::unordered_map<sf::Keyboard::Scancode, std::vector<ISCallback>>& binding_map = (pressed) ? key_press_bindings : key_release_bindings;
	for (ISCallback callback : binding_map[scancode])
	{
		callback();
	}
}
void InputService::ProcessInput(sf::Mouse::Button button, sf::Vector2i position, bool pressed)
{
	// One liner to determine what the correct binding map is
	std::unordered_map<sf::Mouse::Button, std::vector<ISMCallback>> binding_map = (pressed) ? mouse_press_bindings : mouse_release_bindings;
	for (ISMCallback callback : binding_map[button])
	{
		callback(position);
	}
}