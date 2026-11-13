#pragma once

#include "common.h"

namespace CJ
{
	class Component
	{
	public:
		virtual void Inputs(const std::vector<sf::Event>& _events) {}
		virtual void Update(const float _deltaTime) {}
		virtual void Render(sf::RenderTarget& _rt) {}
		virtual const char* GetName() = 0;
	};


	class GraphicComponent : public Component
	{
	public:
		struct AnimParametter
		{
			AnimParametter(sf::Vector2i _frameDivider, sf::Vector2i _startFrame, float _frameTime, unsigned int _nbFrame)
			{
				frameDivider = _frameDivider;
				startFrame = _startFrame;
				frameTime = _frameTime;
				nbFrame = _nbFrame;
			}

			sf::Vector2i frameDivider = sf::Vector2i(0, 0);
			sf::Vector2i startFrame = sf::Vector2i(0, 0);
			unsigned int nbFrame = 0;
			float frameTime = 0.f;
		};

		GraphicComponent(const char* _textureFile, const sf::Vector2f& _position, const sf::IntRect& _area);
		GraphicComponent(const char* _textureFile, const sf::Vector2f& _position, AnimParametter& _parametter);
		virtual ~GraphicComponent() = default;

		virtual void Inputs(const std::vector<sf::Event>& _events) override;
		virtual void Update(const float _deltaTime)override;
		virtual void Render(sf::RenderTarget& _rt)override;

		virtual const char* GetName() override { return "GraphicComponent"; }

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		unsigned int m_frameCount = 0;
		float m_animationTimer = 0.f;
		sf::Vector2i m_frameSize = sf::Vector2i(0, 0);
		sf::Vector2i m_startFrame = sf::Vector2i(0, 0);
		unsigned int m_nbFrame = 0;
	};
}