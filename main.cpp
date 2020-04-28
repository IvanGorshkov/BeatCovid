
#include <SFML/Graphics.hpp>
#include "Level_map.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(480, 480), "SFML works!");
    Texture t;
    t.loadFromFile("ivan.png");
    Sprite s;
    s.setTexture(t);
    s.setTextureRect(IntRect(0, 0, 64, 147));

    Level lvl;
    lvl.LoadFromFile("test_map.tmx");

    Object pl = lvl.GetObject("player");
    s.setPosition(pl.rect.left, (pl.rect.top - 147));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        lvl.Draw(window);
        window.draw(s);
        window.display();
    }

    return 0;
}

