//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "AnimationManager.h"
#include "Level_map.h"
#include "BulletManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 720), "Beat COVID-19");
    sf::View view(sf::FloatRect(0, 0, 960, 720));
    sf::Texture tileSet;
    tileSet.loadFromFile("../fang.png");

    BulletManager bulletmanager;
    sf::Texture bulletTexture;
  AnimationManager animb;
    bulletTexture.loadFromFile("../bullet.png");
    animb.create("move", bulletTexture, 7, 10, 8, 8, 1, 0);
    animb.create("explode", bulletTexture, 27, 7, 18, 18, 4, 0.01, 29);


  AnimationManager anim;
    anim.create("walk", tileSet, 0, 244, 40, 50, 6, 0.005, 40);
    anim.create("stay", tileSet, 0, 187, 42, 52, 3, 0.002, 42);
    anim.create("die", tileSet, 0, 1199, 59, 41, 7, 0.004, 59);
    anim.create("jump", tileSet, 0, 528, 29, 30, 4, 0.0045, 38);
    anim.create("lay", tileSet, 0, 436, 80, 20, 1, 0);

    Level lvl;
    lvl.LoadFromFile("../test_map.tmx");
    Player Mario(anim, lvl);
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
                bulletmanager.add(Mario.getRect().left, Mario.getRect().top, 0.2, 0);
            }
        }

        bulletmanager.update(time, animb);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Mario.setKey("L", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            Mario.setKey("R", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            Mario.setKey("UP", true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            Mario.setKey("DOWN", true);
        }


        Mario.status(time);



      lvl.Draw(window);
      if (Mario.takeDamge(0.005) > 0) {
        sf::RectangleShape hp;
        hp.setSize(sf::Vector2f(100 * (Mario.getHp() / 100), 20));
        hp.setFillColor(sf::Color::Green);
        sf::Vector2f center = window.getView().getCenter();
        sf::Vector2f size = window.getView().getSize();
        hp.setPosition( center.x - size.x/2 + 11, center.y - size.y/2 + 13);
        window.draw(hp);
        sf::RectangleShape arm;
        arm.setSize(sf::Vector2f(100 * (Mario.getArm() / 60), 20));
        arm.setFillColor(sf::Color::Blue);
        arm.setPosition(140, 10);
        arm.setPosition( center.x - size.x/2 + 150, center.y - size.y/2 + 13);
        window.draw(arm);

      }

 
      view.setCenter(Mario.getRect().left, Mario.getRect().top);
      window.setView(view);
      bulletmanager.draw(window, animb);
      Mario.draw(window);
      window.display();
    }

    return 0;
}
