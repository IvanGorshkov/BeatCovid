//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"

const int H = 17;
const int W = 150;
float offsetX=0, offsetY=0;

std::string TileMap[H] = {
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "PPP                                                                                                                                                  0",
    "PPP                                                                                  w                                                               0",
    "PPP                 w                                  w                   w                                                                         0",
    "PPP                                    w                                       kk                                                                    0",
    "PPP                                                                           k  k    k    k                                                         0",
    "PPP                    c                   PPPPPPPP                           k      kkk  kkk  w                                                     0",
    "PPP                                                                     r     k       k    k                                                         0",
    "PPP                                                                    rr     k  k                                                                   0",
    "PPP                            PPPPPPPP                               rrr      kk                                                                    0",
    "PP              c    PPkck                                           rrrr                                                                            0",
    "P            PP                        t0                           rrrrr                                                                            0",
    "P                 P                    00              t0          rrrrrrPPP         G                                                               0",
    "P          P     g      PPPPPPPP            00              00         rrrrrrr                                                                       0",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 200), "Beat COVID-19");

  sf::Texture tileSet;
  tileSet.loadFromFile("/Users/ivangorshkov/beatcovid/tileset.png");
  Player Mario(tileSet);

  sf::Clock clock;
  while (window.isOpen()) {
    window.clear(sf::Color(107,140,255));
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();

    time = time/500;

    if (time > 20) {
      time = 20;
    }

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      Mario.move(-0.1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      Mario.move(0.1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      Mario.jump();
    }

    Mario.status(offsetX, offsetY, time, TileMap);
    if (Mario.getRect().left > 200) {
      offsetX = Mario.getRect().left - 200;
    }

    if (Mario.getRect().top > 150) {
      offsetY = Mario.getRect().top - 150;
    }


    for (int i=0; i<H; i++){
      for (int j=0; j<W; j++)
      {
        sf::RectangleShape rectangle;

        if (TileMap[i][j]=='P')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='k')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='c')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='t')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='g')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='G')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='d')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='w')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='r')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]=='0')  rectangle.setSize(sf::Vector2f(16, 16));

        if (TileMap[i][j]==' ') continue;

        rectangle.setPosition(j*16-offsetX,i*16 - offsetY) ;
        window.draw(rectangle);
      }
    }
    window.draw(Mario.getSprite());
    window.display();
  }

  return 0;
}