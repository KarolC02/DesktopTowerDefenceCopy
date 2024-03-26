#include "PelletTower.hpp"
#include "DEFINE.hpp"

PelletTower::PelletTower(sf::Vector2f position)
    : Tower(position, PELLET_TOWER_COLOR, 2.0f, GRID_CELL_SIZE * 4, "P", 5, 10) {
    // Initialize PelletTower-specific attributes if any
}

//void PelletTower::update(float deltaTime) {
//    // PelletTower's specific update logic
//    Tower::resetCooldown(); // Example of calling base class method
//}

