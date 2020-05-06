#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Interface {
public:
    Interface() = default;
    void StartNewGame(sf::RenderWindow & window);
    void GameMenu(sf::RenderWindow &window);
    void MainMenu(sf::RenderWindow &window);
    void DiedMenu(sf::RenderWindow &window);
};
