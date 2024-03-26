#include "BashTower.hpp"
#include "DEFINE.hpp"

BashTower::BashTower(sf::Vector2f position)
    : Tower(position, BASH_TOWER_COLOR, 2.5f /* Slow attack speed */, 40, "B", 10, 30) {
    // Initialization specific to BashTower
}

//void BashTower::update(float deltaTime) {
//    // Implementation of update specific to BashTower
//}
