#pragma once
#include "Engine.h"
#include "Editor.h"

namespace CJ
{
	class Editor;

	class Application
	{
	public:
		~Application();

		bool Initialize(const char* _title, const sf::VideoMode& _mode, unsigned int _framerateLimite);
		void Run();

	private:
		std::vector<sf::Event> ProcessEvents();

		sf::RenderWindow*	m_window{ nullptr };
		sf::Clock			m_clock;
		bool				m_editorEnabled{ true };
		bool				m_pause{ true };
		std::unique_ptr<Editor>	m_editor;	
		CJ::Engine			m_engine;
	};
}