#include <sstream>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "Level_map.h"
#include "ResourcePath.hpp"

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window, Save &save) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite backImageSprite(resourcePath() + "files/menu/back_image.png", xPosition + 380, yPosition + 0);
  InterfaceSprite newGameSprite(resourcePath() + "files/menu/new_game.png", xPosition + 100, yPosition + 30);
  InterfaceSprite loadGameSprite(resourcePath() + "files/menu/load_game.png", xPosition + 100, yPosition + 90);
  InterfaceSprite statisticSprite(resourcePath() + "files/menu/statistic.png", xPosition + 100, yPosition + 150);
  InterfaceSprite shopSprite(resourcePath() + "files/menu/shop.png", xPosition + 100, yPosition + 210);
  InterfaceSprite exitSprite(resourcePath() + "files/menu/exit.png", xPosition + 100, yPosition + 270);
  InterfaceSprite aboutSprite(resourcePath() + "files/menu/about.png", xPosition + 100, yPosition + 700);

  MusicManager menuMusic;
  menuMusic.PlayBackgroundMenuMusic();

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
      ConfigMenu(window, menuMusic);
    }

//    if (event.type == sf::Event::TextEntered)
//    {
//      if (event.text.unicode >= 48 && event.text.unicode <= 57)
//        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
//    }

    newGameSprite.SetColor(sf::Color::White);
    loadGameSprite.SetColor(sf::Color::White);
    statisticSprite.SetColor(sf::Color::White);
    shopSprite.SetColor(sf::Color::White);
    exitSprite.SetColor(sf::Color::White);
    aboutSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    30,
                    newGameSprite.GetTextureRect().width,
                    newGameSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      newGameSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(100,
                    90,
                    loadGameSprite.GetTextureRect().width,
                    loadGameSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      loadGameSprite.SetColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::IntRect(100,
                    150,
                    statisticSprite.GetTextureRect().width,
                    statisticSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      statisticSprite.SetColor(sf::Color::Red);
      menuNum = 3;
    }

    if (sf::IntRect(100,
                    210,
                    shopSprite.GetTextureRect().width,
                    shopSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      shopSprite.SetColor(sf::Color::Red);
      menuNum = 4;
    }

    if (sf::IntRect(100,
                    270,
                    exitSprite.GetTextureRect().width,
                    exitSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      exitSprite.SetColor(sf::Color::Red);
      menuNum = 5;
    }

    if (sf::IntRect(100,
                    700,
                    aboutSprite.GetTextureRect().width,
                    aboutSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      aboutSprite.SetColor(sf::Color::Red);
      menuNum = 6;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

      if (menuNum == 1) {
        NewGameWarningMenu(window, menuMusic, save);
      }

      if (menuNum == 2) {
        if (Save::SaveExists()) {
          StartNewGame(window, save, menuMusic);
          menuMusic.PlayBackgroundMenuMusic();
        }
      }

      if (menuNum == 3) {
        StatisticMenu(window, menuMusic);
      }

      if (menuNum == 4) {
        Shop(window, save);
      }

      if (menuNum == 5) {
        window.close();
      }

      if (menuNum == 6) {
//        AboutMenu(window, menuMusic);
      }

    }

    backImageSprite.Draw(window);
    newGameSprite.Draw(window);
    loadGameSprite.Draw(window);
    shopSprite.Draw(window);
    exitSprite.Draw(window);
    aboutSprite.Draw(window);
    statisticSprite.Draw(window);
    window.display();
  }
}

// Предупреждение о сбросе данных
bool Interface::NewGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save) {
  if (!Save::SaveExists() && !Save::SaveExistsA() && !Save::SaveExistsP()) {
    StartNewGame(window, save, menuMusic);
    menuMusic.PlayBackgroundMenuMusic();
    for (int kI = 0; kI < 100000000; ++kI) {}
    return false;
  }

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite yesSprite(resourcePath() + "files/menu/yes.png", center.x - size.x / 2 + 800, center.y - size.y / 2 + 400);
  InterfaceSprite noSprite(resourcePath() + "files/menu/no.png", center.x - size.x / 2 + 200, center.y - size.y / 2 + 400);
  InterfaceSprite newGameWarningSprite(resourcePath() + "files/menu/new_game_warning.png", center.x - size.x / 2 + 10, center.y - size.y / 2 + 200);
  newGameWarningSprite.Scale(0.9f, 0.9f);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    yesSprite.SetColor(sf::Color::White);
    noSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(800,
                    400,
                    yesSprite.GetTextureRect().width,
                    yesSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      yesSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(200,
                    400,
                    noSprite.GetTextureRect().width,
                    noSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      noSprite.SetColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 2) {
        return true;
      }

      if (menuNum == 1) {
        std::ostringstream txt_save;
        txt_save << resourcePath() << "files/saves/save.txt";
        std::ostringstream save_armor;
        save_armor << resourcePath() << "files/saves/save_armor.txt";
        std::ostringstream save_points;
        save_points << resourcePath() << "files/saves/save_points.txt";

        if (Save::SaveExists()) {
          remove(txt_save.str().c_str());
        }

        if (Save::SaveExistsA()) {
          remove(save_armor.str().c_str());
        }

        if (Save::SaveExistsP()) {
          remove(save_points.str().c_str());
        }

        StartNewGame(window, save, menuMusic);
        menuMusic.PlayBackgroundMenuMusic();
        for (int kI = 0; kI < 100000000; ++kI) {}
        return false;
      }
    }

    yesSprite.Draw(window);
    noSprite.Draw(window);
    newGameWarningSprite.Draw(window);
    window.display();
  }

  return false;
}

bool Interface::Shop(sf::RenderWindow &window, Save &save) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite armorListSprite(resourcePath() + "files/menu/armor_list.png", xPosition + 250, yPosition + 80);
  InterfaceSprite armorShoesSprite(resourcePath() + "files/menu/armors.png", xPosition + 790, yPosition + 100);
  InterfaceSprite armorCapSprite(resourcePath() + "files/menu/armors.png", xPosition + 260, yPosition + 140);
  InterfaceSprite armorRobeSprite(resourcePath() + "files/menu/armors.png", xPosition + 530, yPosition + 540);
  InterfaceSprite buyShoesSprite(resourcePath() + "files/menu/upgrade.png", xPosition + 1010, yPosition + 160);
  InterfaceSprite buyCapSprite(resourcePath() + "files/menu/upgrade.png", xPosition + 110, yPosition + 160);
  InterfaceSprite buyRobeSprite(resourcePath() + "files/menu/upgrade.png", xPosition + 370, yPosition + 580);
  InterfaceSprite backSprite(resourcePath() + "files/menu/back.png", xPosition + 20, yPosition + 740);


  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceText pointsText(fontPath, 40, xPosition + 800, yPosition + 13);
  InterfaceText armText(fontPath, 40, xPosition + 300, yPosition + 13);
  InterfaceText lvlShoesText(fontPath, 40, xPosition + 840, yPosition + 240);
  InterfaceText lvlCapText(fontPath, 40, xPosition + 300, yPosition + 240);
  InterfaceText lvlRobeText(fontPath, 40, xPosition + 570, yPosition + 660);
  InterfaceText costShoesText(fontPath, 40, xPosition + 1045, yPosition + 290);
  InterfaceText costCapText(fontPath, 40, xPosition + 145, yPosition + 290);
  InterfaceText costRobeText(fontPath, 40, xPosition + 400, yPosition + 710);

  while (window.isOpen()) {
    std::vector<int> arm_vector = Save::LoadArmors();

    std::ostringstream ssPoints;
    int money = Save::LoadPoints();
    ssPoints << "Points: " << money;
    pointsText.SetText(ssPoints);

    std::ostringstream ssArm;
    ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
    armText.SetText(ssArm);

    std::ostringstream ssCap;
    ssCap << "LVL:" << arm_vector[0];
    lvlCapText.SetText(ssCap);

    std::ostringstream ssShoes;
    ssShoes << "LVL:" << arm_vector[1];
    lvlShoesText.SetText(ssShoes);

    std::ostringstream ssRobe;
    ssRobe << "LVL:" << arm_vector[2];
    lvlRobeText.SetText(ssRobe);

    std::ostringstream ssCapCost;
    if (arm_vector[0] * 100 + 100 >= 500) {
      ssCapCost << "max";
    } else {
      ssCapCost << arm_vector[0] * 100 + 100;
    }
    costCapText.SetText(ssCapCost);

    std::ostringstream ssShoesCost;
    if (arm_vector[1] * 100 + 100 >= 500) {
      ssShoesCost << "max";
    } else {
      ssShoesCost << arm_vector[1] * 100 + 100;
    }
    costShoesText.SetText(ssShoesCost);

    std::ostringstream ssRobeCost;
    if (arm_vector[2] * 100 + 100 >= 500) {
      ssRobeCost << "max";
    } else {
      ssRobeCost << arm_vector[2] * 100 + 100;
    }
    costRobeText.SetText(ssRobeCost);

    armorCapSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));
    armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));
    armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));

    window.clear(sf::Color(68, 101, 219));

    buyShoesSprite.SetColor(sf::Color::White);
    buyCapSprite.SetColor(sf::Color::White);
    buyRobeSprite.SetColor(sf::Color::White);
    backSprite.SetColor(sf::Color::White);

    int menuNum = -1;

    if (sf::IntRect(110,
                    160,
                    buyCapSprite.GetTextureRect().width,
                    buyCapSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      buyCapSprite.SetColor(sf::Color::Red);
      menuNum = 0;
    }

    if (sf::IntRect(1010,
                    160,
                    buyShoesSprite.GetTextureRect().width,
                    buyShoesSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      buyShoesSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(370,
                    580,
                    buyRobeSprite.GetTextureRect().width,
                    buyRobeSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      buyRobeSprite.SetColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::IntRect(20,
                    740,
                    backSprite.GetTextureRect().width,
                    backSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      backSprite.SetColor(sf::Color::Red);
      menuNum = 3;
    }

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (menuNum == 0 || menuNum == 1 || menuNum == 2) {
            if (arm_vector[menuNum] < 4) {
              int cost = arm_vector[menuNum] * 100 + 100;
              if (cost <= money) {
                Buy(arm_vector, menuNum);
                Save::SavePoints(money - cost);
              }
            }
          }

          if (menuNum == 3) {
            return true;
          }
        }
      }
    }

    armorListSprite.Draw(window);
    armorShoesSprite.Draw(window);
    armorCapSprite.Draw(window);
    armorRobeSprite.Draw(window);
    buyShoesSprite.Draw(window);
    buyCapSprite.Draw(window);
    buyRobeSprite.Draw(window);
    backSprite.Draw(window);

    pointsText.Draw(window);
    armText.Draw(window);
    lvlShoesText.Draw(window);
    lvlCapText.Draw(window);
    lvlRobeText.Draw(window);
    costShoesText.Draw(window);
    costCapText.Draw(window);
    costRobeText.Draw(window);

    window.display();
  }

  return true;
}

void Interface::Buy(std::vector<int> arm_vector, int index) {
  ++arm_vector[index];
  Save::SaveArmor(arm_vector);
}

bool Interface::GameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic) {
  menuMusic.StopBackgroundMenuMusic();

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite menuSprite(resourcePath() + "files/menu/menu.png", xPosition + 190, yPosition + 650);
  InterfaceSprite continueSprite(resourcePath() + "files/menu/continue.png", xPosition + 140, yPosition + 580);
  InterfaceSprite armorListSprite(resourcePath() + "files/menu/armor_list.png", xPosition + 500, yPosition + 100);
  InterfaceSprite armorCapSprite(resourcePath() + "files/menu/armors.png", xPosition + 520, yPosition + 150);
  InterfaceSprite armorShoesSprite(resourcePath() + "files/menu/armors.png", xPosition + 1050, yPosition + 120);
  InterfaceSprite armorRobeSprite(resourcePath() + "files/menu/armors.png", xPosition + 780, yPosition + 560);


  std::vector<int> data = game.GetPlayer()->GetMainData();

  armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * data[3], 352, 196, 169));
  armorCapSprite.SetTextureRect(sf::Rect<int>(204 * data[4], 41, 196, 85));
  armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * data[5], 200, 195, 165));

  std::ostringstream ssHp;
  ssHp << "HP: " << data[0] << "%";

  std::ostringstream ssArm;
  ssArm << "ARM: " << data[2];

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine: " << data[6];

  std::ostringstream ssPoints;
  ssPoints << "Points: " << data[1];

  std::ostringstream ssCap;
  ssCap << "LVL:" << data[4];

  std::ostringstream ssShoes;
  ssShoes << "LVL:" << data[3];

  std::ostringstream ssRobe;
  ssRobe << "LVL:" << data[5];

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceText pointsText(fontPath, 40, xPosition + 1000, yPosition + 13, ssPoints);
  InterfaceText hpText(fontPath, 40, xPosition + 10, yPosition + 13, ssHp);
  InterfaceText armText(fontPath, 40, xPosition + 200, yPosition + 13, ssArm);
  InterfaceText vaccineText(fontPath, 40, xPosition + 350, yPosition + 13, ssVaccine);

  InterfaceText lvlCapText(fontPath, 40, xPosition + 560, yPosition + 260, ssCap);
  InterfaceText lvlShoesText(fontPath, 40, xPosition + 1090, yPosition + 260, ssShoes);
  InterfaceText lvlRobeText(fontPath, 40, xPosition + 820, yPosition + 680, ssRobe);

  while (window.isOpen()) {

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueSprite.SetColor(sf::Color::White);
    menuSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(190,
                    650,
                    menuSprite.GetTextureRect().width,
                    menuSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(140,
                    580,
                    continueSprite.GetTextureRect().width,
                    continueSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.SetColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        std::vector<int> stat = game.GetStat();
        Save::SaveStat(stat);
        return false;
      }

      if (menuNum == 2) {
        return true;
      }

    }

    menuSprite.Draw(window);
    continueSprite.Draw(window);
    armorListSprite.Draw(window);
    armorShoesSprite.Draw(window);
    armorCapSprite.Draw(window);
    armorRobeSprite.Draw(window);

    pointsText.Draw(window);
    hpText.Draw(window);
    armText.Draw(window);
    vaccineText.Draw(window);
    lvlCapText.Draw(window);
    lvlShoesText.Draw(window);
    lvlRobeText.Draw(window);

    window.display();
  }

  return true;
}

// Старт новой игры
void Interface::StartNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic) {
  sf::View view(sf::FloatRect(0, 0, 1280, 800));

  menuMusic.StopBackgroundMenuMusic();

  Level lvl;
  lvl.LoadFromFile(save.GetLvlName());
  GameManager game(lvl, Save::LoadArmors(), menuMusic, Save::LoadStat(), Save::LoadConfig());
  sf::Clock clock;
  if (Save::SaveExists()) {
    save.Load(game);
  }

  while (window.isOpen()) {
    window.clear(sf::Color(0, 0, 0));
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();

    time = time / 400;

    if (time > 70) {
      time = 70;
    }

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          game.GetPlayer()->SetKey("SPACE", true);
          game.Fire();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
          game.TakeTransport();
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      game.GetPlayer()->SetKey("L", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      game.GetPlayer()->SetKey("R", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      game.GetPlayer()->SetKey("UP", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      game.GetPlayer()->SetKey("DOWN", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      bool status = GameMenu(window, game, menuMusic);
      if (!status) {
        break;
      }

    }
    if (game.GetPlayer()->GetAnim().GetCurrentFrame() == 3 && game.GetPlayer()->GetHp() <= 0) {
      menuMusic.PlayDiedPlayerSound();
      bool status = DiedMenu(window, game);
      if (status) {
        break;
      }
    }

    if (game.GetPlayer()->GetFinish()) {
      bool status = WinMenu(window, save, game, menuMusic);
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

// Экран смерти
bool Interface::DiedMenu(sf::RenderWindow &window, GameManager &game) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite wastedSprite(resourcePath() + "files/menu/wasted.png", xPosition + 540, yPosition + 330);
  InterfaceSprite menuSprite(resourcePath() + "files/menu/menu.png", xPosition + 570, yPosition + 390);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    wastedSprite.SetColor(sf::Color::White);
    menuSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(570,
                    390,
                    menuSprite.GetTextureRect().width,
                    menuSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        std::vector<int> stat = game.GetStat();
        stat[1]++;
        Save::SaveStat(stat);
        return true;
      }
    }

    wastedSprite.Draw(window);
    menuSprite.Draw(window);

    window.display();
  }

  return false;
}

// Экран победы
bool Interface::WinMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic) {
  std::string menuTexturePath;
  std::string continueMenuTexturePath;

  if (save.GetLvl() == MAX_LVL) {
    menuTexturePath = resourcePath() + "files/menu/menu.png";
    continueMenuTexturePath = resourcePath() + "files/menu/winner.png";
  } else {
    menuTexturePath = resourcePath() + "files/menu/menu.png";
    continueMenuTexturePath = resourcePath() + "files/menu/next_mission.png";
  }

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite continueMenuSprite(continueMenuTexturePath);
  InterfaceSprite menuSprite(menuTexturePath, xPosition + 570, center.y - size.y / 2 + 390);

  if (save.GetLvl() == MAX_LVL) {
    continueMenuSprite.SetPosition(xPosition + 20, yPosition + 200);
    continueMenuSprite.Scale(0.9f, 0.9f);
  } else {
    continueMenuSprite.SetPosition(xPosition + 450, yPosition + 330);
  }

  save.ChangeLvl();

  save.SaveGame(game);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueMenuSprite.SetColor(sf::Color::White);
    menuSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(550,
                    390,
                    menuSprite.GetTextureRect().width,
                    menuSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (save.GetLvl() != MAX_LVL + 1) {
      if (sf::IntRect(450,
                      330,
                      continueMenuSprite.GetTextureRect().width,
                      continueMenuSprite.GetTextureRect().height).
          contains(sf::Mouse::getPosition(window))) {

        continueMenuSprite.SetColor(sf::Color::Red);
        menuNum = 2;
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        menuMusic.StopBackgroundGameMusic();
        std::vector<int> stat = game.GetStat();
        stat[0]++;
        Save::SaveStat(stat);
        MainMenu(window, save);
      }

      if (menuNum == 2) {
        std::vector<int> stat = game.GetStat();
        stat[0]++;
        Save::SaveStat(stat);
        StartNewGame(window, save, menuMusic);
        return true;
      }
    }

    menuSprite.Draw(window);
    continueMenuSprite.Draw(window);

    window.display();
  }

  return true;
}

// Экран штраф от полицейского
bool Interface::PenaltyPolice(sf::RenderWindow &window) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite penaltyTextSprite(resourcePath() + "files/menu/penalty_police.png", xPosition + 100, yPosition + 30);
  InterfaceSprite continueSprite(resourcePath() + "files/menu/continue.png", xPosition + 100, yPosition + 90);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    90,
                    continueSprite.GetTextureRect().width,
                    continueSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    penaltyTextSprite.Draw(window);
    continueSprite.Draw(window);

    window.display();
  }

  return false;
}

// Экран умер от полицейского
bool Interface::DiedPolice(sf::RenderWindow &window) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite diedTextSprite(resourcePath() + "files/menu/died_police.png", xPosition + 100, yPosition + 30);
  InterfaceSprite continueSprite(resourcePath() + "files/menu/continue.png", xPosition + 100, yPosition + 90);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    90,
                    continueSprite.GetTextureRect().width,
                    continueSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    diedTextSprite.Draw(window);
    continueSprite.Draw(window);

    window.display();
  }

  return false;
}

bool Interface::AboutMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite backSprite(resourcePath() + "files/menu/back.png",xPosition + 20, yPosition + 740);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    backSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(20,
                    740,
                    backSprite.GetTextureRect().width,
                    backSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      backSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    backSprite.Draw(window);
    window.display();
  }

  return false;
}

bool Interface::StatisticMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite backSprite(resourcePath() + "files/menu/back.png", xPosition + 20, yPosition + 740);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  std::vector<int> stat = Save::LoadStat();

  std::ostringstream ssPatient;
  ssPatient << "Patients saved: " << stat[0];

  std::ostringstream ssDied;
  ssDied << "Hippocrates died: " << stat[1];

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine collected: " << stat[2];

  std::ostringstream ssAntigen;
  ssAntigen << "Antigen collected: " << stat[3];

  std::ostringstream ssPolice;
  ssPolice << "Police cured: " << stat[4];

  std::ostringstream ssBreaker;
  ssBreaker << "Breaker cured: " << stat[5];

  std::ostringstream ssDelivery;
  ssDelivery << "Delivery cured: " << stat[6];

  std::ostringstream ssVirus;
  ssVirus << "Virus cured: " << stat[7];

  std::ostringstream ssAuto;
  ssAuto << "Ambulance trips: " << stat[8];

  std::ostringstream ssMonorail;
  ssMonorail << "Monorail trips: " << stat[9];

  std::ostringstream ssBus;
  ssBus << "Bus trips: " << stat[10];

  std::ostringstream ssMetro;
  ssMetro << "Metro trips: " << stat[11];

  std::ostringstream ssPenalty;
  ssPenalty << "Penalty time: " << stat[12];

  std::ostringstream ssCaught;
  ssCaught << "Caught time: " << stat[13];

  float left = 150;
  float right = 700;
  float y = 170;

  InterfaceText patientText(fontPath, 40, xPosition + left, yPosition + y, ssPatient);
  InterfaceText diedText(fontPath, 40, xPosition + right, yPosition + y, ssDied);
  y += 60;

  InterfaceText vaccineText(fontPath, 40, xPosition + left, yPosition + y, ssVaccine);
  InterfaceText antigenText(fontPath, 40, xPosition + right, yPosition + y, ssAntigen);
  y += 60;

  InterfaceText policeText(fontPath, 40, xPosition + left, yPosition + y, ssPolice);
  InterfaceText breakerText(fontPath, 40, xPosition + right, yPosition + y, ssBreaker);
  y += 60;

  InterfaceText deliveryText(fontPath, 40, xPosition + left, yPosition + y, ssDelivery);
  InterfaceText virusText(fontPath, 40, xPosition + right, yPosition + y, ssVirus);
  y += 60;

  InterfaceText autoText(fontPath, 40, xPosition + left, yPosition + y, ssAuto);
  InterfaceText monorailText(fontPath, 40, xPosition + right, yPosition + y, ssMonorail);
  y += 60;

  InterfaceText busText(fontPath, 40, xPosition + left, yPosition + y, ssBus);
  InterfaceText metroText(fontPath, 40, xPosition + right, yPosition + y, ssMetro);
  y += 60;

  InterfaceText penaltyText(fontPath, 40, xPosition + left, yPosition + y, ssPenalty);
  InterfaceText caughtText(fontPath, 40, xPosition + right, yPosition + y, ssCaught);
  y += 60;

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    backSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(20,
                    740,
                    backSprite.GetTextureRect().width,
                    backSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      backSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    backSprite.Draw(window);

    patientText.Draw(window);
    diedText.Draw(window);
    vaccineText.Draw(window);
    antigenText.Draw(window);
    policeText.Draw(window);
    virusText.Draw(window);
    deliveryText.Draw(window);
    breakerText.Draw(window);
    autoText.Draw(window);
    monorailText.Draw(window);
    busText.Draw(window);
    metroText.Draw(window);
    penaltyText.Draw(window);
    caughtText.Draw(window);

    window.display();
  }

  return false;
}

bool Interface::ConfigMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  InterfaceSprite backSprite(resourcePath() + "files/menu/back.png", xPosition + 20, yPosition + 740);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  int points = Save::LoadPoints();
  std::vector<int> armors = Save::LoadArmors();
  std::vector<float> config = Save::LoadConfig();

  std::ostringstream ssCurrentLvl;
  ssCurrentLvl << "Current lvl: " << 0;

  std::ostringstream ssPlayerHp;
  ssPlayerHp << "Player hp: " << config[0];

  std::ostringstream ssCurrentPoints;
  ssCurrentPoints << "Current points: " << points;

  std::ostringstream ssAntigenPoints;
  ssAntigenPoints << "Antigen Points: " << config[1];

  std::ostringstream ssCapLvl;
  ssCapLvl << "Cap lvl: " << armors[0];

  std::ostringstream ssShoesLvl;
  ssShoesLvl << "Shoes lvl: " << armors[1];

  std::ostringstream ssRobeLvl;
  ssRobeLvl << "Robe lvl: " << armors[2];

  std::ostringstream ssPoliceHp;
  ssPoliceHp << "Police hp: " << config[2];

  std::ostringstream ssPoliceDmg;
  ssPoliceDmg << "Police dmg: " << config[3];

  std::ostringstream ssPolicePenalty;
  ssPolicePenalty << "Police penalty: " << config[4];

  std::ostringstream ssBreakerHp;
  ssBreakerHp << "Breaker hp: " << config[5];

  std::ostringstream ssBreakerDmg;
  ssBreakerDmg << "Breaker dmg: " << config[6];

  std::ostringstream ssDeliveryHp;
  ssDeliveryHp << "Delivery hp: " << config[7];

  std::ostringstream ssDeliveryDmg;
  ssDeliveryDmg << "Delivery dmg: " << config[8];

  std::ostringstream ssVirusHp;
  ssVirusHp << "Virus hp: " << config[9];

  std::ostringstream ssVirusDmg;
  ssVirusDmg << "Virus dmg: " << config[10];

  std::ostringstream ssAutoFuel;
  ssAutoFuel << "Ambulance fuel: " << config[11];

  std::ostringstream ssMonorailFuel;
  ssMonorailFuel << "Monorail fuel: " << config[12];

  std::ostringstream ssBusDmg;
  ssBusDmg << "Bus dmg: " << config[13];

  std::ostringstream ssMetroDmg;
  ssMetroDmg << "Metro dmg: " << config[14];

  float left = 150;
  float right = 700;
  float y = 100;

  InterfaceText currentLvlText(fontPath, 40, xPosition + left, yPosition + y, ssCurrentLvl);
  InterfaceText playerHpText(fontPath, 40, xPosition + right, yPosition + y, ssPlayerHp);
  y += 60;

  InterfaceText currentPointsText(fontPath, 40, xPosition + left, yPosition + y, ssCurrentPoints);
  InterfaceText antigenPointsText(fontPath, 40, xPosition + right, yPosition + y, ssAntigenPoints);
  y += 60;

  InterfaceText capLvlText(fontPath, 40, xPosition + left, yPosition + y, ssCapLvl);
  InterfaceText shoesLvlText(fontPath, 40, xPosition + right, yPosition + y, ssShoesLvl);
  y += 60;

  InterfaceText robeLvlText(fontPath, 40, xPosition + left, yPosition + y, ssRobeLvl);
  InterfaceText policeHpText(fontPath, 40, xPosition + right, yPosition + y, ssPoliceHp);
  y += 60;

  InterfaceText policeDmgText(fontPath, 40, xPosition + left, yPosition + y, ssPoliceDmg);
  InterfaceText policePenaltyText(fontPath, 40, xPosition + right, yPosition + y, ssPolicePenalty);
  y += 60;

  InterfaceText breakerHpText(fontPath, 40, xPosition + left, yPosition + y, ssBreakerHp);
  InterfaceText breakerDmgText(fontPath, 40, xPosition + right, yPosition + y, ssBreakerDmg);
  y += 60;

  InterfaceText deliveryHpText(fontPath, 40, xPosition + left, yPosition + y, ssDeliveryHp);
  InterfaceText deliveryDmgText(fontPath, 40, xPosition + right, yPosition + y, ssDeliveryDmg);
  y += 60;

  InterfaceText virusHpText(fontPath, 40, xPosition + left, yPosition + y, ssVirusHp);
  InterfaceText virusDmgText(fontPath, 40, xPosition + right, yPosition + y, ssVirusDmg);
  y += 60;

  InterfaceText autoFuelText(fontPath, 40, xPosition + left, yPosition + y, ssAutoFuel);
  InterfaceText monorailFuelText(fontPath, 40, xPosition + right, yPosition + y, ssMonorailFuel);
  y += 60;

  InterfaceText busDmgText(fontPath, 40, xPosition + left, yPosition + y, ssBusDmg);
  InterfaceText metroDmgText(fontPath, 40, xPosition + right, yPosition + y, ssMetroDmg);
  y += 60;

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    backSprite.SetColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(20,
                    740,
                    backSprite.GetTextureRect().width,
                    backSprite.GetTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      backSprite.SetColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    backSprite.Draw(window);

    currentLvlText.Draw(window);
    playerHpText.Draw(window);
    currentPointsText.Draw(window);
    antigenPointsText.Draw(window);
    capLvlText.Draw(window);
    shoesLvlText.Draw(window);
    robeLvlText.Draw(window);
    policeHpText.Draw(window);
    policeDmgText.Draw(window);
    policePenaltyText.Draw(window);
    breakerHpText.Draw(window);
    breakerDmgText.Draw(window);
    deliveryHpText.Draw(window);
    deliveryDmgText.Draw(window);
    virusHpText.Draw(window);
    virusDmgText.Draw(window);
    autoFuelText.Draw(window);
    monorailFuelText.Draw(window);
    busDmgText.Draw(window);
    metroDmgText.Draw(window);

    window.display();
  }

  return false;
}
