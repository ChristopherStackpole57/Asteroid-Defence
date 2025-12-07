// Christopher Stackpole, 12/06/2025

#ifndef RENDER_SERVICE_H
#define RENDER_SERVICE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Services/ServiceInterface.h"

class RenderService : public IService
{
public:
	void Start() override;
	void Shutdown() override;
	void Tick(float dt) override;

	void SetWindowSize(sf::Vector2u new_size);
	void SetWindowTitle(sf::String title);
	void SetWindowBackground(sf::Color new_color);

	bool WindowOpen();
	std::optional<sf::Event> PollEvent();
	void CloseWindow();
private:
	sf::Vector2u window_size = sf::Vector2u(800, 600);
	sf::String window_title = "Window";
	sf::Color window_background_color = sf::Color::Black;

	sf::RenderWindow window;
};

#endif