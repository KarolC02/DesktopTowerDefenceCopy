#include "FrostTower.hpp"
#include "DEFINE.hpp"

FrostTower::FrostTower(sf::Vector2f position)
    : Tower(position, FROST_TOWER_COLOR, 2.5f /* Slow attack speed */, 50, "F", 10, 50) {
    // Initialization specific to FrostTower
}

//void FrostTower::update(float deltaTime) {
//    // Implementation of update specific to FrostTower
//}
