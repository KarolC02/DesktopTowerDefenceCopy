#include "Game.hpp"
#include <iostream>
#include <memory> // For std::unique_ptr

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->Run();
    return EXIT_SUCCESS;
}


//int main() {
//    
//    // Set window size to accommodate the playing area plus extra space for UI
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Desktop Tower Defence");
//    
//    std::vector<Enemy> enemies;
//    std::vector<std::unique_ptr<Tower>> towers;
//    std::vector<std::unique_ptr<Bullet>> bullets;
//    sf::Clock clock;
//
//    // Define the preview tower shape
//    sf::RectangleShape previewTower(sf::Vector2f(TOWER_SIDE_LENGTH, TOWER_SIDE_LENGTH));
//    previewTower.setFillColor(sf::Color::Transparent); // Initially set to transparent
//    previewTower.setOrigin(TOWER_SIDE_LENGTH / 2, TOWER_SIDE_LENGTH / 2);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        
//        sf::Vector2f offsetMousePos(static_cast<float>(sf::Mouse::getPosition(window).x),
//                                    static_cast<float>(sf::Mouse::getPosition(window).y));
//
//        sf::Vector2f gridPosition;
//        gridPosition.x = std::floor(offsetMousePos.x / GRID_CELL_SIZE) * GRID_CELL_SIZE; // + GRID_CELL_SIZE / 2;
//        gridPosition.y = std::floor(offsetMousePos.y / GRID_CELL_SIZE) * GRID_CELL_SIZE; // + GRID_CELL_SIZE / 2;
//        
//        previewTower.setPosition(gridPosition.x, gridPosition.y);
//        window.draw(previewTower); // Draw the preview tower
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (gridPosition.x > 0 && gridPosition.x < WINDOW_WIDTH &&
//                    gridPosition.y > 0 && gridPosition.y < WINDOW_HEIGHT) {
//                    
//                    // CHECK FOR COLISION -> LATER MOVE TO FUNCTION
//                    if (isFreeSpace(gridPosition, towers)) {
//                        towers.push_back(std::make_unique<PelletTower>(gridPosition));
//                    }
//                }
//            }
//        }
//
//        float deltaTime = clock.restart().asSeconds();
//        
//        ///asdasda
//        // FIRE BULLETS
//        for (auto& tower : towers) {
//            tower->update(deltaTime, window);
//            tower->draw(window);
//
//            // Iterate through each enemy
//            for (auto& enemy : enemies) {
//                // Calculate distance between tower and enemy
//                sf::Vector2f towerPosition = tower->shape.getPosition();
//                sf::Vector2f enemyPosition = enemy.shape.getPosition();
//                float distance = std::sqrt(std::pow(enemyPosition.x - towerPosition.x, 2) + std::pow(enemyPosition.y - towerPosition.y, 2));
//
//                // If enemy is within tower's range, fire a bullet
//                if (distance <= tower->range) {
//                    tower->fireBullet(enemyPosition, BULLET_SPEED);
//                }
//            }
//        }
//
//        // Enemy spawning logic
//        static float enemySpawnTimer = 0.0f;
//        enemySpawnTimer += deltaTime;
//        if (enemySpawnTimer >= 2.0f) {
//            Enemy newEnemy(sf::Vector2f(-50, window.getSize().y / 2), 20);
//            std::cout << "Spawning enemy with health: " << newEnemy.health << std::endl;
//            enemies.push_back(std::move(newEnemy));
//            enemySpawnTimer = 0.0f;
//        }
//
//        // Render everything
//        window.clear(sf::Color::White); // Clear with a different color for the entire window
//
//        // Draw enemies and towers
//
//        for (auto& tower : towers) {
//            tower->update(deltaTime, window);
//            tower->draw(window);
//
//        }
//        
//        for (auto& enemy : enemies) {
//            enemy.update(deltaTime);
//            enemy.draw(window);
//        }
//        
//        for (auto& tower : towers) {
//            auto& bullets = tower->bullets; // Access the bullets of the tower
//            auto bulletIter = bullets.begin();
//            while (bulletIter != bullets.end()) {
//                bool bulletHit = false;
//
//                for (auto& enemy : enemies) {
//                    if (collision(bulletIter->shape, enemy.shape)) {
//                        enemy.health -= bulletIter->damage; // Bullet deals damage to the enemy
//                        enemy.updateHealthBar(); // Update the enemy's health bar
//                        if (enemy.health <= 0) {
//                            enemy.isDead = true; // Mark the enemy as dead if health drops to 0 or below
//                        }
//                        bulletHit = true; // Mark the bullet for removal
//                        break; // A bullet can only hit one enemy, so break the loop
//                    }
//                }
//
//                if (bulletHit) {
//                    // Remove the bullet if it hit an enemy
//                    bulletIter = bullets.erase(bulletIter);
//                } else {
//                    // Only update and draw the bullet if it did not hit any enemy
//                    bulletIter->update(deltaTime);
//                    window.draw(bulletIter->shape);
//                    ++bulletIter;
//                }
//            }
//        }
//
//        // Remove dead enemies
//        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
//            return enemy.isDead;
//        }), enemies.end());
//        
//
//        // Preview
//        if (gridPosition.x > 0 && gridPosition.x < WINDOW_WIDTH &&
//            gridPosition.y > 0 && gridPosition.y < WINDOW_HEIGHT) {
//            previewTower.setPosition(gridPosition.x, gridPosition.y);
//
//            // Check if the grid position is free
//            if (!isFreeSpace(gridPosition, towers)) { // asda
//                previewTower.setFillColor(sf::Color::Red);
//            } else {
//                previewTower.setFillColor(sf::Color::Green);
//            }
//
//            // Draw the preview tower
//            sf::Color previewColor = previewTower.getFillColor();
//            previewColor.a = 100;
//            previewTower.setFillColor(previewColor);
//            window.draw(previewTower);
//
//            // Get the range of a PelletTower
//            int pelletTowerRange = 4 * GRID_CELL_SIZE; // Assuming there's a static method to get the range
//
//            // Draw the range circle around the preview tower
//            sf::CircleShape rangeCircle(pelletTowerRange);
//            rangeCircle.setFillColor(sf::Color(0, 255, 0, 100)); // Green with 50% transparency
//            rangeCircle.setOutlineColor(sf::Color::Black); // Black outline
//            rangeCircle.setOutlineThickness(1);
//            rangeCircle.setOrigin(pelletTowerRange, pelletTowerRange);
//            rangeCircle.setPosition(gridPosition.x, gridPosition.y);
//            window.draw(rangeCircle);
//        }
//
//        // Collision detection and bullet-enemy interaction
//
//
//        window.display();
//    }
//
//    return 0;
//}
//
