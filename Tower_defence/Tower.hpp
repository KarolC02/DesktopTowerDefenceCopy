#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bullet.hpp"
#include "Enemy.hpp"

class Tower {
protected:
    sf::Text text;
    sf::RectangleShape shape; // Visual representation of the tower
    float attackSpeed;        // How often the tower can attack
    int cost;                 // Cost of the tower
    int damage;               // Damage dealt by the tower
    float attackCooldown;     // Cooldown timer for attacks
    int range;                // Attack range of the tower
    std::vector<std::unique_ptr<Bullet>> bullets; // Bullets fired by the tower

public:
    Tower(sf::Vector2f position, sf::Color color, float atkSpeed, int rng, const std::string& typeSymbol, int dmg, int cst);
    
    void update(float deltaTime, const std::vector<Enemy>& enemies);
    int getRange() const;
    const sf::RectangleShape& getShape() const { return shape; }
    
    void draw(sf::RenderWindow& window) const;
    void fireBullet(sf::Vector2f targetPosition, float bulletSpeed);
    
    bool canAttack() const;
    void resetCooldown();
    
    // Method to erase bullets that are out of the screen bounds
    void eraseOutOfScreenBullets(const sf::RenderWindow& window);

    // Check if an enemy is within the attack range of the tower
    bool isInRange(const sf::Vector2f& enemyPosition) const;

    // New: Method to get the position of the tower
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(sf::Vector2f pos);
    void setColor(sf::Color color);
};
