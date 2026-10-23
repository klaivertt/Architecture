#include "Flocking.h"
#include <cmath>
#include <algorithm>

constexpr const float PI = 3.14159f;

constexpr const float RADIUS_SEPARATION = 25.f;
constexpr const float RADIUS_ALIGNMENT  = 40.f;
constexpr const float RADIUS_COHESION   = 40.f;

constexpr const float WEIGHT_SEPARATION = 2.f;
constexpr const float WEIGHT_ALIGNMENT = 1.f;
constexpr const float WEIGHT_COHESION = 1.f;
constexpr const float WEIGHT_TOTAL = 200.f;

constexpr const float MIN_SPEED = 100.f;
constexpr const float MAX_SPEED = 200.f;

static float length(const sf::Vector2f _v)
{
    return std::sqrt(_v.x * _v.x + _v.y * _v.y);
}

static sf::Vector2f normalize(const sf::Vector2f _v)
{
    return (_v.x != 0 || _v.y != 0) ? _v * (1 / length(_v)) : sf::Vector2f(0,0);
}

// SpatialGrid definition
class Flocking::SpatialGrid
{
public:
    SpatialGrid(float _width, float _height, float _cellSize)
        : m_cellSize(std::max(1.f, _cellSize))
    {
        m_cols = std::max(1, (int)(_width / m_cellSize));
        m_rows = std::max(1, (int)(_height / m_cellSize));
        m_cells.clear();
        m_cells.resize(m_cols * m_rows);
    }

    void clear()
    {
        for (std::vector<int>& c : m_cells) c.clear();
    }

    void affectBoid(int _index, const sf::Vector2f& _pos)
    {
        int ix = (int)(_pos.x / m_cellSize);
        int iy = (int)(_pos.y / m_cellSize);
        m_cells[ix + iy * m_cols].push_back(_index);
    }

    void getNearbyIndices(const sf::Vector2f& _pos, std::vector<int>& _outIndices) const
    {
        _outIndices.clear();
        int ix = (int)(_pos.x / m_cellSize);
        int iy = (int)(_pos.y / m_cellSize);

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                int nx = ix + dx;
                int ny = iy + dy;
                nx = ((nx % m_cols) + m_cols) % m_cols;
                ny = ((ny % m_rows) + m_rows) % m_rows;

                const std::vector<int>& cell = m_cells[nx + ny * m_cols];
                for (int id : cell)
                    _outIndices.push_back(id);
            }
        }
    }

private:
    float m_cellSize;
    int m_cols;
    int m_rows;
    std::vector<std::vector<int>> m_cells;
};

void Flocking::Boid::update(const float _dt)
{
    m_velocity.x += m_acceleration.x * _dt;
    m_velocity.y += m_acceleration.y * _dt;

    const float speed = length(m_velocity);
    if (speed > MAX_SPEED)
        m_velocity = normalize(m_velocity) * MAX_SPEED;

    m_position += m_velocity * _dt;
}

void Flocking::Boid::wrap(const float _maxX, const float _maxY)
{
    if (m_position.x < 0)       m_position.x += _maxX;
    if (m_position.x >= _maxX)  m_position.x -= _maxX;
    if (m_position.y < 0)       m_position.y += _maxY;
    if (m_position.y >= _maxY)  m_position.y -= _maxY;
}

void Flocking::Boid::draw(sf::RenderTarget& _rt) const
{
    sf::ConvexShape& shape = const_cast<sf::ConvexShape&>(m_shape);
    shape.setPosition(m_position);
    const float rotation = std::atan2(m_velocity.y, m_velocity.x) * 180.f / PI;
    shape.setRotation(rotation);
    _rt.draw(shape);
}

void Flocking::Boid::flock(const std::vector<Boid>& _boids)
{
    const sf::Vector2f separationForce = WEIGHT_SEPARATION * computeSeparationForce(_boids, RADIUS_SEPARATION);
    const sf::Vector2f alignmentForce = WEIGHT_ALIGNMENT * computeAlignmentForce(_boids, RADIUS_ALIGNMENT);
    const sf::Vector2f cohesionForce = WEIGHT_COHESION * computeCohesionForce(_boids, RADIUS_COHESION);

    m_acceleration = WEIGHT_TOTAL * (separationForce + alignmentForce + cohesionForce);
}

sf::Vector2f Flocking::Boid::computeSeparationForce(const std::vector<Boid>& _boids, const float _radius)
{
    sf::Vector2f result;
    int neighborsCount = 0;

    for (const Boid& other : _boids)
    {
        const sf::Vector2f diff = (m_position - other.m_position);
        const float distance = length(diff);

        if (distance > 0 && distance < _radius)
        {
            const float coeff = (RADIUS_SEPARATION - distance) / RADIUS_SEPARATION;
            result += normalize(diff) * RADIUS_SEPARATION * coeff;
            neighborsCount += 1;
        }
    }

    if (neighborsCount)
        return result * (1 / (float)neighborsCount);

    return sf::Vector2f(0,0);
}

sf::Vector2f Flocking::Boid::computeAlignmentForce(const std::vector<Boid>& _boids, const float _radius)
{
    sf::Vector2f neighborsDirection;
    size_t neighborsCount = 0u;

    for (const Boid& other : _boids)
    {
        const float distance = length(m_position - other.m_position);
        if (distance > 0 && distance < _radius)
        {
            const sf::Vector2f otherDirection = normalize(other.m_velocity);
            const float coeff = (_radius - distance) / _radius;
            neighborsDirection += coeff * otherDirection;
            neighborsCount += 1;
        }
    }


    if (neighborsCount)
        return neighborsDirection * (1 / (float) neighborsCount);
    return sf::Vector2f(0, 0);
}

sf::Vector2f Flocking::Boid::computeCohesionForce(const std::vector<Boid>& _boids, const float _radius)
{
    sf::Vector2f targetPosition(0, 0);
    size_t neighborsCount = 0u;

    for (const Boid& other : _boids)
    {
        const sf::Vector2f diff = other.m_position - m_position;
        const float distance = length(diff);
        if (distance > 0 && distance < _radius)
        {
            const float coeff = (_radius - distance) / _radius;
            targetPosition += coeff * diff;
            neighborsCount += 1u;
        }
    }

    if (neighborsCount)
        return targetPosition * (1 / (float) neighborsCount);
    return sf::Vector2f(0, 0);
}


Flocking::Flocking(unsigned _numBoids, const sf::Vector2u& _windowSize)
    : m_windowSize(_windowSize), m_simulationSpeed(1.0f)
{
    m_boids.reserve(_numBoids);
    for (unsigned i = 0; i < _numBoids; ++i)
    {
        m_boids.emplace_back();
        initializeBoid(m_boids.back(), (float)m_windowSize.x, (float)m_windowSize.y);
    }
}

void Flocking::restart()
{
    for (Boid& b : m_boids)
        initializeBoid(b, (float)m_windowSize.x, (float)m_windowSize.y);
}

void Flocking::setNumBoids(unsigned _numBoids)
{
	const unsigned oldCount = m_boids.size();
    m_boids.resize(_numBoids);

    if (_numBoids > oldCount)
    {
        for (unsigned i = oldCount; i < m_boids.size(); ++i)
            initializeBoid(m_boids[i], (float)m_windowSize.x, (float)m_windowSize.y);
    }
}

void Flocking::initializeBoid(Boid& _boid, const float _maxX, const float _maxY)
{
    _boid.m_position.x = (std::rand() / (float)RAND_MAX) * _maxX;
    _boid.m_position.y = (std::rand() / (float)RAND_MAX) * _maxY;

    float randomAngle = (rand() / (float) RAND_MAX) * 2.f * PI;
    _boid.m_velocity = sf::Vector2f(std::cos(randomAngle), std::sin(randomAngle)) * MAX_SPEED;

    _boid.m_shape.setPointCount(3);
    _boid.m_shape.setPoint(0, sf::Vector2f(10, 0));
    _boid.m_shape.setPoint(1, sf::Vector2f(-5, -5));
    _boid.m_shape.setPoint(2, sf::Vector2f(-5, 5));
    _boid.m_shape.setOrigin(0, 0);

    switch (rand() % 5)
    {
    case 0: _boid.m_shape.setFillColor(sf::Color(100, 200, 255)); break;
    case 1: _boid.m_shape.setFillColor(sf::Color(255, 150, 100)); break;
    case 2: _boid.m_shape.setFillColor(sf::Color(150, 255, 150)); break;
    case 3: _boid.m_shape.setFillColor(sf::Color(255, 200, 150)); break;
    case 4: _boid.m_shape.setFillColor(sf::Color(200, 150, 255)); break;
    }
}

void Flocking::update(float _dt)
{
    float dt = _dt * m_simulationSpeed;
    const float stepMax = 0.05f;
    do
    {
        const float step = std::min(dt, stepMax);

        for (Boid& _boid : m_boids)
            _boid.flock(m_boids);

        for (Boid& _boid : m_boids)
        {
            _boid.update(step);
            _boid.wrap((float)m_windowSize.x, (float)m_windowSize.y);
        }

        dt = dt - step;
    } while (dt > 0.f);
}

void Flocking::draw(sf::RenderTarget& _rt)
{
    for (Boid& _boid : m_boids)
        _boid.draw(_rt);
}
