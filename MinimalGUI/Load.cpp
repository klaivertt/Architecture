#include "Load.h"
#include "GameData.h"
#include "Button.h"
#include "CheckBox.h"
#include "Slider.h"
#include "WidgetsOwner.h"
#include "Panel.h"

int Load(GameData& _data)
{
	srand((unsigned int)(time(NULL)));

	WidgetsOwner::s_create();

	sf::Font& font = _data.font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return -1;
	}

	int sizeGrid = 80;
	_data.gameLife = GameLife(sf::Vector2i(sizeGrid, sizeGrid), 0.5f);

	GameLife& game = _data.gameLife;

	sf::Text* text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Panel");
	
	sf::RectangleShape* pShape = new sf::RectangleShape(sf::Vector2f(40.f, 40.f));
	pShape->setPosition(SCREEN_S.x - 230.f, 20.f);
	pShape->setFillColor(sf::Color(80, 50, 100, 150));

	Panel* panel = new Panel(pShape, sf::Vector2f(5.f,15.f), text);


	sf::CircleShape* shape = new sf::CircleShape(20.f);

	text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Init");

	Button* buttonInit = new Button(shape, text);

	buttonInit->SetOnClick([&game]() { game.Init(); });
	buttonInit->SetOwner(panel);

	panel->Add(buttonInit);


	sf::RectangleShape* rshape = new sf::RectangleShape(sf::Vector2f(40.f, 40.f));
	
	text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Pause");

	
	CheckBox* checkBox = new CheckBox(rshape, text);

	checkBox->SetOnToggle([&game](bool _on) { game.SetPause(_on); });
	checkBox->SetOwner(panel);

	panel->Add(checkBox);
	
	rshape = new sf::RectangleShape(sf::Vector2f(160.f, 25.f));
	rshape->setFillColor(sf::Color(75,180,120));
	
	text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Life Rate : ");

	Slider* slider = new Slider(sf::Vector2f(0.f,1.f), 0.5f, rshape, text, true);

	slider->SetOnReleased([&game](float _percent) { game.SetLifePercent(_percent); });
	slider->SetOwner(panel);

	panel->Add(slider);
	
	//update Time
	rshape = new sf::RectangleShape(sf::Vector2f(160.f, 25.f));
	rshape->setFillColor(sf::Color(120,100,180));
	
	text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Update Rate : ");

	slider = new Slider(sf::Vector2f(0.01f, MAX_UPDATE_TIME), 0.5f, rshape, text);

	slider->SetOnReleased([&game](float _percent) { game.SetUdpdateTime(_percent); });
	slider->SetOwner(panel);

	panel->Add(slider);
	panel->SetOwner(WidgetsOwner::get(), true);
	WidgetsOwner::get()->Add(panel);

	//update Time
	rshape = new sf::RectangleShape(sf::Vector2f(160.f, 25.f));
	rshape->setFillColor(sf::Color(120,100,180));
	
	text = new sf::Text();
	text->setFont(font);
	text->setCharacterSize(16);
	text->setString("Update Rate : ");

	slider = new Slider(sf::Vector2f(0.01f, MAX_UPDATE_TIME), 0.5f, rshape, text);

	slider->SetOnReleased([&game](float _percent) { game.SetUdpdateTime(_percent); });
	slider->SetOwner(WidgetsOwner::get(), true);
	WidgetsOwner::get()->Add(slider);
	return 0;
}