// Christopher Stackpole, 12/07/2025

#include "ResourceService.h"

void ResourceService::Start()
{

}
void ResourceService::Shutdown()
{

}
void ResourceService::Tick(float dt)
{

}

bool ResourceService::LoadResource(std::string& text, const std::string& path)
{
	// TODO: Implement Text loading
	return false;
}

bool ResourceService::LoadResource(sf::Texture& texture, const std::string& path)
{
	// TODO: Add error handling
	auto result = texture.loadFromFile(path);

	if (!result)
	{
		std::cerr << "ResourceService: Encountered SFML Load Error:" << result << std::endl;
		return false;
	}

	return true;
}

bool ResourceService::LoadResource(sf::SoundBuffer& sound_buffer, const std::string& path)
{
	// TODO: Add error handling
	return sound_buffer.loadFromFile(path);
}