#pragma once

#include "common.h"

class AssetManager
{
public:
	SINGLETON_PUBLIC_DECLARATION(AssetManager);

	sf::Font* GetFont(void);
private:
	SINGLETON_PRIVATE_DECLARATION(AssetManager);
	sf::Font* font;
	AssetManager();
	~AssetManager();
};