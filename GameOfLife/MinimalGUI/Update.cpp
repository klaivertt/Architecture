#include "Update.h"
#include "GameData.h"
#include "WidgetsOwner.h"

void Update(float _dt, GameData& _data)
{
	_data.gameLife.Update(_dt);
	WidgetsOwner::get()->Update(_data.mousePos);
}
