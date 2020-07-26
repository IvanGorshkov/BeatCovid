#include "Interface.h"
#include <sstream>
#include <memory>
#include "Level_map.h"

sf::Vector2i calculatePlayerPosition(unsigned int width,
                                     unsigned int height,
                                     int leftX,
                                     int rightX,
                                     int upY,
                                     int downY,
                                     int playerCurrentX,
                                     int playerCurrentY) {
  int playerX = 0;
  int playerY = 0;

  if (playerCurrentX - width / 2.0 > leftX && playerCurrentX + width / 2.0 < rightX) {
    playerX = playerCurrentX;
  } else {
    if (playerCurrentX - width / 2.0 < leftX) {
      playerX = leftX + width / 2.0;
    } else {
      playerX = rightX - width / 2.0;
    }
  }

  if (playerCurrentY - height / 2.0 > upY && playerCurrentY + height / 2.0 < downY) {
    playerY = playerCurrentY;
  } else {
    if (playerCurrentY - height / 2.0 < upY) {
      playerY = upY + height / 2.0;
    } else {
      playerY = downY - height / 2.0;
    }
  }

  return {playerX, playerY};
}

void setPrice(std::vector<int> arm_vctr, InterfaceLabel &lbl, int id) {
  std::ostringstream str;
  if (arm_vctr[id] * 100 + 100 >= 500) {
    str << "max";
  } else {
    str << arm_vctr[id] * 100 + 100;
  }
  lbl.SetText(str.str());
}

void setArmLvl(std::vector<int> arm_vctr, InterfaceLabel &lbl, int id) {
  std::ostringstream str;
  str << "LVL:" << arm_vctr[id];
  lbl.SetText(str.str());
}

void buy(std::vector<int> arm_vector, int index) {
  ++arm_vector[index];
  Save::SaveArmor(arm_vector);
}

Interface &Interface::GetInstance(sf::RenderWindow &window) {
  static Interface instance(window);
  return instance;
}

Interface::Interface(sf::RenderWindow &window)
    : height(window.getSize().y),
      width(window.getSize().x),
      buttonSize(window.getSize().y / 25),
      textSize(window.getSize().y / 30),
      headSize(window.getSize().y / 20),
      buttonFontPath(FILES_PATH"files/fonts/Inconsolata-Bold.ttf"),
      textFontPath(FILES_PATH"files/fonts/Inconsolata-Bold.ttf") {
  if (width > 2500 && height > 1600) {
    gameWidth = 2500;
    gameHeight = 1600;
  } else {
    gameWidth = width;
    gameHeight = height;
  }
}

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window) {
  float left = buttonSize * 2;
  float up = buttonSize * 0.6;
  float dy = buttonSize * 1.4;
  InterfaceButton newGameButton(buttonFontPath, buttonSize, left, up, "New Game");
  up += dy;
  InterfaceButton loadGameButton(buttonFontPath, buttonSize, left, up, "Load Game");
  up += dy;
  InterfaceButton statisticButton(buttonFontPath, buttonSize, left, up, "Statistic");
  up += dy;
  InterfaceButton shopButton(buttonFontPath, buttonSize, left, up, "Shop");
  up += dy;
  InterfaceButton exitButton(buttonFontPath, buttonSize, left, up, "Exit");

  InterfaceButton aboutButton(buttonFontPath, buttonSize, left, height - left, "About");

  InterfaceImage backImageSprite(FILES_PATH"files/menu/back_image.png");
  backImageSprite.SetPosition(statisticButton.GetTextRectSize().x + left + 30, 0);
  backImageSprite.Size(width - backImageSprite.GetTextureRect().left, height);

  music.PlayBackgroundMenuMusic();

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

    if (newGameButton.IsSelect(mousePosition, music)) {
      if (!Save::IsExistLvlFile()) {
        music.StopBackgroundMenuMusic();
        startNewGame(window);
      } else {
        newGameWarningMenu(window);
      }
    }

    if (loadGameButton.IsSelect(mousePosition, music)) {
      if (Save::IsExistLvlFile()) {
        if (Save::LoadLvl() != 0) {
          music.StopBackgroundMenuMusic();
          startNewGame(window);
        } else {
          winMenu(window, true);
        }
      }
    }

    if (statisticButton.IsSelect(mousePosition, music)) {
      music.PlayOnButtonSound();
      statisticMenu(window);
    }

    if (shopButton.IsSelect(mousePosition, music)) {
      shopMenu(window);
    }

    if (exitButton.IsSelect(mousePosition, music)) {
      window.close();
    }

    if (aboutButton.IsSelect(mousePosition, music)) {
      aboutMenu(window);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::G)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
      configMenu(window);
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

  InterfaceTable penaltyTable;
  penaltyTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "You were caught and fined"));
  penaltyTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Continue"));

  penaltyTable.CalculateTablePosition();
  penaltyTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (penaltyTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
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

  InterfaceTable diedTable;
  diedTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                            headSize,
                                                            "You were caught and brought back"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Continue"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (diedTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }
}

// Предупреждение о сбросе данных
void Interface::newGameWarningMenu(sf::RenderWindow &window) {
  InterfaceTable newGameWarningTable;
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "Are you sure you want to start a new game?"));
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "All your saves will be lost"));
  newGameWarningTable.SetLeftButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Yes"));
  newGameWarningTable.SetRightButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "No"));

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

    if (newGameWarningTable.GetLeftButtons()[0]->IsSelect(mousePosition, music)) {
      Save::RemoveGameSaves();
      music.StopBackgroundMenuMusic();
      startNewGame(window);
      break;
    }

    if (newGameWarningTable.GetRightButtons()[0]->IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    newGameWarningTable.Draw(window);
    window.display();
  }
}

// Старт новой игры
int Interface::startNewGame(sf::RenderWindow &window) {
  bool repeat = true;

  Save save;

  while (repeat) {
    sf::View menuView(sf::FloatRect(0, 0, width, height));
    sf::View gameView(sf::FloatRect(0, 0, gameWidth, gameHeight));

    music.PlayBackgroundGameMusic();

    Level lvl;
    lvl.LoadFromFile(save.GetLvlName());

    int leftX = lvl.GetObject("left").rect.left;
    int rightX = lvl.GetObject("right").rect.left + lvl.GetObject("right").rect.width;
    int upY = lvl.GetObject("top").rect.top;
    int downY = lvl.GetObject("bottom").rect.top + lvl.GetObject("bottom").rect.height;

    GameManager
        game(lvl, textSize, music, Save::LoadArmors(), Save::LoadPoints(), Save::LoadStat(), Save::LoadConfig());
    sf::Clock clock;

    while (window.isOpen()) {
      sf::Event event{};
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          repeat = false;
          window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Space) {
            game.Fire();
          }

          if (event.key.code == sf::Keyboard::E) {
            game.TakeTransport();
          }

          if (event.key.code == sf::Keyboard::Escape) {
            music.StopBackgroundGameMusic();

            window.setView(menuView);

            if (!gameMenu(window, game.GetPlayer()->GetMainData())) {
              repeat = false;
              return 0;
            }

            music.PlayBackgroundGameMusic();
          }
        }
      }

      if (game.GetPlayer()->GetHp() <= 0) {
        music.StopBackgroundGameMusic();
        music.StopAllMusic();
        music.PlayDiedPlayerSound();

        window.setView(menuView);

        repeat = diedMenu(window);
        break;
      }

      if (game.GetPlayer()->GetFinish()) {
        music.StopBackgroundGameMusic();

        window.setView(menuView);

        if (save.GetLvl() == MAX_LVL) {
          save.SetEndGame();
          repeat = winMenu(window, false);

        } else {
          save.ChangeLvl();
          repeat = nextLvlMenu(window);
        }

        save.SaveGame(game.GetPlayer()->GetPoints());
        break;
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

      float time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      time = time / 400;
      if (time > 70) {
        time = 70;
      }

      game.Update(time);
      auto playerPosition = calculatePlayerPosition(gameWidth, gameHeight,
                                                    leftX, rightX, upY, downY,
                                                    game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);

      window.clear(sf::Color(0, 0, 0));
      lvl.Draw(window, gameHeight, gameWidth, playerPosition.x, playerPosition.y);
      game.Draw(window, playerPosition.x, playerPosition.y, gameHeight, gameWidth);
      gameView.setCenter(playerPosition.x, playerPosition.y);
      window.setView(gameView);
      window.display();
    }

    Save::SaveStat(game.GetStat());
  }
}

// Предупреждение о сбросе данных
bool Interface::endGameWarningMenu(sf::RenderWindow &window) {
  InterfaceTable endGameWarningTable;
  endGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "Are you sure you want to end game?"));
  endGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "All your progress will be lost"));
  endGameWarningTable.SetLeftButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Yes"));
  endGameWarningTable.SetRightButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "No"));

  endGameWarningTable.CalculateTablePosition();
  endGameWarningTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (endGameWarningTable.GetLeftButtons()[0]->IsSelect(mousePosition, music)) {
      return false;
    }

    if (endGameWarningTable.GetRightButtons()[0]->IsSelect(mousePosition, music)) {
      return true;
    }

    window.clear(sf::Color(68, 101, 219));
    endGameWarningTable.Draw(window);
    window.display();
  }
}

bool Interface::winMenu(sf::RenderWindow &window, bool isLoadFromMenu) {
  if (!isLoadFromMenu) {
    music.PlayBackgroundMenuMusic();
  }

  InterfaceTable winTable;
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Congratulations!"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                           textSize,
                                                           "You have collected all the vaccines and were able to"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                           textSize,
                                                           "save the world from the fucking coronavirus"));
  winTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  winTable.CalculateTablePosition();
  winTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (winTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      if (!isLoadFromMenu) {
        music.StopBackgroundMenuMusic();
      }

      return false;;
    }

    window.clear(sf::Color(68, 101, 219));
    winTable.Draw(window);
    window.display();
  }

  return false;
}

bool Interface::nextLvlMenu(sf::RenderWindow &window) {
  music.PlayBackgroundMenuMusic();

  InterfaceTable nextMissionTable;
  nextMissionTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Mission completed"));
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Next mission"));
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  nextMissionTable.CalculateTablePosition();
  nextMissionTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (nextMissionTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    if (nextMissionTable.GetCenterButtons()[1]->IsSelect(mousePosition, music)) {
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    nextMissionTable.Draw(window);
    window.display();
  }

  return false;
}

// Экран смерти
bool Interface::diedMenu(sf::RenderWindow &window) {
  music.PlayBackgroundMenuMusic();

  InterfaceTable diedTable;
  diedTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Mission failed"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Restart"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (diedTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    if (diedTable.GetCenterButtons()[1]->IsSelect(mousePosition, music)) {
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }

  return false;
}

void Interface::statisticMenu(sf::RenderWindow &window) {
  InterfaceLabel statisticHeadText(textFontPath, headSize, "Statistic menu");
  statisticHeadText.SetPosition((width - statisticHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable statisticTable;
  std::vector<int> stat = Save::LoadStat();

  std::ostringstream ssPatient;
  ssPatient << "Patients saved: " << stat[0];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPatient.str()));

  std::ostringstream ssDied;
  ssDied << "Hippocrates died: " << stat[1];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDied.str()));

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine collected: " << stat[2];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVaccine.str()));

  std::ostringstream ssAntigen;
  ssAntigen << "Antigen collected: " << stat[3];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAntigen.str()));

  std::ostringstream ssPolice;
  ssPolice << "Police cured: " << stat[4];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPolice.str()));

  std::ostringstream ssBreaker;
  ssBreaker << "Breaker cured: " << stat[5];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreaker.str()));

  std::ostringstream ssDelivery;
  ssDelivery << "Delivery cured: " << stat[6];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDelivery.str()));

  std::ostringstream ssVirus;
  ssVirus << "Virus cured: " << stat[7];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirus.str()));

  std::ostringstream ssAuto;
  ssAuto << "Ambulance trips: " << stat[8];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAuto.str()));

  std::ostringstream ssMonorail;
  ssMonorail << "Monorail trips: " << stat[9];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMonorail.str()));

  std::ostringstream ssBus;
  ssBus << "Bus trips: " << stat[10];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBus.str()));

  std::ostringstream ssMetro;
  ssMetro << "Metro trips: " << stat[11];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMetro.str()));

  std::ostringstream ssPenalty;
  ssPenalty << "Penalty time: " << stat[12];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPenalty.str()));

  std::ostringstream ssCaught;
  ssCaught << "Back time: " << stat[13];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCaught.str()));

  statisticTable.CalculateTablePosition();
  statisticTable.SetPosition(height, width);

  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    statisticHeadText.Draw(window);
    statisticTable.Draw(window);
    backButton.Draw(window);
    window.display();
  }
}

void Interface::configMenu(sf::RenderWindow &window) {
  InterfaceLabel configurationHeadText(textFontPath, headSize, "Configuration menu");
  configurationHeadText.SetPosition((width - configurationHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable configurationTable;
  int lvl = Save::LoadLvl();
  int points = Save::LoadPoints();
  std::vector<int> armors = Save::LoadArmors();
  std::vector<float> config = Save::LoadConfig();

  std::ostringstream ssCurrentLvl;
  ssCurrentLvl << "Current lvl: " << lvl;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCurrentLvl.str()));

  std::ostringstream ssPlayerHp;
  ssPlayerHp << "Player hp: " << config[0];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPlayerHp.str()));

  std::ostringstream ssCurrentPoints;
  ssCurrentPoints << "Current points: " << points;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCurrentPoints.str()));

  std::ostringstream ssAntigenPoints;
  ssAntigenPoints << "Antigen Points: " << config[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAntigenPoints.str()));

  std::ostringstream ssCapLvl;
  ssCapLvl << "Cap lvl: " << armors[0];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCapLvl.str()));

  std::ostringstream ssShoesLvl;
  ssShoesLvl << "Shoes lvl: " << armors[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssShoesLvl.str()));

  std::ostringstream ssRobeLvl;
  ssRobeLvl << "Robe lvl: " << armors[2];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssRobeLvl.str()));

  std::ostringstream ssPoliceHp;
  ssPoliceHp << "Police hp: " << config[2];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPoliceHp.str()));

  std::ostringstream ssPoliceDmg;
  ssPoliceDmg << "Police dmg: " << config[3];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPoliceDmg.str()));

  std::ostringstream ssPolicePenalty;
  ssPolicePenalty << "Police penalty: " << config[4];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPolicePenalty.str()));

  std::ostringstream ssBreakerHp;
  ssBreakerHp << "Breaker hp: " << config[5];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreakerHp.str()));

  std::ostringstream ssBreakerDmg;
  ssBreakerDmg << "Breaker dmg: " << config[6];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreakerDmg.str()));

  std::ostringstream ssDeliveryHp;
  ssDeliveryHp << "Delivery hp: " << config[7];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDeliveryHp.str()));

  std::ostringstream ssDeliveryDmg;
  ssDeliveryDmg << "Delivery dmg: " << config[8];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDeliveryDmg.str()));

  std::ostringstream ssVirusHp;
  ssVirusHp << "Virus hp: " << config[9];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirusHp.str()));

  std::ostringstream ssVirusDmg;
  ssVirusDmg << "Virus dmg: " << config[10];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirusDmg.str()));

  std::ostringstream ssAutoFuel;
  ssAutoFuel << "Ambulance fuel: " << config[11];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAutoFuel.str()));

  std::ostringstream ssMonorailFuel;
  ssMonorailFuel << "Monorail fuel: " << config[12];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMonorailFuel.str()));

  std::ostringstream ssBusDmg;
  ssBusDmg << "Bus dmg: " << config[13];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBusDmg.str()));

  std::ostringstream ssMetroDmg;
  ssMetroDmg << "Metro dmg: " << config[14];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMetroDmg.str()));

  configurationTable.CalculateTablePosition();
  configurationTable.SetPosition(height, width);

  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");
  InterfaceButton defaultButton(buttonFontPath, buttonSize, "Default");
  defaultButton.SetPosition(width - defaultButton.GetTextRectSize().x - 30, height - buttonSize - 30);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    if (defaultButton.IsSelect(mousePosition, music)) {
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

bool Interface::shopMenu(sf::RenderWindow &window) {
  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  InterfaceImage armorListSprite(FILES_PATH"files/menu/armor_list.png",
                                 width / 2 - (width / 1.6) / 2, height / 2 - (width / 1.9) / 2,
                                 width / 1.6, width / 1.9);

  InterfaceImage armorShoesSprite(FILES_PATH"files/menu/armors.png",
                                  width / 1.57, height / 14,
                                  width / 1.0, width / 1.7);

  InterfaceImage armorCapSprite(FILES_PATH"files/menu/armors.png",
                                width / 4.9, height / 6,
                                width / 1.3, width / 2);

  InterfaceImage armorRobeSprite(FILES_PATH"files/menu/armors.png",
                                 width / 2.32, height / 1.45,
                                 width / 1.3, width / 2.2);

  InterfaceImage buyShoesSprite(FILES_PATH"files/menu/upgrade.png",
                                width / 1.215, height / 7,
                                width / 15, width / 15);

  InterfaceImage buyCapSprite(FILES_PATH"files/menu/upgrade.png",
                              width / 10, height / 7,
                              width / 15, width / 15);

  InterfaceImage buyRobeSprite(FILES_PATH"files/menu/upgrade.png",
                               width / 1.67, height / 1.4,
                               width / 15, width / 15);

  InterfaceLabel lvlShoesText(textFontPath, textSize, width / 1.46, height / 3.5);
  InterfaceLabel lvlCapText(textFontPath, textSize, width / 4.2, height / 3.5);
  InterfaceLabel lvlRobeText(textFontPath, textSize, width / 2.15, height / 1.18);
  InterfaceLabel costShoesText(textFontPath, textSize, width / 1.2, height / 4);
  InterfaceLabel costCapText(textFontPath, textSize, width / 9, height / 4);
  InterfaceLabel costRobeText(textFontPath, textSize, width / 1.64, height / 1.22);

  std::ostringstream ssPoints;
  int money = Save::LoadPoints();
  ssPoints << "Points: " << money;
  InterfaceLabel pointsLabel(textFontPath, textSize, ssPoints.str());
  pointsLabel.SetPosition(width - pointsLabel.GetTextRectSize().x - 30, 13);

  std::vector<int> arm_vector = Save::LoadArmors();
  std::ostringstream ssArm;
  ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
  InterfaceLabel armText(textFontPath, textSize, 30, 13, ssArm.str());

  setArmLvl(arm_vector, lvlCapText, 0);
  setArmLvl(arm_vector, lvlShoesText, 1);
  setArmLvl(arm_vector, lvlRobeText, 2);

  setPrice(arm_vector, costCapText, 0);
  setPrice(arm_vector, costShoesText, 1);
  setPrice(arm_vector, costRobeText, 2);

  armorCapSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));
  armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));
  armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));

  while (window.isOpen()) {
    buyShoesSprite.SetColor(sf::Color::White);
    buyCapSprite.SetColor(sf::Color::White);
    buyRobeSprite.SetColor(sf::Color::White);

    int menuNum = -1;

    if (sf::IntRect(buyCapSprite.GetSpriteRect().x,
                    buyCapSprite.GetSpriteRect().y,
                    buyCapSprite.GetSize().x,
                    buyCapSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyCapSprite.SetColor(sf::Color::Black);
      menuNum = 0;
    }

    if (sf::IntRect(buyShoesSprite.GetSpriteRect().x,
                    buyShoesSprite.GetSpriteRect().y,
                    buyShoesSprite.GetSize().x,
                    buyShoesSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyShoesSprite.SetColor(sf::Color::Black);
      menuNum = 1;
    }
    if (sf::IntRect(buyRobeSprite.GetSpriteRect().x,
                    buyRobeSprite.GetSpriteRect().y,
                    buyRobeSprite.GetSize().x,
                    buyRobeSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyRobeSprite.SetColor(sf::Color::Black);
      menuNum = 2;
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
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
                ssPoints.str("");
                money = Save::LoadPoints();
                ssPoints << "Points: " << money;
                pointsLabel.SetText(ssPoints.str());
                arm_vector = Save::LoadArmors();
                ssArm.str("");
                ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
                armText.SetText(ssArm.str());
                armText.SetPosition(+30, +13);
                setArmLvl(arm_vector, lvlCapText, 0);
                setArmLvl(arm_vector, lvlShoesText, 1);
                setArmLvl(arm_vector, lvlRobeText, 2);
                setPrice(arm_vector, costCapText, 0);
                setPrice(arm_vector, costShoesText, 1);
                setPrice(arm_vector, costRobeText, 2);
                armorCapSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));
                armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));
                armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));
              }
            }
          }
        }
      }
    }

    window.clear(sf::Color(68, 101, 219));

    armorListSprite.Draw(window);
    armorShoesSprite.Draw(window);
    armorCapSprite.Draw(window);
    armorRobeSprite.Draw(window);
    buyShoesSprite.Draw(window);
    buyCapSprite.Draw(window);
    buyRobeSprite.Draw(window);

    backButton.Draw(window);

    pointsLabel.Draw(window);
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

bool Interface::gameMenu(sf::RenderWindow &window, std::vector<int> data) {
  music.PlayBackgroundMenuMusic();

  InterfaceButton continueButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Continue");
  InterfaceButton menuButton(buttonFontPath, buttonSize, "Menu");
  menuButton.SetPosition(width - menuButton.GetTextRectSize().x - 30, height - menuButton.GetTextRectSize().y - 30);

  InterfaceImage armorListImage(FILES_PATH"files/menu/armor_list.png",
                                width / 2 - (width / 1.6) / 2, height / 2 - (width / 1.9) / 2,
                                width / 1.6, width / 1.9);

  InterfaceImage armorCapImage(FILES_PATH"files/menu/armors.png",
                               width / 4.9, height / 6,
                               width / 1.3, width / 2);

  InterfaceImage armorShoesImage(FILES_PATH"files/menu/armors.png",
                                 width / 1.57, height / 14,
                                 width / 1.0, width / 1.7);

  InterfaceImage armorRobeImage(FILES_PATH"files/menu/armors.png",
                                width / 2.32, height / 1.45,
                                width / 1.3, width / 2.2);

  armorShoesImage.SetTextureRect(sf::Rect<int>(204 * data[3], 352, 196, 169));
  armorCapImage.SetTextureRect(sf::Rect<int>(204 * data[4], 41, 196, 85));
  armorRobeImage.SetTextureRect(sf::Rect<int>(204 * data[5], 200, 195, 165));

  std::ostringstream ssData;
  ssData << "HP: " << data[0] << "%" << " ARM: " << data[2] << " Vaccine: " << data[6];
  InterfaceLabel playerDataLabel(textFontPath, textSize, 20, 20, ssData.str());

  std::ostringstream ssPoints;
  ssPoints << "Points: " << data[1];
  InterfaceLabel pointsLabel(textFontPath, textSize, ssPoints.str());
  pointsLabel.SetPosition(width - pointsLabel.GetTextRectSize().x - 20, 20);

  std::ostringstream ssShoes;
  ssShoes << "LVL:" << data[3];
  InterfaceLabel lvlShoesLabel(textFontPath, textSize, width / 1.46, height / 3.5, ssShoes.str());

  std::ostringstream ssCap;
  ssCap << "LVL:" << data[4];
  InterfaceLabel lvlCapLabel(textFontPath, textSize, width / 4.2, height / 3.5, ssCap.str());

  std::ostringstream ssRobe;
  ssRobe << "LVL:" << data[5];
  InterfaceLabel lvlRobeLabel(textFontPath, textSize, width / 2.15, height / 1.18, ssRobe.str());

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          music.StopBackgroundMenuMusic();
          return true;
        }
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (menuButton.IsSelect(mousePosition, music)) {
      return endGameWarningMenu(window);
    }

    if (continueButton.IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    window.clear(sf::Color(68, 101, 219));

    menuButton.Draw(window);
    continueButton.Draw(window);

    armorListImage.Draw(window);
    armorShoesImage.Draw(window);
    armorCapImage.Draw(window);
    armorRobeImage.Draw(window);

    playerDataLabel.Draw(window);
    pointsLabel.Draw(window);
    lvlCapLabel.Draw(window);
    lvlShoesLabel.Draw(window);
    lvlRobeLabel.Draw(window);

    window.display();
  }

  return true;
}

void Interface::aboutMenu(sf::RenderWindow &window) {
  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    backButton.Draw(window);
    window.display();
  }
}
