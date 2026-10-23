#pragma once

#include "common.h"
#include <vector>

class Flocking
{
public:
    Flocking(unsigned _numBoids, const sf::Vector2u& _windowSize);

    void update(float _dt);
    void draw(sf::RenderTarget& _rt);

    void restart();
    void setNumBoids(unsigned _numBoids);
	unsigned getNumBoids() const { return m_boids.size(); }

	void setSimulationSpeed(float _speed) { m_simulationSpeed = _speed; }
	float getSimulationSpeed() const { return m_simulationSpeed; }

private:
    class SpatialGrid;
    struct Boid
    {
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::Vector2f m_acceleration;
        sf::ConvexShape m_shape;

        void update(const float _dt);
        void wrap(const float _maxX, const float _maxY);
        void draw(sf::RenderTarget& _rt) const;

        void flock(const std::vector<Boid>& _boids);

    private:
        sf::Vector2f computeSeparationForce(const std::vector<Boid>& _boids, const float _radius);
        sf::Vector2f computeAlignmentForce(const std::vector<Boid>& _boids, const float _radius);
        sf::Vector2f computeCohesionForce(const std::vector<Boid>& _boids, const float _radius);
    };

    void initializeBoid(Boid& _boid, const float _maxX, const float _maxY);

private:
    std::vector<Boid> m_boids;
    sf::Vector2u m_windowSize;
    float m_simulationSpeed{1.0f};
};
