#include "SwarmTower.hpp"
#include "DEFINE.hpp"

SwarmTower::SwarmTower(sf::Vector2f position)
    : Tower(position, SWARM_TOWER_COLOR, 1.5f /* Average attack speed */, 60, "SW", 20, 50) {
    // Initialization specific to SwarmTower
}

//void SwarmTower::update(float deltaTime) {
//    // Implementation of update specific to SwarmTower
//}
