// PelletTower.hpp
#ifndef PELLETTOWER_HPP
#define PELLETTOWER_HPP

#include "Tower.hpp"

class PelletTower : public Tower {
public:
    PelletTower(sf::Vector2f position);
//    void update(float deltaTime) override; // Correct use of override
};


#endif // PELLETTOWER_HPP
