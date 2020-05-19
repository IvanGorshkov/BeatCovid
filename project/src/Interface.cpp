#include "Interface.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Level_map.h"

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window, Save &save) {
  sf::Texture menuNewGame, menuLoad, menuExit, aboutTexture, main_menuBackground, tShop;
  menuNewGame.loadFromFile("../files/menu/new_game.png");
  menuLoad.loadFromFile("../files/menu/load.png");
  menuExit.loadFromFile("../files/menu/exit.png");
  main_menuBackground.loadFromFile("../files/menu/main_menu.jpg");
  tShop.loadFromFile("../files/menu/shop.png");
  sf::Sprite MenuNewGame(menuNewGame);
  sf::Sprite MenuLoad(menuLoad);
  sf::Sprite MenuExit(menuExit);
  sf::Sprite MenuBg(main_menuBackground);
  sf::Sprite SMenu(tShop);
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
    SMenu.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 150);
    MenuExit.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 210);
    MenuBg.setPosition(center.x - size.x / 2 + 345, center.y - size.y / 2 + 0);
    MenuNewGame.setColor(sf::Color::White);
    MenuLoad.setColor(sf::Color::White);
    MenuExit.setColor(sf::Color::White);
    SMenu.setColor(sf::Color::White);
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
      SMenu.setColor(sf::Color::Blue);
      menuNum = 3;
    }
    if (sf::IntRect(100, 210, 300, 50).contains(sf::Mouse::getPosition(window))) {
      MenuExit.setColor(sf::Color::Blue);
      menuNum = 4;
    }


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        if (save.SaveExists()) {
          remove("../files/saves/save.txt");
        }
        if (save.SaveExistsA()) {
          remove("../files/saves/save_armor.txt");
        }
        if (save.SaveExistsP()) {
          remove("../files/saves/save_points.txt");
        }


        StartNewGame(window, save);
        for (int kI = 0; kI < 100000000; ++kI) {}
      }

      if (menuNum == 2) {
        if (save.SaveExists()) {
          StartNewGame(window, save);
        }
      }

      if (menuNum == 3) {
        Shop(window, save);
      }

      if (menuNum == 4) {
        window.close();
      }
    }

    window.draw(MenuBg);
    window.draw(MenuNewGame);
    window.draw(MenuLoad);
    window.draw(SMenu);
    window.draw(MenuExit);
    window.display();
  }
}
bool Interface::Shop(sf::RenderWindow &window, Save &save) {
  sf::Texture bg_arrmor, arms, buy, back;
  bg_arrmor.loadFromFile("../files/menu/bg_arrmor.png");
  arms.loadFromFile("../files/menu/arrmors.png");
  buy.loadFromFile("../files/menu/upgrade.png");
  back.loadFromFile("../files/menu/back.png");
  sf::Sprite BgArrmor(bg_arrmor);
  sf::Sprite Arms_glasses(arms);
  sf::Sprite Arms_gloves(arms);
  sf::Sprite Arms_robe(arms);
  sf::Sprite Arms_mask(arms);
  sf::Sprite buy_glasses(buy);
  sf::Sprite buy_gloves(buy);
  sf::Sprite buy_robe(buy);
  sf::Sprite buy_mask(buy);
  sf::Sprite backB(back);

  sf::Text points;
  sf::Text arm;
  sf::Text lvl_glasses;
  sf::Text lvl_mask;
  sf::Text lvl_gloves;
  sf::Text lvl_robe;

  sf::Text cost_glasses;
  sf::Text cost_mask;
  sf::Text cost_gloves;
  sf::Text cost_robe;

  sf::Font font;
  font.loadFromFile("../files/fonts/Inconsolata-Bold.ttf");
  points.setFont(font);
  points.setCharacterSize(40);
  points.setStyle(sf::Text::Bold);
  points.setColor(sf::Color::White);
  arm.setFont(font);
  arm.setCharacterSize(40);
  arm.setStyle(sf::Text::Bold);
  arm.setColor(sf::Color::White);

  lvl_glasses.setFont(font);
  lvl_glasses.setCharacterSize(40);
  lvl_glasses.setStyle(sf::Text::Bold);
  lvl_glasses.setColor(sf::Color::White);

  lvl_mask.setFont(font);
  lvl_mask.setCharacterSize(40);
  lvl_mask.setStyle(sf::Text::Bold);
  lvl_mask.setColor(sf::Color::White);

  lvl_gloves.setFont(font);
  lvl_gloves.setCharacterSize(40);
  lvl_gloves.setStyle(sf::Text::Bold);
  lvl_gloves.setColor(sf::Color::White);

  lvl_robe.setFont(font);
  lvl_robe.setCharacterSize(40);
  lvl_robe.setStyle(sf::Text::Bold);
  lvl_robe.setColor(sf::Color::White);

  cost_glasses.setFont(font);
  cost_glasses.setCharacterSize(40);
  cost_glasses.setStyle(sf::Text::Bold);
  cost_glasses.setColor(sf::Color::White);

  cost_mask.setFont(font);
  cost_mask.setCharacterSize(40);
  cost_mask.setStyle(sf::Text::Bold);
  cost_mask.setColor(sf::Color::White);

  cost_gloves.setFont(font);
  cost_gloves.setCharacterSize(40);
  cost_gloves.setStyle(sf::Text::Bold);
  cost_gloves.setColor(sf::Color::White);

  cost_robe.setFont(font);
  cost_robe.setCharacterSize(40);
  cost_robe.setStyle(sf::Text::Bold);
  cost_robe.setColor(sf::Color::White);

  int menuNum = 0;
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  BgArrmor.setPosition(center.x - size.x / 2 + 250, center.y - size.y / 2 + 50);
  points.setPosition(center.x - size.x / 2 + 750, center.y - size.y / 2 + 13);
  arm.setPosition(center.x - size.x / 2 + 350, center.y - size.y / 2 + 13);

  lvl_glasses.setPosition(center.x - size.x / 2 + 310, center.y - size.y / 2 + 230);
  lvl_mask.setPosition(center.x - size.x / 2 + 820, center.y - size.y / 2 + 230);
  lvl_gloves.setPosition(center.x - size.x / 2 + 310, center.y - size.y / 2 + 610);
  lvl_robe.setPosition(center.x - size.x / 2 + 820, center.y - size.y / 2 + 610);

  backB.setPosition(center.x - size.x / 2 + 20, center.y - size.y / 2 + 750);

  buy_glasses.setPosition(center.x - size.x / 2 + 110, center.y - size.y / 2 + 130);
  buy_mask.setPosition(center.x - size.x / 2 + 1020, center.y - size.y / 2 + 130);
  buy_gloves.setPosition(center.x - size.x / 2 + 110, center.y - size.y / 2 + 510);
  buy_robe.setPosition(center.x - size.x / 2 + 1020, center.y - size.y / 2 + 510);

  cost_glasses.setPosition(center.x - size.x / 2 + 145, center.y - size.y / 2 + 260);
  cost_mask.setPosition(center.x - size.x / 2 + 1060, center.y - size.y / 2 + 260);
  cost_gloves.setPosition(center.x - size.x / 2 + 145, center.y - size.y / 2 + 640);
  cost_robe.setPosition(center.x - size.x / 2 + 1060, center.y - size.y / 2 + 640);



  while (window.isOpen()) {
    std::vector<int> arm_vector = save.GetArmors();

    std::ostringstream ss;
    int money = save.GetPonits();
    ss << "Points: " << money;
    points.setString(ss.str());

    std::ostringstream ssarm;
    ssarm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2] + arm_vector[3];
    arm.setString(ssarm.str());

    std::ostringstream ss_glass;
    ss_glass << "LVL:" << arm_vector[0];
    lvl_glasses.setString(ss_glass.str());

    std::ostringstream ss_mask;
    ss_mask << "LVL:" << arm_vector[1];
    lvl_mask.setString(ss_mask.str());

    std::ostringstream ss_robe;
    ss_robe << "LVL:" << arm_vector[3];
    lvl_robe.setString(ss_robe.str());

    std::ostringstream ss_gloves;
    ss_gloves << "LVL:" << arm_vector[2];
    lvl_gloves.setString(ss_gloves.str());

    std::ostringstream ss_glass_cost;
    if (arm_vector[0] * 100 + 100 >= 500) {
      ss_glass_cost  << "max";
    } else {
      ss_glass_cost  << arm_vector[0] * 100 + 100;
    }
    cost_glasses.setString(ss_glass_cost.str());


    std::ostringstream ss_mask_cost;
    if (arm_vector[1] * 100 + 100 >= 500) {
      ss_mask_cost  << "max";
    } else {
      ss_mask_cost << arm_vector[1] * 100 + 100;
    }
    cost_mask.setString(ss_mask_cost.str());

    std::ostringstream ss_robe_cost;
    if (arm_vector[3] * 100 + 100 >= 500) {
      ss_robe_cost  << "max";
    } else {
      ss_robe_cost << arm_vector[3] * 100 + 100;
    }
    cost_robe.setString(ss_robe_cost.str());

    std::ostringstream ss_gloves_cost;
    if (arm_vector[2] * 100 + 100 >= 500) {
      ss_gloves_cost  << "max";
    } else {
      ss_gloves_cost  << arm_vector[2] * 100 + 100;
    }

    cost_gloves.setString(ss_gloves_cost.str());


    Arms_glasses.setPosition(center.x - size.x / 2 + 310, center.y - size.y / 2 + 100);
    Arms_glasses.setTextureRect(sf::Rect<int>(204 * arm_vector[0],176,196,169));
    Arms_gloves.setPosition(center.x - size.x / 2 + 310, center.y - size.y / 2 + 450);
    Arms_gloves.setTextureRect(sf::Rect<int>(204 * arm_vector[2],352,196,169));
    Arms_mask.setPosition(center.x - size.x / 2 + 770, center.y - size.y / 2 + 90);
    Arms_mask.setTextureRect(sf::Rect<int>(204 * arm_vector[1],526,196,165));
    Arms_robe.setPosition(center.x - size.x / 2 + 770, center.y - size.y / 2 + 450);
    Arms_robe.setTextureRect(sf::Rect<int>(204 * arm_vector[3],5,195,165));

    window.clear(sf::Color(129, 181, 221));
    buy_glasses.setColor(sf::Color::White);
    buy_mask.setColor(sf::Color::White);
    buy_gloves.setColor(sf::Color::White);
    buy_robe.setColor(sf::Color::White);
    backB.setColor(sf::Color::White);
    menuNum = -1;
    if (sf::IntRect(110, 130, 100, 100).contains(sf::Mouse::getPosition(window))) {
      buy_glasses.setColor(sf::Color::Blue);
      menuNum = 0;
    }

    if (sf::IntRect(1020, 130, 100, 100).contains(sf::Mouse::getPosition(window))) {
      buy_mask.setColor(sf::Color::Blue);
      menuNum = 1;
    }

    if (sf::IntRect(110, 510, 100, 100).contains(sf::Mouse::getPosition(window))) {
      buy_gloves.setColor(sf::Color::Blue);
      menuNum = 2;
    }

    if (sf::IntRect(1020, 510, 100, 100).contains(sf::Mouse::getPosition(window))) {
      buy_robe.setColor(sf::Color::Blue);
      menuNum = 3;
    }

    if (sf::IntRect(20, 700, 100, 100).contains(sf::Mouse::getPosition(window))) {
      backB.setColor(sf::Color::Blue);
      menuNum = 4;
    }

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (menuNum == 1 || menuNum == 0 || menuNum == 2 || menuNum == 3) {
            if (arm_vector[menuNum] < 4) {
              int cost = arm_vector[menuNum] * 100 + 100;
              if (cost <= money) {
                Buy(arm_vector, menuNum, save);
                save.SavePoints(money - cost);
              }
            }
          }
          if (menuNum == 4) {
            return true;
          }
        }
      }
    }


    window.draw(BgArrmor);
    window.draw(points);
    window.draw(arm);

    window.draw(lvl_glasses);
    window.draw(lvl_mask);
    window.draw(lvl_gloves);
    window.draw(lvl_robe);

    window.draw(Arms_glasses);
    window.draw(Arms_gloves);
    window.draw(Arms_robe);
    window.draw(Arms_mask);

    window.draw(buy_glasses);
    window.draw(buy_gloves);
    window.draw(buy_robe);
    window.draw(buy_mask);

    window.draw(cost_glasses);
    window.draw(cost_gloves);
    window.draw(cost_robe);
    window.draw(cost_mask);

    window.draw(backB);
    window.display();
  }

  return true;
}

void Interface::Buy(std::vector<int> arm_vector, int index, Save &save) {
  ++arm_vector[index];
  save.SaveArmor(arm_vector);
}

bool Interface::GameMenu(sf::RenderWindow &window, GameManager &game) {
  sf::Texture menuContinue, menuToMenu, saveGame, bg_arrmor, arms;
  menuToMenu.loadFromFile("../files/menu/to_menu.png");
  menuContinue.loadFromFile("../files/menu/continue.png");
  bg_arrmor.loadFromFile("../files/menu/bg_arrmor.png");
  arms.loadFromFile("../files/menu/arrmors.png");
  sf::Sprite MenuToMenu(menuToMenu);
  sf::Sprite MenuContinue(menuContinue);
  sf::Sprite BgArrmor(bg_arrmor);
  sf::Sprite Arms_glasses(arms);
  sf::Sprite Arms_gloves(arms);
  sf::Sprite Arms_robe(arms);
  sf::Sprite Arms_mask(arms);

  sf::Text points;
  sf::Text hp;
  sf::Text arm;
  sf::Text lvl_glasses;
  sf::Text lvl_mask;
  sf::Text lvl_gloves;
  sf::Text lvl_robe;
  sf::Font font;
  font.loadFromFile("../files/fonts/Inconsolata-Bold.ttf");
  points.setFont(font);
  points.setCharacterSize(40);
  points.setStyle(sf::Text::Bold);
  points.setColor(sf::Color::White);
  hp.setFont(font);
  hp.setCharacterSize(40);
  hp.setStyle(sf::Text::Bold);
  hp.setColor(sf::Color::White);
  arm.setFont(font);
  arm.setCharacterSize(40);
  arm.setStyle(sf::Text::Bold);
  arm.setColor(sf::Color::White);

  lvl_glasses.setFont(font);
  lvl_glasses.setCharacterSize(40);
  lvl_glasses.setStyle(sf::Text::Bold);
  lvl_glasses.setColor(sf::Color::White);

  lvl_mask.setFont(font);
  lvl_mask.setCharacterSize(40);
  lvl_mask.setStyle(sf::Text::Bold);
  lvl_mask.setColor(sf::Color::White);

  lvl_gloves.setFont(font);
  lvl_gloves.setCharacterSize(40);
  lvl_gloves.setStyle(sf::Text::Bold);
  lvl_gloves.setColor(sf::Color::White);

  lvl_robe.setFont(font);
  lvl_robe.setCharacterSize(40);
  lvl_robe.setStyle(sf::Text::Bold);
  lvl_robe.setColor(sf::Color::White);



  int menuNum = 0;
  std::vector<int> data = game.GetPlayer()->GetMainData();
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  MenuContinue.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  MenuToMenu.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 150);
  BgArrmor.setPosition(center.x - size.x / 2 + 500, center.y - size.y / 2 + 50);
  points.setPosition(center.x - size.x / 2 + 1000, center.y - size.y / 2 + 13);
  hp.setPosition(center.x - size.x / 2 + 800, center.y - size.y / 2 + 13);
  arm.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 13);
  lvl_glasses.setPosition(center.x - size.x / 2 + 560, center.y - size.y / 2 + 230);
  lvl_mask.setPosition(center.x - size.x / 2 + 1070, center.y - size.y / 2 + 230);
  lvl_gloves.setPosition(center.x - size.x / 2 + 560, center.y - size.y / 2 + 610);
  lvl_robe.setPosition(center.x - size.x / 2 + 1070, center.y - size.y / 2 + 610);
  Arms_glasses.setPosition(center.x - size.x / 2 + 520, center.y - size.y / 2 + 100);
  Arms_glasses.setTextureRect(sf::Rect<int>(204 * data[5],176,196,169));
  Arms_gloves.setPosition(center.x - size.x / 2 + 520, center.y - size.y / 2 + 450);
  Arms_gloves.setTextureRect(sf::Rect<int>(204 * data[4],352,196,169));
  Arms_mask.setPosition(center.x - size.x / 2 + 1020, center.y - size.y / 2 + 90);
  Arms_mask.setTextureRect(sf::Rect<int>(204 * data[3],526,196,165));
  Arms_robe.setPosition(center.x - size.x / 2 + 1020, center.y - size.y / 2 + 450);
  Arms_robe.setTextureRect(sf::Rect<int>(204 * data[6],5,195,165));

  std::ostringstream ss;
  ss << "Points: " << data[1];
  points.setString(ss.str());

  std::ostringstream sshp;
  sshp << "HP: " << data[0];
  hp.setString(sshp.str());

  std::ostringstream ssarm;
  ssarm << "ARM: " << data[2];
  arm.setString(ssarm.str());

  std::ostringstream ss_glass;
  ss_glass << "LVL:" << data[5];
  lvl_glasses.setString(ss_glass.str());

  std::ostringstream ss_mask;
  ss_mask << "LVL:" << data[4];
  lvl_mask.setString(ss_mask.str());

  std::ostringstream ss_robe;
  ss_robe << "LVL:" << data[3];
  lvl_robe.setString(ss_robe.str());

  std::ostringstream ss_gloves;
  ss_gloves << "LVL:" << data[6];
  lvl_gloves.setString(ss_gloves.str());



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
    window.draw(BgArrmor);
    window.draw(points);
    window.draw(hp);
    window.draw(arm);
    window.draw(lvl_glasses);
    window.draw(lvl_mask);
    window.draw(lvl_gloves);
    window.draw(lvl_robe);
    window.draw(Arms_glasses);
    window.draw(Arms_gloves);
    window.draw(Arms_robe);
    window.draw(Arms_mask);
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
  GameManager game(lvl, save.GetArmors());
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
  save.ChangeLvl();
  save.SaveGame(game);
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
