#pragma once
#include "common.h"

//--------------------------------------------------------------------------------------------------
struct FoodSpot
{
    sf::Vector2f m_position { 0.f, 0.f };
    unsigned int m_quantity { 0 };

    static float s_getRadius(unsigned _quantity, float radiusFactor);
};

//--------------------------------------------------------------------------------------------------
struct Nest
{
    sf::Vector2f    m_position  { 0.f, 0.f };
    float           m_radius    { 0 };
};

//------------------------------------------------------------------------------------------------------------
struct Marker
{
    sf::Vector2f    m_position  { 0.f, 0.f };
    float           m_timer     { 0.f };
    enum class Type
    {
        FOOD = 0,
        NEST,
    } m_type = Type::FOOD;
};

//------------------------------------------------------------------------------------------------------------
struct Agent
{
    sf::Vector2f m_position { 0.f, 0.f };
    sf::Vector2f m_direction{ 0.f, 0.f };

    enum class Mode
    {
        TO_FOOD = 0,
        TO_NEST,
    } m_mode    { Mode::TO_FOOD };

    float m_spawnMarkerTimer{ 0.f };
    float m_markerStrength  { 0.f };
};

//------------------------------------------------------------------------------------------------------------
class Simulation
{
public:
    Simulation();

    void setWindowSize  (unsigned int _width, unsigned int _height) { m_windowWidth = _width; m_windowHeight = _height; }

	void draw		    (sf::RenderWindow& _window) const;
	void update		    (float _dt);

    void trySpawnFoodSpot   (const sf::Vector2f& _position);

    float getSpawnMarkerTimer() const { return m_spawnMarkerTimer; }
    void setSpawnMarkerTimer(float _v) { m_spawnMarkerTimer = _v; }

    float getMarkerTimer() const { return m_markerTimer; }
    void setMarkerTimer(float _v) { m_markerTimer = _v; }

    float getAgentSpeed() const { return m_agentSpeed; }
    void setAgentSpeed(float _v) { m_agentSpeed = _v; }

    float getMinPerceptionRadius() const { return m_minPerceptionRadius; }
    void setMinPerceptionRadius(float _v) { m_minPerceptionRadius = _v; }

    float getMaxPerceptionRadius() const { return m_maxPerceptionRadius; }
    void setMaxPerceptionRadius(float _v) { m_maxPerceptionRadius = _v; }

    unsigned int getFoodQuantity() const { return m_foodQuantity; }
    void setFoodQuantity(unsigned int _v) { m_foodQuantity = _v; }

    void FoodSpotQuantityString(std::string& _string) const
    {
        _string = _string + " : " + std::to_string(m_foodSpots.size());
    }

    float getFoodRadiusFactor() const { return m_foodRadiusFactor; }
    void setFoodRadiusFactor(float _v) { m_foodRadiusFactor = _v; }

    float getFoodAttractionStrength() const { return m_foodAttractionStrength; }
    void setFoodAttractionStrength(float _v) { m_foodAttractionStrength = _v; }

    float getNestAttractionStrength() const { return m_nestAttractionStrength; }
    void setNestAttractionStrength(float _v) { m_nestAttractionStrength = _v; }

    float getRandomWiggleStrength() const { return m_randomWiggleStrength; }
    void setRandomWiggleStrength(float _v) { m_randomWiggleStrength = _v; }

    float getAgentTurnSpeed() const { return m_agentTurnSpeed; }
    void setAgentTurnSpeed(float _v) { m_agentTurnSpeed = _v; }

    size_t getAgentsMaxCount() const { return m_agentsMaxCount; }
    void setAgentsMaxCount(size_t _v) { m_agentsMaxCount = _v; if (m_agents.size() > m_agentsMaxCount) m_agents.resize(m_agentsMaxCount); }

    float getAgentMarkerStrengthDecreaseRate() const { return m_agentMarkerStrengthDecreaseRate; }
    void setAgentMarkerStrengthDecreaseRate(float _v) { m_agentMarkerStrengthDecreaseRate = _v; }

private:
    void spawnAgent     ();
    void updateAgent    (float _dt, Agent& _agent);

    sf::Vector2f computeAgentTargetDirection(const Agent& _agent) const;
    sf::Vector2f computeNoiseDirection      (const Agent& _agent, float _dt) const;

private:
    Nest                    m_nest{ { 900.f, 500.f }, 20.f };
    std::vector<FoodSpot>   m_foodSpots;

    std::vector<Agent>  m_agents;
    std::vector<Marker> m_markers;

    unsigned int m_windowWidth  { 0u };
    unsigned int m_windowHeight { 0u };

    float m_spawnMarkerTimer { 0.1f };
    float m_markerTimer { 5.0f };

    float m_agentSpeed { 100.f };

    float m_minPerceptionRadius { 0.1f };
    float m_maxPerceptionRadius { 30.f };

    unsigned int m_foodQuantity { 200 };
    float m_foodRadiusFactor { 0.5f };

    float m_foodAttractionStrength { 100.f };
    float m_nestAttractionStrength { 100.f };

    float m_randomWiggleStrength { 15.f };
    float m_agentTurnSpeed { 30000.0f };
    size_t m_agentsMaxCount { 300 };

    float m_agentMarkerStrengthDecreaseRate { 0.05f };
};