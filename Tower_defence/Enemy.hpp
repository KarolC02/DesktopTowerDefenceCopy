#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::CircleShape shape;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBarForeground;
    sf::Vector2f position;
    float speed;
    int health;
    int maxHealth;
    bool isDead;


    void updateHealthBar(); // Made private to enforce encapsulation

public:
    Enemy(sf::Vector2f startPosition, int initialHealth);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    // Getters for private members
    const sf::CircleShape& getShape() const { return shape; }
    int getHealth() const { return health; }
    bool getIsDead() const { return isDead; }

    // Setters if needed
    void setHealth(int newHealth);
    void setIsDead(bool dead);
};

#endif // ENEMY_HPP
