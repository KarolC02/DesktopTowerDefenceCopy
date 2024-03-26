#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

class Arena {
public:
    Arena(float width, float height, sf::Vector2f position);
    void update(float dt, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    // Accessor for demonstration purposes
    std::vector<std::unique_ptr<Tower>>& getTowers();
    std::vector<Enemy>& getEnemies();
    
    bool addTower(std::unique_ptr<Tower> tower);
    sf::Vector2f snapToGrid(const sf::Vector2f& position);
    bool isWithinBounds(sf::Vector2f snappedPos);
    bool isSpaceFree(const sf::Vector2f& position) const;

private:
    sf::RectangleShape background;
    sf::RectangleShape topFrame;
    sf::RectangleShape bottomFrame;
    std::vector<std::unique_ptr<Tower>> towers;
    std::vector<Enemy> enemies;
    // Assuming Bullet handling is within Tower, but if not, add here
    sf::Clock _enemySpawner;
    
    void removeDeadOrOutOfBoundsEnemies(const sf::RenderWindow& window);

};

