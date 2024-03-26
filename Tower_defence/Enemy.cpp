#include "Enemy.hpp"
#include <iostream>
#include "DEFINE.hpp"

Enemy::Enemy(sf::Vector2f startPosition, int initialHealth)
    : position(startPosition), health(initialHealth), maxHealth(initialHealth), speed(ENEMY_SPEED), isDead(false) {
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(position);

    // Initialize health bar background
    healthBarBackground.setSize(sf::Vector2f(20, 5));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50)); // Dark gray color
    healthBarBackground.setOrigin(healthBarBackground.getSize().x / 2, healthBarBackground.getSize().y / 2);

    // Initialize health bar foreground
    healthBarForeground.setSize(sf::Vector2f(20, 5));
    healthBarForeground.setFillColor(sf::Color::Green);
    healthBarForeground.setOrigin(healthBarForeground.getSize().x / 2, healthBarForeground.getSize().y / 2);
    
    // std::cout << "Spawned enemy with health: " << health << std::endl;
}

void Enemy::update(float deltaTime) {
    position.x += speed * deltaTime;
    shape.setPosition(position);
    updateHealthBar();
    if (health <= 0) {
        isDead = true;
    }
}

void Enemy::updateHealthBar() {
    healthBarBackground.setPosition(position.x, position.y - shape.getRadius() - 10);
    healthBarForeground.setPosition(position.x, position.y - shape.getRadius() - 10);
    healthBarForeground.setPosition(position.x, position.y - shape.getRadius() - 10);
    float healthRatio = static_cast<float>(health) / maxHealth;
    healthBarForeground.setSize(sf::Vector2f(20 * healthRatio, 5));
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(healthBarBackground);
    window.draw(healthBarForeground);
}

// Setters
void Enemy::setHealth(int newHealth) {
    health = newHealth;
    updateHealthBar();
}

void Enemy::setIsDead(bool dead) {
    isDead = dead;
}
