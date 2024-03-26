#include "DartTower.hpp"
#include "DEFINE.hpp"

DartTower::DartTower(sf::Vector2f position)
    : Tower(position, DART_TOWER_COLOR, 3.0f /* Very slow attack speed */, 90, "D", 8, 20) {
    // Initialization specific to DartTower
}

//void DartTower::update(float deltaTime) {
//    // Implementation of update specific to DartTower
//}
