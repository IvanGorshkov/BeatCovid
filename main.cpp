#include <SFML/Graphics.hpp>
#include "Level_map.h"
#include "GameManager.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19");
  sf::View view(sf::FloatRect(0, 0, 1280, 800));

  Level lvl;
  lvl.LoadFromFile("../files/test_map.tmx");
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

    game.Update(time);

    lvl.Draw(window);
    game.Draw(window);

    view.setCenter(game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);
    window.setView(view);

    window.display();
  }

  return 0;
}
