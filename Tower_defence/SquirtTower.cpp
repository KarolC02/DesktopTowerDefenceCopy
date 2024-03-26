#include "SquirtTower.hpp"
#include "DEFINE.hpp"

SquirtTower::SquirtTower(sf::Vector2f position)
    : Tower(position, SQUIRT_TOWER_COLOR, 0.5f /* Fast attack speed */, 70, "S", 5, 15) {
    // Initialization specific to SquirtTower
}

//void SquirtTower::update(float deltaTime) {
//    // Implementation of update specific to SquirtTower
//}
