#include "Draw.h"
#include "GameData.h"
#include "WidgetsOwner.h"
void Draw(sf::RenderTarget& _render, GameData& _data)
{
	_data.gameLife.Draw(_render);

	WidgetsOwner::get()->Draw(_render);
}
