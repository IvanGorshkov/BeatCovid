
#include "Interface.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19");
    Interface interface;
    interface.MainMenu(window);
    return 0;
}
