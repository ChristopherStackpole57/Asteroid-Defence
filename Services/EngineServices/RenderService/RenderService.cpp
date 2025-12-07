// Christopher Stackpole, 12/06/2025

#include <iostream>

#include "RenderService.h"

void RenderService::Start()
{
	window = sf::RenderWindow(sf::VideoMode(window_size), window_title);
}

void RenderService::Shutdown()
{

}

void RenderService::Tick(float d)
{
	// Enter the primary rendering loop
	// Start by setting the background color for the window
	window.clear(window_background_color);

	// Render the results of all operations thus far
	window.display();
}

// Render Service Behavior
void RenderService::SetWindowSize(sf::Vector2u new_size)
{
	window_size = new_size;
}

void RenderService::SetWindowTitle(sf::String new_title)
{
	window_title = new_title;
}

void RenderService::SetWindowBackground(sf::Color new_color)
{
	window_background_color = new_color;
}

bool RenderService::WindowOpen()
{
	return window.isOpen();
}

std::optional<sf::Event> RenderService::PollEvent()
{
	return window.pollEvent();
}

void RenderService::CloseWindow()
{
	window.close();
}