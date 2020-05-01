//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "AnimationManager.h"
#include "Level_map.h"
//#include "BulletManager.h"
#include "GameManager.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19");
  sf::View view(sf::FloatRect(0, 0, 1280, 800));

  //  BulletManager bulletmanager;
  Level lvl;
  lvl.LoadFromFile("../test_map.tmx");
  GameManager game(lvl);
  sf::Clock clock;
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

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game.Fire();
      }
    }

    //  bulletmanager.update(time);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      game.GetPlayer()->setKey("L", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      game.GetPlayer()->setKey("R", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      game.GetPlayer()->setKey("UP", true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      game.GetPlayer()->setKey("DOWN", true);
    }


    // Mario.status(time);
    game.Update(time);

    lvl.Draw(window);
    game.Draw(window);
    sf::RectangleShape hp;
    hp.setSize(sf::Vector2f(100 * (game.GetPlayer()->getHp() / 100), 20));
    hp.setFillColor(sf::Color::Green);
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();
    hp.setPosition(center.x - size.x / 2 + 11, center.y - size.y / 2 + 13);
    window.draw(hp);
    sf::RectangleShape arm;
    arm.setSize(sf::Vector2f(100 * (game.GetPlayer()->getArm() / 60), 20));
    arm.setFillColor(sf::Color::Blue);
    arm.setPosition(140, 10);
    arm.setPosition(center.x - size.x / 2 + 150, center.y - size.y / 2 + 13);
    window.draw(arm);


    view.setCenter(game.GetPlayer()->getRect().left, game.GetPlayer()->getRect().top);
    window.setView(view);
    //

    window.display();
  }

  return 0;
}
