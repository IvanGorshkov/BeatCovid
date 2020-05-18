#include "Interface.h"

#include <SFML/Graphics.hpp>
#include "Level_map.h"

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window, Save &save) {
  sf::Texture menuNewGame, menuLoad, menuExit, aboutTexture, main_menuBackground;
  menuNewGame.loadFromFile("../files/menu/new_game.png");
  menuLoad.loadFromFile("../files/menu/load.png");
  menuExit.loadFromFile("../files/menu/exit.png");
  main_menuBackground.loadFromFile("../files/menu/main_menu.jpg");

  sf::Sprite MenuNewGame(menuNewGame);
  sf::Sprite MenuLoad(menuLoad);
  sf::Sprite MenuExit(menuExit);
  sf::Sprite MenuBg(main_menuBackground);

  int menuNum = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();
    MenuNewGame.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
    MenuLoad.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
    MenuExit.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 150);
    MenuBg.setPosition(center.x - size.x / 2 + 345, center.y - size.y / 2 + 0);
    MenuNewGame.setColor(sf::Color::White);
    MenuLoad.setColor(sf::Color::White);
    MenuExit.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuNewGame.setColor(sf::Color::Blue);
      menuNum = 1;
    }
    if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuLoad.setColor(sf::Color::Blue);
      menuNum = 2;
    }
    if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuExit.setColor(sf::Color::Blue);
      menuNum = 3;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        StartNewGame(window, save);
        for (int kI = 0; kI < 100000000; ++kI) {}
      }

      if (menuNum == 2) {
        window.close();

      }

      if (menuNum == 3) {
        window.close();
      }
    }

    window.draw(MenuBg);
    window.draw(MenuNewGame);
    window.draw(MenuLoad);
    window.draw(MenuExit);
    window.display();
  }
}

bool Interface::GameMenu(sf::RenderWindow &window, GameManager &game) {
  sf::Texture menuContinue, menuToMenu, saveGame;
  Save save;
  menuToMenu.loadFromFile("../files/menu/to_menu.png");
  menuContinue.loadFromFile("../files/menu/continue.png");
  sf::Sprite MenuToMenu(menuToMenu);
  sf::Sprite MenuContinue(menuContinue);
  int menuNum = 0;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  MenuContinue.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  MenuToMenu.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 150);
  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    MenuContinue.setColor(sf::Color::White);
    MenuToMenu.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuToMenu.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuContinue.setColor(sf::Color::Blue);
      menuNum = 2;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return false;
      }
      if (menuNum == 2) {
        return true;
      }

    }

    window.draw(MenuToMenu);
    window.draw(MenuContinue);

    window.display();
  }

  return true;
}

// Экран смерти
bool Interface::DiedMenu(sf::RenderWindow &window, Save &save) {
  sf::Texture deathMsg, menuToMenu;
  deathMsg.loadFromFile("../files/menu/dead.png");
  menuToMenu.loadFromFile("../files/menu/to_menu.png");
  sf::Sprite menu1(deathMsg);
  sf::Sprite menu2(menuToMenu);
  int menuNum = 0;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  menu1.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  menu2.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    menu1.setColor(sf::Color::White);
    menu2.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
      menu2.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(menu1);
    window.draw(menu2);
    window.display();
  }
  return false;
}

// Старт новой игры
void Interface::StartNewGame(sf::RenderWindow &window, Save &save) {
  sf::View view(sf::FloatRect(0, 0, 1280, 800));

  Level lvl;
  lvl.LoadFromFile(save.GetLvlName());
  GameManager game(lvl);
  sf::Clock clock;
  if (save.SaveExists()) {
    save.Load(game);
  }
  while (window.isOpen()) {
    window.clear(sf::Color(107, 140, 255));
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();

    time = time / 500;

    if (time > 40) {
      time = 40;
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

      if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
          game.TakeTransport();
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
      bool status = GameMenu(window, game);
      if (!status) {
        break;
      }

    }
    if (game.GetPlayer()->GetAnim().GetCurrentFrame() == 6 && game.GetPlayer()->GetHp() <= 0) {
      bool status = DiedMenu(window, save);
      if (status) {
        break;
      }
    }

    if (game.GetPlayer()->GetFinish()) {
      bool status = WinMenu(window, save, game);
      if (status) {
        break;
      }
    }
    game.Update(time);
    lvl.Draw(window);
    game.Draw(window);
    view.setCenter(game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);
    window.setView(view);
    window.display();
  }
}

bool Interface::WinMenu(sf::RenderWindow &window, Save &save, GameManager &game) {
  sf::Texture menuContinue, menuToMenu;
  menuToMenu.loadFromFile("../files/menu/to_menu.png");
  menuContinue.loadFromFile("../files/menu/next_mission.png");
  sf::Sprite MenuToMenu(menuToMenu);
  sf::Sprite MenuContinue(menuContinue);
  int menuNum = 0;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  MenuContinue.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  MenuToMenu.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    MenuContinue.setColor(sf::Color::White);
    MenuToMenu.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuToMenu.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuContinue.setColor(sf::Color::Blue);
      menuNum = 2;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return false;
      }
      if (menuNum == 2) {
        save.ChangeLvl();
        save.SaveGame(game);
        StartNewGame(window, save);
        return true;
      }
    }

    window.draw(MenuToMenu);
    window.draw(MenuContinue);

    window.display();
  }

  return true;
}

// Экран штраф от полицейского
bool Interface::PenaltyPolice(sf::RenderWindow &window) {
  sf::Texture deathMsg, menuToMenu;
  deathMsg.loadFromFile("../files/menu/penalty_police.png");
  menuToMenu.loadFromFile("../files/menu/continue.png");
  sf::Sprite menu1(deathMsg);
  sf::Sprite menu2(menuToMenu);
  int menuNum = 0;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  menu1.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  menu2.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    menu1.setColor(sf::Color::White);
    menu2.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
      menu2.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(menu1);
    window.draw(menu2);
    window.display();
  }

  return false;
}

// Экран умер от полицейского
bool Interface::DiedPolice(sf::RenderWindow &window) {
  sf::Texture deathMsg, menuToMenu;
  deathMsg.loadFromFile("../files/menu/died_police.png");
  menuToMenu.loadFromFile("../files/menu/continue.png");
  sf::Sprite menu1(deathMsg);
  sf::Sprite menu2(menuToMenu);
  int menuNum = 0;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  menu1.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  menu2.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    menu1.setColor(sf::Color::White);
    menu2.setColor(sf::Color::White);
    menuNum = 0;
    window.clear(sf::Color(129, 181, 221));

    if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
      menu2.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(menu1);
    window.draw(menu2);
    window.display();
  }

  return false;
}
