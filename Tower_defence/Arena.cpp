#include "Arena.hpp"
#include <algorithm> // For std::remove_if
#include "PelletTower.hpp"
#include <stdio.h>
#include "DEFINE.hpp"
#include <math.h>

Arena::Arena(float width, float height, sf::Vector2f position) {
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(133, 187, 101));
    background.setPosition(position);
    
    topFrame.setSize(sf::Vector2f(width+2*GRID_CELL_SIZE, 4 * TOWER_SIDE_LENGTH + GRID_CELL_SIZE));
    topFrame.setPosition(position - sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
    topFrame.setFillColor(BACKGROUND_FRAME_COLOR);
    
    bottomFrame.setSize(sf::Vector2f(width+2*GRID_CELL_SIZE, 9 * GRID_CELL_SIZE));
    bottomFrame.setPosition(topFrame.getPosition() + sf::Vector2f(0,15*GRID_CELL_SIZE));
    bottomFrame.setFillColor(BACKGROUND_FRAME_COLOR);
    
    // Add a single PelletTower - adjust position as needed
//    towers.push_back(std::make_unique<PelletTower>(sf::Vector2f(300, 150))); // Using the simplified constructor

    // Add a single Enemy - adjust position and initial health as needed
}

void Arena::update(float dt, const sf::RenderWindow& window) {
    if(_enemySpawner.getElapsedTime().asSeconds() > 1.5f ){
        enemies.emplace_back(sf::Vector2f(LEFT_OFFSET, TOP_OFFSET + ARENA_HEIGHT/2), 20); // Position and initial health
        _enemySpawner.restart();
    }
    for (auto& tower : towers) {
        tower->update(dt, enemies);
    }

    // printf("There are currently %d enemies\n", (int) enemies.size());
    for (auto& enemy : enemies) {
        enemy.update(dt);
    }

    for (auto& tower : towers) {
        tower->eraseOutOfScreenBullets(window);
    }
    
    removeDeadOrOutOfBoundsEnemies(window);
}

void Arena::draw(sf::RenderWindow& window) const {
    window.draw(topFrame);
    window.draw(bottomFrame);
    window.draw(background);
    for (const auto& tower : towers) {
        tower->draw(window);
    }
    for (const auto& enemy : enemies) {
        window.draw(enemy.getShape()); // Assuming Enemy has an SFML drawable shape
    }
    // Similar drawing logic for bullets if managed here
}

std::vector<std::unique_ptr<Tower>>& Arena::getTowers() {
    return towers;
}

std::vector<Enemy>& Arena::getEnemies() {
    return enemies;
}

bool Arena::addTower(std::unique_ptr<Tower> tower) {
    // Snap tower's position to grid
    sf::Vector2f snappedPos = snapToGrid(tower->getPosition());

    // Check if the snapped position is valid and free
    if ( isSpaceFree(snappedPos)  && isWithinBounds(snappedPos)) {
        tower->setPosition(snappedPos);
        towers.push_back(std::move(tower));
        return true; // Successfully added tower
    }
    return false; // Failed to add tower
}

sf::Vector2f Arena::snapToGrid(const sf::Vector2f& position) {
    sf::Vector2f snappedPos;
    snappedPos.x = std::floor((position.x - LEFT_OFFSET) / GRID_CELL_SIZE) * GRID_CELL_SIZE + LEFT_OFFSET;
    snappedPos.y = std::floor((position.y - TOP_OFFSET) / GRID_CELL_SIZE) * GRID_CELL_SIZE + TOP_OFFSET;
    return snappedPos;
}

void Arena::removeDeadOrOutOfBoundsEnemies(const sf::RenderWindow& window) {
    auto newEnd = std::remove_if(enemies.begin(), enemies.end(),
        [&window](const Enemy& enemy) {
            // Assume Enemy has a method isDead() to check if it's dead
            // and getShape() for its graphical representation
            bool isDead = enemy.getIsDead();
            bool isOutOfBounds = enemy.getShape().getPosition().x < 0 ||
                                 enemy.getShape().getPosition().x > LEFT_OFFSET + ARENA_WIDTH + enemy.getShape().getGlobalBounds().width  ||
                                 enemy.getShape().getPosition().y < 0 ||
                                 enemy.getShape().getPosition().y > TOP_OFFSET + ARENA_HEIGHT + enemy.getShape().getGlobalBounds().height ;
            return isDead || isOutOfBounds;
        });
    enemies.erase(newEnd, enemies.end());
    // printf("Just ereased an enemy!\n");
}

bool Arena::isWithinBounds(sf::Vector2f snappedPos){
    return (snappedPos.x > LEFT_OFFSET && snappedPos.x < ARENA_WIDTH + LEFT_OFFSET
            && snappedPos.y > TOP_OFFSET && snappedPos.y < TOP_OFFSET + ARENA_HEIGHT);
}

bool Arena::isSpaceFree(const sf::Vector2f& position) const {
    for (const auto& tower : towers) {
        sf::Vector2f diff = tower->getPosition() - position;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (distance < 40) { // Assuming 20 is the threshold for "closeness"
            return false; // Position already taken
        }
    }
    return true; // No tower at this position, free to place a new tower
}

