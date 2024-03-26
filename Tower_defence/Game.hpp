#pragma once
#include "DEFINE.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.hpp"
#include "Tower.hpp"
#include "PelletTower.hpp"
#include "Bullet.hpp"
#include "Arena.hpp"
#include "TowerButton.hpp"
#include "vector"
class Game {
public:
    Game();
    void Run();

    enum class GameState {
        Default,
        PlacingTower,
        TowerSelected
    };

    void setGameState(GameState newState); // To change game states
    void handleMouseHover(sf::Vector2i hoverPosition);
    std::vector<TowerButton> buttons;
private:
    
    TowerButton pelletTowerButton;
    TowerButton SwarmTowerButton;
    TowerButton DartTowerButton;
    TowerButton SquirtTowerButton;
    TowerButton BashTowerButton;
    TowerButton FrostTowerButton;
    
    TowerType currentlyPlacing;
    bool showPreview = true;
    std::unique_ptr<Tower> previewTower;
    GameState currentState;
    sf::RenderWindow window;
    Arena arena;
    std::vector<std::unique_ptr<Tower>> towers;
    std::vector<Enemy> enemies;
    sf::Font gameFont;
    
    void setCurrentlyPlacing(TowerType type);
    void processEvents();
    void update(float dt);
    void render();
    void handleMouseClick(sf::Vector2i clickPosition);
    bool isFreeSpace(const sf::Vector2f& gridPosition) const;
    bool collision(const sf::Shape& shape1, const sf::Shape& shape2) const;
};
