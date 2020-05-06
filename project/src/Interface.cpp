#include "Interface.h"

#include <SFML/Graphics.hpp>
#include "Level_map.h"
#include "GameManager.h"

// Вывод главного меню

void Interface::MainMenu(sf::RenderWindow & window) {
    sf::Texture menuNewGame, menuLoad, menuExit, aboutTexture, main_menuBackground;
    menuNewGame.loadFromFile("../files/menu/new_game.png");
    menuLoad.loadFromFile("../files/menu/load.png");
    menuExit.loadFromFile("../files/menu/exit.png");
    main_menuBackground.loadFromFile("../files/menu/main_menu.jpg");

    sf::Sprite MenuNewGame(menuNewGame);
    sf::Sprite MenuLoad(menuLoad);
    sf::Sprite MenuExit(menuExit);
    sf::Sprite MenuBg(main_menuBackground);

    bool isMenu = 1;
    int menuNum = 0;

    MenuNewGame.setPosition(100, 30);
    MenuLoad.setPosition(100, 90);
    MenuExit.setPosition(100, 150);
    MenuBg.setPosition(345, 0);

    while (isMenu) {
        MenuNewGame.setColor(sf::Color::White);
        MenuLoad.setColor(sf::Color::White);
        MenuExit.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { MenuNewGame.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { MenuLoad.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { MenuExit.setColor(sf::Color::Blue); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) {
                StartNewGame(window);
                isMenu = false;
            }
            if (menuNum == 2) { window.close(); isMenu = false;  }
            if (menuNum == 3)  { window.close(); isMenu = false; }

        }

        window.draw(MenuBg);
        window.draw(MenuNewGame);
        window.draw(MenuLoad);
        window.draw(MenuExit);

        window.display();
    }
}

// вывод игрового меню (привязка к offset x,y, не разобрался как решить)

void Interface::GameMenu(sf::RenderWindow &window) {
    sf::Texture menuContinue, menuToMenu;
    menuToMenu.loadFromFile("../files/menu/to_menu.png");
    menuContinue.loadFromFile("../files/menu/continue.png");
    sf::Sprite MenuToMenu(menuToMenu);
    sf::Sprite MenuContinue(menuContinue);

    bool isMenu = 1;
    int menuNum = 0;

    MenuContinue.setPosition(100, 30);
    MenuToMenu.setPosition(100, 90);

    while (isMenu) {
        MenuContinue.setColor(sf::Color::White);
        MenuToMenu.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { MenuToMenu.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { MenuContinue.setColor(sf::Color::Blue); menuNum = 2; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1)  {
                menuNum = 0;
                MainMenu(window);
                isMenu = false;
            }
            if (menuNum == 2) {
                isMenu = false;
            }
        }

        window.draw(MenuToMenu);
        window.draw(MenuContinue);

        window.display();
    }
}

// Экран смерти
void Interface::DiedMenu(sf::RenderWindow &window) {
    sf::Texture deathMsg, menuToMenu;
    deathMsg.loadFromFile("../files/menu/dead.png");
    menuToMenu.loadFromFile("../files/menu/to_menu.png");
    sf::Sprite menu1(deathMsg);
    sf::Sprite menu2(menuToMenu);

    bool isMenu = 1;
    int menuNum = 0;

    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);

    while (isMenu) {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 1; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) {
                isMenu = false;
                MainMenu(window);
            }
        }

        window.draw(menu1);
        window.draw(menu2);

        window.display();
    }
}

// Старт новой игры
void Interface::StartNewGame(sf::RenderWindow & window) {
    sf::View view(sf::FloatRect(0, 0, 1280, 800));

    Level lvl;
    lvl.LoadFromFile("../files/test_map.tmx");
    GameManager game(lvl);
    sf::Clock clock;
    Interface inter;
    while (window.isOpen()) {
        window.clear(sf::Color(107, 140, 255));
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 500;

        if (time > 20) {
            time = 20;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    game.Fire();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            game.GetPlayer()->SetKey("L", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            game.GetPlayer()->SetKey("R", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            game.GetPlayer()->SetKey("UP", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            game.GetPlayer()->SetKey("DOWN", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            GameMenu(window);
        }
        if (game.GetPlayer()->GetHp() == 0) {
            DiedMenu(window);
        }

        game.Update(time);

        lvl.Draw(window);
        game.Draw(window);

        view.setCenter(game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);
        window.setView(view);

        window.display();
    }
}
