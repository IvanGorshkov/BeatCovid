#include <sstream>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "Level_map.h"

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window, Save &save) {
  sf::Texture BackImageTexture,
      NewGameTexture,
      LoadGameTexture,
      ShopTexture,
      ExitTexture,
      AboutTexture;

  BackImageTexture.loadFromFile(FILES_PATH"files/menu/back_image.png");
  NewGameTexture.loadFromFile(FILES_PATH"files/menu/new_game.png");
  LoadGameTexture.loadFromFile(FILES_PATH"files/menu/load_game.png");
  ShopTexture.loadFromFile(FILES_PATH"files/menu/shop.png");
  ExitTexture.loadFromFile(FILES_PATH"files/menu/exit.png");
  AboutTexture.loadFromFile(FILES_PATH"files/menu/about.png");

  sf::Sprite BackImageSprite(BackImageTexture);
  sf::Sprite NewGameSprite(NewGameTexture);
  sf::Sprite LoadGameSprite(LoadGameTexture);
  sf::Sprite ShopSprite(ShopTexture);
  sf::Sprite ExitSprite(ExitTexture);
  sf::Sprite AboutSprite(AboutTexture);

  MusicManager menuMusic;
  menuMusic.PlayBackgroundMenuMusic();

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    BackImageSprite.setPosition(center.x - size.x / 2 + 380, center.y - size.y / 2 + 0);
    NewGameSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
    LoadGameSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);
    ShopSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 150);
    ExitSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 210);
    AboutSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 700);

    NewGameSprite.setColor(sf::Color::White);
    LoadGameSprite.setColor(sf::Color::White);
    ShopSprite.setColor(sf::Color::White);
    ExitSprite.setColor(sf::Color::White);
    AboutSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    30,
                    NewGameSprite.getTextureRect().width,
                    NewGameSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      NewGameSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(100,
                    90,
                    LoadGameSprite.getTextureRect().width,
                    LoadGameSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      LoadGameSprite.setColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::IntRect(100,
                    150,
                    ShopSprite.getTextureRect().width,
                    ShopSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      ShopSprite.setColor(sf::Color::Red);
      menuNum = 3;
    }

    if (sf::IntRect(100,
                    210,
                    ExitSprite.getTextureRect().width,
                    ExitSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      ExitSprite.setColor(sf::Color::Red);
      menuNum = 4;
    }

    if (sf::IntRect(100,
                    700,
                    AboutSprite.getTextureRect().width,
                    AboutSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      AboutSprite.setColor(sf::Color::Red);
      menuNum = 5;
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
        Shop(window, save);
      }

      if (menuNum == 4) {
        window.close();
      }

      if (menuNum == 5) {
//        AboutMenu(window, menuMusic)
      }
    }

    window.draw(BackImageSprite);
    window.draw(NewGameSprite);
    window.draw(LoadGameSprite);
    window.draw(ShopSprite);
    window.draw(ExitSprite);
    window.draw(AboutSprite);
    window.display();
  }
}

// Не числтил
bool Interface::NewGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save) {
  if (!Save::SaveExists() && !Save::SaveExistsA() && !Save::SaveExistsP()) {
    StartNewGame(window, save, menuMusic);
    menuMusic.PlayBackgroundMenuMusic();
    for (int kI = 0; kI < 100000000; ++kI) {}
    return false;
  }

  sf::Texture yesTexture,
      noTexture,
      newGameWarningTexture;

  yesTexture.loadFromFile(FILES_PATH"files/menu/yes.png");
  noTexture.loadFromFile(FILES_PATH"files/menu/no.png");
  newGameWarningTexture.loadFromFile(FILES_PATH"files/menu/new_game_warning.png");

  sf::Sprite yesSprite(yesTexture);
  sf::Sprite noSprite(noTexture);
  sf::Sprite newGameWarningSprite(newGameWarningTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  yesSprite.setPosition(center.x - size.x / 2 + 800, center.y - size.y / 2 + 400);
  noSprite.setPosition(center.x - size.x / 2 + 200, center.y - size.y / 2 + 400);
  newGameWarningSprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 200);
  newGameWarningSprite.scale(0.9f, 0.9f);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    yesSprite.setColor(sf::Color::White);
    noSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(800,
                    400,
                    yesSprite.getTextureRect().width,
                    yesSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      yesSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(200,
                    400,
                    noSprite.getTextureRect().width,
                    noSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      noSprite.setColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 2) {
        return true;
      }

      if (menuNum == 1) {
        std::ostringstream txt_save;
        txt_save << FILES_PATH << "files/saves/save.txt";
        std::ostringstream save_armor;
        save_armor << FILES_PATH << "files/saves/save_armor.txt";
        std::ostringstream save_points;
        save_points << FILES_PATH << "files/saves/save_points.txt";

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

    window.draw(yesSprite);
    window.draw(noSprite);
    window.draw(newGameWarningSprite);
    window.display();
  }

  return false;
}

bool Interface::Shop(sf::RenderWindow &window, Save &save) {
  sf::Texture ArmorListTexture,
      ArmorsTexture,
      BuyTexture,
      BackTexture;

  ArmorListTexture.loadFromFile(FILES_PATH"files/menu/armor_list.png");
  ArmorsTexture.loadFromFile(FILES_PATH"files/menu/armors.png");
  BuyTexture.loadFromFile(FILES_PATH"files/menu/upgrade.png");
  BackTexture.loadFromFile(FILES_PATH"files/menu/back.png");

  sf::Sprite ArmorListSprite(ArmorListTexture);

  sf::Sprite ArmorShoesSprite(ArmorsTexture);
  sf::Sprite ArmorCapSprite(ArmorsTexture);
  sf::Sprite ArmorRobeSprite(ArmorsTexture);

  sf::Sprite BuyShoesSprite(BuyTexture);
  sf::Sprite BuyCapSprite(BuyTexture);
  sf::Sprite BuyRobeSprite(BuyTexture);

  sf::Sprite BackSprite(BackTexture);

  sf::Text PointsText;
  sf::Text ArmText;

  sf::Text lvlShoesText;
  sf::Text lvlCapText;
  sf::Text lvlRobeText;

  sf::Text costShoesText;
  sf::Text costCapText;
  sf::Text costRobeText;

  sf::Font font;
  font.loadFromFile(FILES_PATH"files/fonts/Inconsolata-Bold.ttf");

  PointsText.setFont(font);
  PointsText.setCharacterSize(40);
  PointsText.setStyle(sf::Text::Bold);
  PointsText.setFillColor(sf::Color::White);

  ArmText.setFont(font);
  ArmText.setCharacterSize(40);
  ArmText.setStyle(sf::Text::Bold);
  ArmText.setFillColor(sf::Color::White);

  lvlShoesText.setFont(font);
  lvlShoesText.setCharacterSize(40);
  lvlShoesText.setStyle(sf::Text::Bold);
  lvlShoesText.setFillColor(sf::Color::White);

  lvlCapText.setFont(font);
  lvlCapText.setCharacterSize(40);
  lvlCapText.setStyle(sf::Text::Bold);
  lvlCapText.setFillColor(sf::Color::White);

  lvlRobeText.setFont(font);
  lvlRobeText.setCharacterSize(40);
  lvlRobeText.setStyle(sf::Text::Bold);
  lvlRobeText.setFillColor(sf::Color::White);

  costShoesText.setFont(font);
  costShoesText.setCharacterSize(40);
  costShoesText.setStyle(sf::Text::Bold);
  costShoesText.setFillColor(sf::Color::White);

  costCapText.setFont(font);
  costCapText.setCharacterSize(40);
  costCapText.setStyle(sf::Text::Bold);
  costCapText.setFillColor(sf::Color::White);

  costRobeText.setFont(font);
  costRobeText.setCharacterSize(40);
  costRobeText.setStyle(sf::Text::Bold);
  costRobeText.setFillColor(sf::Color::White);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  ArmorListSprite.setPosition(center.x - size.x / 2 + 250, center.y - size.y / 2 + 80);

  BuyCapSprite.setPosition(center.x - size.x / 2 + 110, center.y - size.y / 2 + 160);
  BuyShoesSprite.setPosition(center.x - size.x / 2 + 1010, center.y - size.y / 2 + 160);
  BuyRobeSprite.setPosition(center.x - size.x / 2 + 370, center.y - size.y / 2 + 580);

  BackSprite.setPosition(center.x - size.x / 2 + 20, center.y - size.y / 2 + 740);

  PointsText.setPosition(center.x - size.x / 2 + 800, center.y - size.y / 2 + 13);
  ArmText.setPosition(center.x - size.x / 2 + 300, center.y - size.y / 2 + 13);

  lvlCapText.setPosition(center.x - size.x / 2 + 300, center.y - size.y / 2 + 240);
  lvlShoesText.setPosition(center.x - size.x / 2 + 840, center.y - size.y / 2 + 240);
  lvlRobeText.setPosition(center.x - size.x / 2 + 570, center.y - size.y / 2 + 660);

  costCapText.setPosition(center.x - size.x / 2 + 145, center.y - size.y / 2 + 290);
  costShoesText.setPosition(center.x - size.x / 2 + 1045, center.y - size.y / 2 + 290);
  costRobeText.setPosition(center.x - size.x / 2 + 400, center.y - size.y / 2 + 710);

  while (window.isOpen()) {
    std::vector<int> arm_vector = Save::GetArmors();

    std::ostringstream ssPoints;
    int money = Save::GetPonits();
    ssPoints << "Points: " << money;
    PointsText.setString(ssPoints.str());

    std::ostringstream ssArm;
    ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
    ArmText.setString(ssArm.str());

    std::ostringstream ssCap;
    ssCap << "LVL:" << arm_vector[0];
    lvlCapText.setString(ssCap.str());

    std::ostringstream ssShoes;
    ssShoes << "LVL:" << arm_vector[1];
    lvlShoesText.setString(ssShoes.str());

    std::ostringstream ssRobe;
    ssRobe << "LVL:" << arm_vector[2];
    lvlRobeText.setString(ssRobe.str());

    std::ostringstream ssCapCost;
    if (arm_vector[0] * 100 + 100 >= 500) {
      ssCapCost << "max";
    } else {
      ssCapCost << arm_vector[0] * 100 + 100;
    }
    costCapText.setString(ssCapCost.str());

    std::ostringstream ssShoesCost;
    if (arm_vector[1] * 100 + 100 >= 500) {
      ssShoesCost << "max";
    } else {
      ssShoesCost << arm_vector[1] * 100 + 100;
    }
    costShoesText.setString(ssShoesCost.str());

    std::ostringstream ssRobeCost;
    if (arm_vector[2] * 100 + 100 >= 500) {
      ssRobeCost << "max";
    } else {
      ssRobeCost << arm_vector[2] * 100 + 100;
    }
    costRobeText.setString(ssRobeCost.str());

    ArmorCapSprite.setPosition(center.x - size.x / 2 + 260, center.y - size.y / 2 + 140);
    ArmorCapSprite.setTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));

    ArmorShoesSprite.setPosition(center.x - size.x / 2 + 790, center.y - size.y / 2 + 100);
    ArmorShoesSprite.setTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));

    ArmorRobeSprite.setPosition(center.x - size.x / 2 + 530, center.y - size.y / 2 + 540);
    ArmorRobeSprite.setTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));

    window.clear(sf::Color(68, 101, 219));

    BuyShoesSprite.setColor(sf::Color::White);
    BuyCapSprite.setColor(sf::Color::White);
    BuyRobeSprite.setColor(sf::Color::White);
    BackSprite.setColor(sf::Color::White);

    int menuNum = -1;

    if (sf::IntRect(110,
                    160,
                    BuyCapSprite.getTextureRect().width,
                    BuyCapSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      BuyCapSprite.setColor(sf::Color::Red);
      menuNum = 0;
    }

    if (sf::IntRect(1010,
                    160,
                    BuyShoesSprite.getTextureRect().width,
                    BuyShoesSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      BuyShoesSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(370,
                    580,
                    BuyRobeSprite.getTextureRect().width,
                    BuyRobeSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      BuyRobeSprite.setColor(sf::Color::Red);
      menuNum = 2;
    }

    if (sf::IntRect(20,
                    740,
                    BackSprite.getTextureRect().width,
                    BackSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      BackSprite.setColor(sf::Color::Red);
      menuNum = 4;
    }

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (menuNum == 0 || menuNum == 1 || menuNum == 2 || menuNum == 3) {
            if (arm_vector[menuNum] < 4) {
              int cost = arm_vector[menuNum] * 100 + 100;
              if (cost <= money) {
                Buy(arm_vector, menuNum);
                Save::SavePoints(money - cost);
              }
            }
          }

          if (menuNum == 4) {
            return true;
          }
        }
      }
    }

    window.draw(ArmorListSprite);

    window.draw(ArmorShoesSprite);
    window.draw(ArmorCapSprite);
    window.draw(ArmorRobeSprite);

    window.draw(BuyShoesSprite);
    window.draw(BuyCapSprite);
    window.draw(BuyRobeSprite);

    window.draw(BackSprite);

    window.draw(PointsText);
    window.draw(ArmText);

    window.draw(lvlShoesText);
    window.draw(lvlCapText);
    window.draw(lvlRobeText);

    window.draw(costShoesText);
    window.draw(costCapText);
    window.draw(costRobeText);

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

  sf::Texture continueTexture,
      menuTexture,
      armorListTexture,
      armorsTexture;

  menuTexture.loadFromFile(FILES_PATH"files/menu/menu.png");
  continueTexture.loadFromFile(FILES_PATH"files/menu/continue.png");
  armorListTexture.loadFromFile(FILES_PATH"files/menu/armor_list.png");
  armorsTexture.loadFromFile(FILES_PATH"files/menu/armors.png");

  sf::Sprite menuSprite(menuTexture);
  sf::Sprite continueSprite(continueTexture);
  sf::Sprite armorListSprite(armorListTexture);

  sf::Sprite armorCapSprite(armorsTexture);
  sf::Sprite armorShoesSprite(armorsTexture);
  sf::Sprite armorRobeSprite(armorsTexture);

  sf::Text pointsText;
  sf::Text hpText;
  sf::Text armText;
  sf::Text vaccineText;

  sf::Text lvlCapText;
  sf::Text lvlShoesText;
  sf::Text lvlRobeText;

  sf::Font font;
  font.loadFromFile(FILES_PATH"files/fonts/Inconsolata-Bold.ttf");

  pointsText.setFont(font);
  pointsText.setCharacterSize(40);
  pointsText.setStyle(sf::Text::Bold);
  pointsText.setFillColor(sf::Color::White);

  hpText.setFont(font);
  hpText.setCharacterSize(40);
  hpText.setStyle(sf::Text::Bold);
  hpText.setFillColor(sf::Color::White);

  armText.setFont(font);
  armText.setCharacterSize(40);
  armText.setStyle(sf::Text::Bold);
  armText.setFillColor(sf::Color::White);

  vaccineText.setFont(font);
  vaccineText.setCharacterSize(40);
  vaccineText.setStyle(sf::Text::Bold);
  vaccineText.setFillColor(sf::Color::White);

  lvlCapText.setFont(font);
  lvlCapText.setCharacterSize(40);
  lvlCapText.setStyle(sf::Text::Bold);
  lvlCapText.setFillColor(sf::Color::White);

  lvlShoesText.setFont(font);
  lvlShoesText.setCharacterSize(40);
  lvlShoesText.setStyle(sf::Text::Bold);
  lvlShoesText.setFillColor(sf::Color::White);

  lvlRobeText.setFont(font);
  lvlRobeText.setCharacterSize(40);
  lvlRobeText.setStyle(sf::Text::Bold);
  lvlRobeText.setFillColor(sf::Color::White);

  std::vector<int> data = game.GetPlayer()->GetMainData();
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  continueSprite.setPosition(center.x - size.x / 2 + 140, center.y - size.y / 2 + 580);
  menuSprite.setPosition(center.x - size.x / 2 + 190, center.y - size.y / 2 + 650);
  armorListSprite.setPosition(center.x - size.x / 2 + 500, center.y - size.y / 2 + 100);

  armorShoesSprite.setPosition(center.x - size.x / 2 + 1050, center.y - size.y / 2 + 120);
  armorShoesSprite.setTextureRect(sf::Rect<int>(204 * data[3], 352, 196, 169));

  armorCapSprite.setPosition(center.x - size.x / 2 + 520, center.y - size.y / 2 + 150);
  armorCapSprite.setTextureRect(sf::Rect<int>(204 * data[4], 41, 196, 85));

  armorRobeSprite.setPosition(center.x - size.x / 2 + 780, center.y - size.y / 2 + 560);
  armorRobeSprite.setTextureRect(sf::Rect<int>(204 * data[5], 200, 195, 165));

  pointsText.setPosition(center.x - size.x / 2 + 1000, center.y - size.y / 2 + 13);
  hpText.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 13);
  armText.setPosition(center.x - size.x / 2 + 200, center.y - size.y / 2 + 13);
  vaccineText.setPosition(center.x - size.x / 2 + 350, center.y - size.y / 2 + 13);

  lvlCapText.setPosition(center.x - size.x / 2 + 560, center.y - size.y / 2 + 260);
  lvlShoesText.setPosition(center.x - size.x / 2 + 1090, center.y - size.y / 2 + 260);
  lvlRobeText.setPosition(center.x - size.x / 2 + 820, center.y - size.y / 2 + 680);

  std::ostringstream ssHp;
  ssHp << "HP: " << data[0] << "%";
  hpText.setString(ssHp.str());

  std::ostringstream ssArm;
  ssArm << "ARM: " << data[2];
  armText.setString(ssArm.str());

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine: " << data[6];
  vaccineText.setString(ssVaccine.str());

  std::ostringstream ssPoints;
  ssPoints << "Points: " << data[1];
  pointsText.setString(ssPoints.str());

  std::ostringstream ssGlass;
  ssGlass << "LVL:" << data[4];
  lvlCapText.setString(ssGlass.str());

  std::ostringstream ssMask;
  ssMask << "LVL:" << data[3];
  lvlShoesText.setString(ssMask.str());

  std::ostringstream ssRobe;
  ssRobe << "LVL:" << data[5];
  lvlRobeText.setString(ssRobe.str());

  while (window.isOpen()) {

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueSprite.setColor(sf::Color::White);
    menuSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(190,
                    650,
                    menuSprite.getTextureRect().width,
                    menuSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::IntRect(140,
                    580,
                    continueSprite.getTextureRect().width,
                    continueSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.setColor(sf::Color::Red);
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

    window.draw(menuSprite);
    window.draw(continueSprite);
    window.draw(armorListSprite);

    window.draw(armorShoesSprite);
    window.draw(armorCapSprite);
    window.draw(armorRobeSprite);

    window.draw(pointsText);
    window.draw(hpText);
    window.draw(armText);
    window.draw(vaccineText);

    window.draw(lvlCapText);
    window.draw(lvlShoesText);
    window.draw(lvlRobeText);

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
  GameManager game(lvl, Save::GetArmors(), menuMusic, Save::LoadStat());
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
  sf::Texture wastedTexutre,
      menuTexture;

  wastedTexutre.loadFromFile(FILES_PATH"files/menu/wasted.png");
  menuTexture.loadFromFile(FILES_PATH"files/menu/menu.png");

  sf::Sprite wastedSprite(wastedTexutre);
  sf::Sprite menuSprite(menuTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  wastedSprite.setPosition(center.x - size.x / 2 + 540, center.y - size.y / 2 + 330);
  menuSprite.setPosition(center.x - size.x / 2 + 570, center.y - size.y / 2 + 390);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    wastedSprite.setColor(sf::Color::White);
    menuSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(570,
                    390,
                    menuSprite.getTextureRect().width,
                    menuSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        std::vector<int> stat = game.GetStat();
        Save::SaveStat(stat);
        return true;
      }
    }

    window.draw(wastedSprite);
    window.draw(menuSprite);

    window.display();
  }

  return false;
}

// Экран победы
bool Interface::WinMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic) {
  sf::Texture menuTexture,
      continueMenuTexture;

  if (save.GetLvl() == MAX_LVL) {
    menuTexture.loadFromFile(FILES_PATH"files/menu/menu.png");
    continueMenuTexture.loadFromFile(FILES_PATH"files/menu/winner.png");
  } else {
    menuTexture.loadFromFile(FILES_PATH"files/menu/menu.png");
    continueMenuTexture.loadFromFile(FILES_PATH"files/menu/next_mission.png");
  }

  sf::Sprite menuSprite(menuTexture);
  sf::Sprite continueMenuSprite(continueMenuTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  if (save.GetLvl() == MAX_LVL) {
    continueMenuSprite.setPosition(center.x - size.x / 2 + 20, center.y - size.y / 2 + 200);
    continueMenuSprite.scale(0.9f, 0.9f);
  } else {
    continueMenuSprite.setPosition(center.x - size.x / 2 + 450, center.y - size.y / 2 + 330);
  }

  menuSprite.setPosition(center.x - size.x / 2 + 570, center.y - size.y / 2 + 390);

  save.ChangeLvl();

  save.SaveGame(game);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    continueMenuSprite.setColor(sf::Color::White);
    menuSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(550,
                    390,
                    menuSprite.getTextureRect().width,
                    menuSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      menuSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (save.GetLvl() != MAX_LVL + 1) {
      if (sf::IntRect(450,
                      330,
                      continueMenuSprite.getTextureRect().width,
                      continueMenuSprite.getTextureRect().height).
          contains(sf::Mouse::getPosition(window))) {

        continueMenuSprite.setColor(sf::Color::Red);
        menuNum = 2;
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        menuMusic.StopBackgroundGameMusic();
        std::vector<int> stat = game.GetStat();
        stat[0]++;
        std::cout << "Patient: " << stat[0] << std::endl;
        save.SaveStat(stat);
        MainMenu(window, save);
      }

      if (menuNum == 2) {
        std::vector<int> stat = game.GetStat();
        stat[0]++;
        std::cout << "Patient: " << stat[0] << std::endl;
        save.SaveStat(stat);
        StartNewGame(window, save, menuMusic);
        return true;
      }
    }

    window.draw(menuSprite);
    window.draw(continueMenuSprite);

    window.display();
  }

  return true;
}

// Экран штраф от полицейского
bool Interface::PenaltyPolice(sf::RenderWindow &window) {
  sf::Texture penaltyTextTexture,
      continueTexture;

  penaltyTextTexture.loadFromFile(FILES_PATH"files/menu/penalty_police.png");
  continueTexture.loadFromFile(FILES_PATH"files/menu/continue.png");

  sf::Sprite penaltyTextSprite(penaltyTextTexture);
  sf::Sprite continueSprite(continueTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  penaltyTextSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  continueSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    penaltyTextSprite.setColor(sf::Color::White);
    continueSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    90,
                    continueSprite.getTextureRect().width,
                    continueSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(penaltyTextSprite);
    window.draw(continueSprite);

    window.display();
  }

  return false;
}

// Экран умер от полицейского
bool Interface::DiedPolice(sf::RenderWindow &window) {
  sf::Texture diedTextTexture,
      continueTexture;

  diedTextTexture.loadFromFile(FILES_PATH"files/menu/died_police.png");
  continueTexture.loadFromFile(FILES_PATH"files/menu/continue.png");

  sf::Sprite diedTextSprite(diedTextTexture);
  sf::Sprite continueSprite(continueTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  diedTextSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 30);
  continueSprite.setPosition(center.x - size.x / 2 + 100, center.y - size.y / 2 + 90);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    diedTextSprite.setColor(sf::Color::White);
    continueSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(100,
                    90,
                    continueSprite.getTextureRect().width,
                    continueSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      continueSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(diedTextSprite);
    window.draw(continueSprite);

    window.display();
  }

  return false;
}

bool Interface::AboutMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  sf::Texture backTexture;
  backTexture.loadFromFile(FILES_PATH"files/menu/back.png");
  sf::Sprite backSprite(backTexture);

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  backSprite.setPosition(center.x - size.x / 2 + 20, center.y - size.y / 2 + 740);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    backSprite.setColor(sf::Color::White);

    int menuNum = 0;

    window.clear(sf::Color(68, 101, 219));

    if (sf::IntRect(20,
                    740,
                    backSprite.getTextureRect().width,
                    backSprite.getTextureRect().height).
        contains(sf::Mouse::getPosition(window))) {

      backSprite.setColor(sf::Color::Red);
      menuNum = 1;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menuNum == 1) {
        return true;
      }
    }

    window.draw(backSprite);
    window.display();
  }

  return false;
}
