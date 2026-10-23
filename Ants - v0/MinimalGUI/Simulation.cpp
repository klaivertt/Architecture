#include "Simulation.h"

//--------------------------------------------------------------------------------------------------
// Math & physics functions (unchanged)
//--------------------------------------------------------------------------------------------------
static float length(const sf::Vector2f & _value)
{
    return std::sqrt(_value.x * _value.x + _value.y * _value.y);
}

//--------------------------------------------------------------------------------------------------
static float distance(const sf::Vector2f& _left, const sf::Vector2f& _right)
{
    return length(_left - _right);
}

//--------------------------------------------------------------------------------------------------
static float dot(const sf::Vector2f& _left, const sf::Vector2f& _right)
{
    return _left.x * _right.x + _left.y * _right.y;
}

//--------------------------------------------------------------------------------------------------
static sf::Vector2f normalize(const sf::Vector2f& _value)
{
    const float l = length(_value);
    return (l == 0.f) ? sf::Vector2f(0, 0) : _value / l;
}

//--------------------------------------------------------------------------------------------------
static sf::Vector2f modulo(sf::Vector2f _value, float _x, float _y)
{
    if (_value.x < 0)
        _value.x = _value.x + _x;
    else if (_value.x >= _x)
        _value.x = _value.x - _x;
    if (_value.y < 0)
        _value.y = _value.y + _y;
    else if (_value.y >= _y)
        _value.y = _value.y - _y;
    return _value;
}

//--------------------------------------------------------------------------------------------------
static sf::Vector2f computeWeightedDirection(const sf::Vector2f& _position, const sf::Vector2f& _direction,
    const sf::Vector2f& _attractionPoint, float _attractionRadius, float _attractionStrength,
    float _attractionRadiusMin, float _attractionRadiusMax)
{
    sf::Vector2f toAttractionPoint = _attractionPoint - _position;
    float distanceToAttractionPoint = length(toAttractionPoint) - _attractionRadius;

    if (distanceToAttractionPoint > _attractionRadiusMin &&
        distanceToAttractionPoint < _attractionRadiusMax)
    {
        normalize(toAttractionPoint);
        const float dotProduct = dot(_direction, toAttractionPoint);
        if (dotProduct > 0)
        {
            const float weight = dotProduct * (1.f - distanceToAttractionPoint / _attractionRadiusMax) * _attractionStrength;
            return weight * toAttractionPoint;
        }
    }
    return sf::Vector2f(0.f, 0.f);
}

//--------------------------------------------------------------------------------------------------
// Food
//--------------------------------------------------------------------------------------------------
float FoodSpot::s_getRadius(unsigned _quantity, float radiusFactor) 
{
    return sqrt(_quantity) * radiusFactor;
}

//--------------------------------------------------------------------------------------------------
// Simulation
//--------------------------------------------------------------------------------------------------
Simulation::Simulation()
{
    for (size_t i = 0u; i < m_agentsMaxCount; ++i)
        spawnAgent();
}

//--------------------------------------------------------------------------------------------------
void Simulation::draw(sf::RenderWindow& _window) const
{
    // Draw nest
    sf::CircleShape nestShape(m_nest.m_radius);
    nestShape.setFillColor(sf::Color::Blue);
    nestShape.setPosition(m_nest.m_position.x - m_nest.m_radius, m_nest.m_position.y - m_nest.m_radius);
    _window.draw(nestShape);

    // Draw foods
    for (const FoodSpot& food : m_foodSpots)
    {
        float r = FoodSpot::s_getRadius(food.m_quantity, m_foodRadiusFactor);
        sf::CircleShape foodShape(r);
        foodShape.setFillColor(sf::Color::Yellow);
        foodShape.setPosition(food.m_position.x - r, food.m_position.y - r);
        _window.draw(foodShape);
    }

    // Draw agents
    sf::VertexArray agentsVertices(sf::Triangles);
    for (const Agent& agent : m_agents)
    {
        float agentRotation = std::atan2(agent.m_direction.y, agent.m_direction.x);
        float cosA = std::cos(agentRotation), sinA = std::sin(agentRotation);

        // Triangle points
        sf::Vector2f p0(6.f, 0.f);
        sf::Vector2f p1(-4.f, 3.f);
        sf::Vector2f p2(-4.f, -3.f);

        auto transform = [&](const sf::Vector2f& _point, float _cosA, float _sinA)
            {
                return sf::Vector2f(cosA * _point.x - sinA * _point.y + agent.m_position.x,
                    sinA * _point.x + cosA * _point.y + agent.m_position.y);
            };

        const sf::Color c = (agent.m_mode == Agent::Mode::TO_FOOD) ? sf::Color(150, 150, 255) : sf::Color(150, 255, 150);

        agentsVertices.append(sf::Vertex(transform(p0, cosA, sinA), c));
        agentsVertices.append(sf::Vertex(transform(p1, cosA, sinA), c));
        agentsVertices.append(sf::Vertex(transform(p2, cosA, sinA), c));
    }
    _window.draw(agentsVertices);

    // Draw markers
    sf::VertexArray markersVertices(sf::Quads, m_markers.size() * 4);
    const float halfSize = 2.f;
    for (size_t i = 0; i < m_markers.size(); ++i)
    {
        sf::Color color = (m_markers[i].m_type == Marker::Type::NEST) ? sf::Color(0, 0, 255, 128) : sf::Color(128, 128, 0, 128);
        markersVertices.append(sf::Vertex(sf::Vector2f(m_markers[i].m_position.x - halfSize, m_markers[i].m_position.y - halfSize), color));
        markersVertices.append(sf::Vertex(sf::Vector2f(m_markers[i].m_position.x + halfSize, m_markers[i].m_position.y - halfSize), color));
        markersVertices.append(sf::Vertex(sf::Vector2f(m_markers[i].m_position.x + halfSize, m_markers[i].m_position.y + halfSize), color));
        markersVertices.append(sf::Vertex(sf::Vector2f(m_markers[i].m_position.x - halfSize, m_markers[i].m_position.y + halfSize), color));

    }
    const sf::RenderStates states(sf::BlendAdd);
    _window.draw(markersVertices, states);
}

//--------------------------------------------------------------------------------------------------
void Simulation::update(float _dt)
{
    const float maxDt = 1.0f;
    _dt = std::min(_dt, maxDt);
    const float subStep = 0.1f;
    do
    {
        const float dt = std::min(_dt, subStep);

        spawnAgent();

        for (Agent& _agent : m_agents)
            updateAgent(dt, _agent);

        for (auto it = m_markers.begin(); it != m_markers.end();)
        {
            it->m_timer -= dt;
            if (it->m_timer <= 0)
                it = m_markers.erase(it);
            else
                ++it;
        }

        for (auto it = m_foodSpots.begin(); it != m_foodSpots.end();) {
            if (it->m_quantity == 0)
                it = m_foodSpots.erase(it);
            else
                ++it;
        }
        _dt -= subStep;
    } while (_dt > 0.f);
}

//--------------------------------------------------------------------------------------
void Simulation::spawnAgent()
{
    if (m_agents.size() >= m_agentsMaxCount)
        return;

    Agent agent;
    agent.m_position = m_nest.m_position;

    float randomRotation = ((rand() % 360u) * PI) / 180.f;
    agent.m_direction = sf::Vector2f(std::cos(randomRotation), std::sin(randomRotation));

    agent.m_spawnMarkerTimer = (rand() / (float)RAND_MAX) * m_spawnMarkerTimer;
    agent.m_mode = Agent::Mode::TO_FOOD;

    m_agents.push_back(agent);
}

//--------------------------------------------------------------------------------------
void Simulation::updateAgent(float _dt, Agent& _agent)
{
    sf::Vector2f targetDirection = computeAgentTargetDirection(_agent);

    if (length(targetDirection) > 0.f)
        normalize(targetDirection);
    else
        targetDirection = _agent.m_direction;

    sf::Vector2f noise = computeNoiseDirection(_agent, _dt);
    targetDirection = targetDirection + noise;

    _agent.m_direction = normalize(_agent.m_direction + (targetDirection - _agent.m_direction) * m_agentTurnSpeed * _dt);
    _agent.m_position += _agent.m_direction * m_agentSpeed * _dt;
    _agent.m_position = modulo(_agent.m_position, m_windowWidth, m_windowHeight);

    switch (_agent.m_mode)
    {
    case Agent::Mode::TO_FOOD:
    {
        for (FoodSpot& food : m_foodSpots)
        {
            if (food.m_quantity > 0 && distance(food.m_position, _agent.m_position) <= FoodSpot::s_getRadius(food.m_quantity, m_foodRadiusFactor) + m_minPerceptionRadius)
            {
                _agent.m_mode = Agent::Mode::TO_NEST;
                _agent.m_direction = -_agent.m_direction;
                _agent.m_markerStrength = 1.f;
                food.m_quantity--;
            }
        }
    }
    break;
    case Agent::Mode::TO_NEST:
    {
        if (distance(m_nest.m_position, _agent.m_position) <= m_nest.m_radius + m_minPerceptionRadius)
        {
            _agent.m_mode = Agent::Mode::TO_FOOD;
            _agent.m_direction = -_agent.m_direction;
            _agent.m_markerStrength = 1.f;
        }
    }
    break;
    }

    _agent.m_spawnMarkerTimer += _dt;
    if (_agent.m_spawnMarkerTimer >= m_spawnMarkerTimer && _agent.m_markerStrength > 0.f)
    {
		const Marker::Type markerType = (_agent.m_mode == Agent::Mode::TO_FOOD) ? Marker::Type::NEST : Marker::Type::FOOD;
        m_markers.push_back({ _agent.m_position, m_markerTimer * _agent.m_markerStrength, markerType });
        _agent.m_spawnMarkerTimer = 0.f;
    }
    _agent.m_markerStrength = _agent.m_markerStrength - m_agentMarkerStrengthDecreaseRate * _dt;
}

//--------------------------------------------------------------------------------------
sf::Vector2f Simulation::computeAgentTargetDirection(const Agent& _agent) const
{
    sf::Vector2f targetDirection(0.f, 0.f);

    const Marker::Type targetMarkerType = (_agent.m_mode == Agent::Mode::TO_FOOD) ? Marker::Type::FOOD : Marker::Type::NEST;
    for (const Marker& marker : m_markers)
    {
        if (marker.m_type != targetMarkerType)
            continue;

        const float markerStrength = (marker.m_timer / m_markerTimer);
        targetDirection += computeWeightedDirection(_agent.m_position, _agent.m_direction,
            marker.m_position, 0.f, markerStrength,
            m_minPerceptionRadius, m_maxPerceptionRadius);
    }

    switch (_agent.m_mode)
    {
    case Agent::Mode::TO_NEST:
    {
        targetDirection += computeWeightedDirection(_agent.m_position, _agent.m_direction,
            m_nest.m_position, m_nest.m_radius, m_nestAttractionStrength,
            m_minPerceptionRadius, m_maxPerceptionRadius);
    }
    break;
    case Agent::Mode::TO_FOOD:
    {
        for (const FoodSpot& food : m_foodSpots)
        {
            targetDirection += computeWeightedDirection(_agent.m_position, _agent.m_direction,
                m_nest.m_position, FoodSpot::s_getRadius(food.m_quantity, m_foodRadiusFactor), m_foodAttractionStrength,
                m_minPerceptionRadius, m_maxPerceptionRadius);
        }
    }
    break;
    }

    return targetDirection;
}

//--------------------------------------------------------------------------------------
sf::Vector2f Simulation::computeNoiseDirection(const Agent& _agent, float _dt) const
{
    float randAngle = ((rand() / (float)RAND_MAX) * 2 - 1) * m_randomWiggleStrength * _dt;
    float cosA = std::cos(randAngle);
    float sinA = std::sin(randAngle);
    return sf::Vector2f(_agent.m_direction.x * cosA - _agent.m_direction.y * sinA, _agent.m_direction.x * sinA + _agent.m_direction.y * cosA);
}

//--------------------------------------------------------------------------------------
void Simulation::trySpawnFoodSpot(const sf::Vector2f& _position)
{
    const unsigned quantityToSpawn = 100;
    const float radiusToSpawn = FoodSpot::s_getRadius(quantityToSpawn, m_foodRadiusFactor);

    for (const FoodSpot& f : m_foodSpots)
    {
        const float radius = FoodSpot::s_getRadius(f.m_quantity, m_foodRadiusFactor);
        if (length(f.m_position - _position) < (radius + radiusToSpawn))
            return;
    }

    m_foodSpots.push_back({ _position, quantityToSpawn });
}
