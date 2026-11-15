#include "AssetsManager.h"

SINGLETON_DEFINITION(AssetManager)

sf::Font* AssetManager::GetFont(void)
{
	return font;
}

AssetManager::AssetManager()
{
	font = new sf::Font();
	if (font)
	{
		font->loadFromFile("arial.ttf");
	}
}

AssetManager::~AssetManager()
{
	if (font)
	{
		delete font;
	}
}
