#include <sstream>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "Level_map.h"
#include "ResourcePath.hpp"

Interface &Interface::GetInstance(sf::RenderWindow &window) {
  static Interface instance(window);
  return instance;
}

Interface::Interface(sf::RenderWindow &window)
    : height(window.getSize().y),
      width(window.getSize().x),
      buttonSize(window.getSize().y / 25),
      textSize(window.getSize().y / 30),
      headSize(window.getSize().y / 20) {
}

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window) {
  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceSprite backImageSprite(resourcePath() + "files/menu/back_image.png");
  backImageSprite.SetPosition(700, 0);

  float left = buttonSize * 2;
  float up = buttonSize * 0.6;
  float dy = buttonSize * 1.4;
  InterfaceButton newGameButton(fontPath, buttonSize, left, up, "New Game");
  up += dy;
  InterfaceButton loadGameButton(fontPath, buttonSize, left, up, "Load Game");
  up += dy;
  InterfaceButton statisticButton(fontPath, buttonSize, left, up, "Statistic");
  up += dy;
  InterfaceButton shopButton(fontPath, buttonSize, left, up, "Shop");
  up += dy;
  InterfaceButton exitButton(fontPath, buttonSize, left, up, "Exit");

  InterfaceButton aboutButton(fontPath, buttonSize, left, height - left, "About");

  MusicManager menuMusic;
  menuMusic.PlayBackgroundMenuMusic();

  Save save;

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    //    if (event.type == sf::Event::TextEntered)
//    {
//      if (event.text.unicode >= 48 && event.text.unicode <= 57)
//        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
//    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (newGameButton.IsSelect(mousePosition)) {
      if (!Save::IsExistLvlFile()) {
        while (startNewGame(window, save, menuMusic)) {}
        menuMusic.PlayBackgroundMenuMusic();
      } else {
        newGameWarningMenu(window, menuMusic, save);
      }
    }

    if (loadGameButton.IsSelect(mousePosition)) {
      if (Save::IsExistLvlFile()) {
        while (startNewGame(window, save, menuMusic)) {}
        menuMusic.PlayBackgroundMenuMusic();
      }
    }

    if (statisticButton.IsSelect(mousePosition)) {
      statisticMenu(window, menuMusic);
    }

    if (shopButton.IsSelect(mousePosition)) {
      shopMenu(window, save);
    }

    if (exitButton.IsSelect(mousePosition)) {
      window.close();
    }

    if (aboutButton.IsSelect(mousePosition)) {
      aboutMenu(window, menuMusic);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::G)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
      configMenu(window, menuMusic);
    }

    window.clear(sf::Color(68, 101, 219));

    backImageSprite.Draw(window);
    newGameButton.Draw(window);
    loadGameButton.Draw(window);
    statisticButton.Draw(window);
    shopButton.Draw(window);
    exitButton.Draw(window);
    aboutButton.Draw(window);

    window.display();
  }
}

// Экран штраф от полицейского
void Interface::PenaltyPolice(sf::RenderWindow &window) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable penaltyTable;
  penaltyTable.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, "You were caught and fined"));
  penaltyTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Continue"));

  penaltyTable.CalculateTablePosition();
  penaltyTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (penaltyTable.GetCenterButtons()[0]->IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    penaltyTable.Draw(window);
    window.display();
  }
}

// Экран умер от полицейского
void Interface::DiedPolice(sf::RenderWindow &window) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable diedTable;
  diedTable.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, "You were caught and brought back"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Continue"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (diedTable.GetCenterButtons()[0]->IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }
}

// Предупреждение о сбросе данных
void Interface::newGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save) {
  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable newGameWarningTable;
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(fontPath, textSize, "Are you sure you want to start a new game?"));
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(fontPath, textSize, "All your saves will be lost"));
  newGameWarningTable.SetLeftButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Yes"));
  newGameWarningTable.SetRightButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "No"));

  newGameWarningTable.CalculateTablePosition();
  newGameWarningTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (newGameWarningTable.GetLeftButtons()[0]->IsSelect(mousePosition)) {
      Save::RemoveGameSaves();
      while (startNewGame(window, save, menuMusic)) {}
      menuMusic.PlayBackgroundMenuMusic();
      break;
    }

    if (newGameWarningTable.GetRightButtons()[0]->IsSelect(mousePosition)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    newGameWarningTable.Draw(window);
    window.display();
  }
}

// Старт новой игры
bool Interface::startNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

  menuMusic.StopBackgroundMenuMusic();

  Level lvl;
  lvl.LoadFromFile(save.GetLvlName());
  GameManager game(lvl, menuMusic, Save::LoadArmors(), Save::LoadPoints(), Save::LoadStat(), Save::LoadConfig());
  sf::Clock clock;

  while (window.isOpen()) {
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
      if (!gameMenu(window, game, menuMusic)) {
        return false;
      }
    }

    if (game.GetPlayer()->GetAnim().GetCurrentFrame() == 3 && game.GetPlayer()->GetHp() <= 0) {
      menuMusic.PlayDiedPlayerSound();
      return diedMenu(window, game);
    }

    if (game.GetPlayer()->GetFinish()) {
      if (save.GetLvl() == MAX_LVL) {
        return winMenu(window, save, game, menuMusic);
      } else {
        return nextLvlMenu(window, save, game, menuMusic);
      }
    }

    game.Update(time);

    window.clear(sf::Color(0, 0, 0));
    lvl.Draw(window);
    game.Draw(window);

    view.setCenter(game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);
    window.setView(view);
    window.display();
  }

  return false;
}

bool Interface::winMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic) {
  sf::View view(sf::FloatRect(0, 0, width, height));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable winTable;
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, headSize, "Congratulations!"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, headSize, "You have collected all the vaccines and were able to"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, headSize, "save the world from the fucking coronavirus"));
  winTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Menu"));

  winTable.CalculateTablePosition();
  winTable.SetPosition(height, width);

  save.SaveGame(game);

  std::vector<int> stat = game.GetStat();
  stat[0]++;
  Save::SaveStat(stat);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (winTable.GetCenterButtons()[0]->IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      return false;;
    }

    window.clear(sf::Color(68, 101, 219));
    winTable.Draw(window);
    window.display();
  }

  return false;
}

bool Interface::nextLvlMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic) {
  sf::View view(sf::FloatRect(0, 0, width, height));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable nextMissionTable;
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Next mission"));
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Menu"));

  nextMissionTable.CalculateTablePosition();
  nextMissionTable.SetPosition(height, width);

  save.ChangeLvl();
  save.SaveGame(game);

  std::vector<int> stat = game.GetStat();
  stat[0]++;
  Save::SaveStat(stat);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (nextMissionTable.GetCenterButtons()[0]->IsSelect(mousePosition)) {
      return true;
    }

    if (nextMissionTable.GetCenterButtons()[1]->IsSelect(mousePosition)) {
      menuMusic.StopBackgroundGameMusic();
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    nextMissionTable.Draw(window);
    window.display();
  }

  return false;
}

// Экран смерти
bool Interface::diedMenu(sf::RenderWindow &window, GameManager &game) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceTable diedTable;
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Restart"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "Menu"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  std::vector<int> stat = game.GetStat();
  stat[1]++;
  Save::SaveStat(stat);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (diedTable.GetCenterButtons()[0]->IsSelect(mousePosition)) {
      return true;
    }

    if (diedTable.GetCenterButtons()[1]->IsSelect(mousePosition)) {
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }

  return false;
}

void Interface::statisticMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceLabel statisticHeadText(fontPath, headSize, "Statistic menu");
  statisticHeadText.SetPosition((width - statisticHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable statisticTable;
  std::vector<int> stat = Save::LoadStat();

  std::ostringstream ssPatient;
  ssPatient << "Patients saved: " << stat[0];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPatient.str()));

  std::ostringstream ssDied;
  ssDied << "Hippocrates died: " << stat[1];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssDied.str()));

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine collected: " << stat[2];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssVaccine.str()));

  std::ostringstream ssAntigen;
  ssAntigen << "Antigen collected: " << stat[3];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssAntigen.str()));

  std::ostringstream ssPolice;
  ssPolice << "Police cured: " << stat[4];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPolice.str()));

  std::ostringstream ssBreaker;
  ssBreaker << "Breaker cured: " << stat[5];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssBreaker.str()));

  std::ostringstream ssDelivery;
  ssDelivery << "Delivery cured: " << stat[6];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssDelivery.str()));

  std::ostringstream ssVirus;
  ssVirus << "Virus cured: " << stat[7];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssVirus.str()));

  std::ostringstream ssAuto;
  ssAuto << "Ambulance trips: " << stat[8];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssAuto.str()));

  std::ostringstream ssMonorail;
  ssMonorail << "Monorail trips: " << stat[9];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssMonorail.str()));

  std::ostringstream ssBus;
  ssBus << "Bus trips: " << stat[10];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssBus.str()));

  std::ostringstream ssMetro;
  ssMetro << "Metro trips: " << stat[11];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssMetro.str()));

  std::ostringstream ssPenalty;
  ssPenalty << "Penalty time: " << stat[12];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPenalty.str()));

  std::ostringstream ssCaught;
  ssCaught << "Caught time: " << stat[13];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssCaught.str()));

  statisticTable.CalculateTablePosition();
  statisticTable.SetPosition(height, width);

  InterfaceButton backButton(fontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (backButton.IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    statisticHeadText.Draw(window);
    statisticTable.Draw(window);
    backButton.Draw(window);
    window.display();
  }
}

void Interface::configMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceLabel configurationHeadText(fontPath, headSize, "Configuration menu");
  configurationHeadText.SetPosition((width - configurationHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable configurationTable;
  int lvl = Save::LoadLvl();
  int points = Save::LoadPoints();
  std::vector<int> armors = Save::LoadArmors();
  std::vector<float> config = Save::LoadConfig();

  std::ostringstream ssCurrentLvl;
  ssCurrentLvl << "Current lvl: " << lvl;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssCurrentLvl.str()));

  std::ostringstream ssPlayerHp;
  ssPlayerHp << "Player hp: " << config[0];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPlayerHp.str()));

  std::ostringstream ssCurrentPoints;
  ssCurrentPoints << "Current points: " << points;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssCurrentPoints.str()));

  std::ostringstream ssAntigenPoints;
  ssAntigenPoints << "Antigen Points: " << config[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssAntigenPoints.str()));

  std::ostringstream ssCapLvl;
  ssCapLvl << "Cap lvl: " << armors[0];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssCapLvl.str()));

  std::ostringstream ssShoesLvl;
  ssShoesLvl << "Shoes lvl: " << armors[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssShoesLvl.str()));

  std::ostringstream ssRobeLvl;
  ssRobeLvl << "Robe lvl: " << armors[2];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssRobeLvl.str()));

  std::ostringstream ssPoliceHp;
  ssPoliceHp << "Police hp: " << config[2];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPoliceHp.str()));

  std::ostringstream ssPoliceDmg;
  ssPoliceDmg << "Police dmg: " << config[3];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPoliceDmg.str()));

  std::ostringstream ssPolicePenalty;
  ssPolicePenalty << "Police penalty: " << config[4];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssPolicePenalty.str()));

  std::ostringstream ssBreakerHp;
  ssBreakerHp << "Breaker hp: " << config[5];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssBreakerHp.str()));

  std::ostringstream ssBreakerDmg;
  ssBreakerDmg << "Breaker dmg: " << config[6];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssBreakerDmg.str()));

  std::ostringstream ssDeliveryHp;
  ssDeliveryHp << "Delivery hp: " << config[7];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssDeliveryHp.str()));

  std::ostringstream ssDeliveryDmg;
  ssDeliveryDmg << "Delivery dmg: " << config[8];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssDeliveryDmg.str()));

  std::ostringstream ssVirusHp;
  ssVirusHp << "Virus hp: " << config[9];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssVirusHp.str()));

  std::ostringstream ssVirusDmg;
  ssVirusDmg << "Virus dmg: " << config[10];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssVirusDmg.str()));

  std::ostringstream ssAutoFuel;
  ssAutoFuel << "Ambulance fuel: " << config[11];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssAutoFuel.str()));

  std::ostringstream ssMonorailFuel;
  ssMonorailFuel << "Monorail fuel: " << config[12];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssMonorailFuel.str()));

  std::ostringstream ssBusDmg;
  ssBusDmg << "Bus dmg: " << config[13];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssBusDmg.str()));

  std::ostringstream ssMetroDmg;
  ssMetroDmg << "Metro dmg: " << config[14];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, ssMetroDmg.str()));

  configurationTable.CalculateTablePosition();
  configurationTable.SetPosition(height, width);

  InterfaceButton backButton(fontPath, buttonSize, 30, height - buttonSize - 30, "Back");
  InterfaceButton defaultButton(fontPath, buttonSize, "Default");
  defaultButton.SetPosition(width - defaultButton.GetTextRectSize().x - 30, height - buttonSize - 30);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition)) {
      break;
    }

    if (defaultButton.IsSelect(mousePosition)) {
      Save::RemoveConfig();
    }

    window.clear(sf::Color(68, 101, 219));
    configurationHeadText.Draw(window);
    configurationTable.Draw(window);
    backButton.Draw(window);
    defaultButton.Draw(window);
    window.display();
  }
}

bool Interface::shopMenu(sf::RenderWindow &window, Save &save) {
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

  InterfaceLabel pointsText(fontPath, 40, xPosition + 800, yPosition + 13);
  InterfaceLabel armText(fontPath, 40, xPosition + 300, yPosition + 13);
  InterfaceLabel lvlShoesText(fontPath, 40, xPosition + 840, yPosition + 240);
  InterfaceLabel lvlCapText(fontPath, 40, xPosition + 300, yPosition + 240);
  InterfaceLabel lvlRobeText(fontPath, 40, xPosition + 570, yPosition + 660);
  InterfaceLabel costShoesText(fontPath, 40, xPosition + 1045, yPosition + 290);
  InterfaceLabel costCapText(fontPath, 40, xPosition + 145, yPosition + 290);
  InterfaceLabel costRobeText(fontPath, 40, xPosition + 400, yPosition + 710);

  while (window.isOpen()) {
    std::vector<int> arm_vector = Save::LoadArmors();

    std::ostringstream ssPoints;
    int money = Save::LoadPoints();
    ssPoints << "Points: " << money;
    pointsText.SetText(ssPoints.str());

    std::ostringstream ssArm;
    ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
    armText.SetText(ssArm.str());

    std::ostringstream ssCap;
    ssCap << "LVL:" << arm_vector[0];
    lvlCapText.SetText(ssCap.str());

    std::ostringstream ssShoes;
    ssShoes << "LVL:" << arm_vector[1];
    lvlShoesText.SetText(ssShoes.str());

    std::ostringstream ssRobe;
    ssRobe << "LVL:" << arm_vector[2];
    lvlRobeText.SetText(ssRobe.str());

    std::ostringstream ssCapCost;
    if (arm_vector[0] * 100 + 100 >= 500) {
      ssCapCost << "max";
    } else {
      ssCapCost << arm_vector[0] * 100 + 100;
    }
    costCapText.SetText(ssCapCost.str());

    std::ostringstream ssShoesCost;
    if (arm_vector[1] * 100 + 100 >= 500) {
      ssShoesCost << "max";
    } else {
      ssShoesCost << arm_vector[1] * 100 + 100;
    }
    costShoesText.SetText(ssShoesCost.str());

    std::ostringstream ssRobeCost;
    if (arm_vector[2] * 100 + 100 >= 500) {
      ssRobeCost << "max";
    } else {
      ssRobeCost << arm_vector[2] * 100 + 100;
    }
    costRobeText.SetText(ssRobeCost.str());

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
                buy(arm_vector, menuNum);
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

void Interface::buy(std::vector<int> arm_vector, int index) {
  ++arm_vector[index];
  Save::SaveArmor(arm_vector);
}

bool Interface::gameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

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

  InterfaceLabel pointsText(fontPath, 40, xPosition + 1000, yPosition + 13, ssPoints.str());
  InterfaceLabel hpText(fontPath, 40, xPosition + 10, yPosition + 13, ssHp.str());
  InterfaceLabel armText(fontPath, 40, xPosition + 200, yPosition + 13, ssArm.str());
  InterfaceLabel vaccineText(fontPath, 40, xPosition + 350, yPosition + 13, ssVaccine.str());

  InterfaceLabel lvlCapText(fontPath, 40, xPosition + 560, yPosition + 260, ssCap.str());
  InterfaceLabel lvlShoesText(fontPath, 40, xPosition + 1090, yPosition + 260, ssShoes.str());
  InterfaceLabel lvlRobeText(fontPath, 40, xPosition + 820, yPosition + 680, ssRobe.str());

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

bool Interface::aboutMenu(sf::RenderWindow &window, MusicManager &menuMusic) {
  std::string fontPath = resourcePath() + "files/fonts/Inconsolata-Bold.ttf";

  InterfaceButton backButton(fontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  InterfaceTable table1;
//  table1.SetCenterLabel(std::make_shared<InterfaceLabel>(fontPath, textSize, "Congratulations"));
  table1.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "TYK"));
  table1.SetCenterButton(std::make_shared<InterfaceButton>(fontPath, buttonSize, "TYK"));

  table1.CalculateTablePosition();
  table1.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (table1.GetCenterButtons()[0]->IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      return true;
    }

    if (backButton.IsSelect(sf::Vector2i(sf::Mouse::getPosition(window)))) {
      return true;
    }

    window.clear(sf::Color(68, 101, 219));

    backButton.Draw(window);
    table1.Draw(window);

    window.display();
  }

  return false;
}
