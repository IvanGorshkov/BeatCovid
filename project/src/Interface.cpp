#include "Interface.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Level_map.h"
#include "GameManager.h"

void Interface::StartGame(sf::RenderWindow *window) {
    window->setVerticalSyncEnabled(true);
    sf::View view(sf::FloatRect(0, 0, 1280, 800));
    Level lvl;
    lvl.LoadFromFile("../files/test_map.tmx");
    GameManager game(lvl);
    sf::Clock clock;
    while (window->isOpen()) {
        window->clear(sf::Color(107, 140, 255));
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 10;

        if (time > 20) {
            time = 20;
        }

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            Interface::Pause();
        }

        game.Update(time);

        lvl.Draw(*window);
        game.Draw(*window);

        view.setCenter(game.GetPlayer()->GetRect().left, game.GetPlayer()->GetRect().top);
        window->setView(view);

        window->display();
    }
}

void Interface::MainMenu() {
    sf::RenderWindow window(sf::VideoMode(1024, 512), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    char windowTitle[255] = "beatCOVID";
    window.setTitle(windowTitle);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Main Menu");
        if (ImGui::Button("New game")) {
            ImGui::SFML::Shutdown();
            Interface::StartGame(&window);
        }
        if (ImGui::Button("Exit")) {
            ImGui::SFML::Shutdown();
            window.close();
        }
        ImGui::End();
        window.clear(bgColor);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}

void Interface::Pause() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = { 0.f, 0.f, 0.f };

    // здесь мы будем использовать массив char. Чтобы использовать
    // std::string нужно сделать действия, описанные во второй части
    char windowTitle[255] = "ImGui + SFML = <3";
    window.setTitle(windowTitle);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Pause");

        if (ImGui::Button("Continue")) {
            window.close();
        }
        if (ImGui::Button("Retry")) {
            ImGui::SFML::Shutdown();
            Interface::StartGame(&window);
        }
        ImGui::End(); // end window

        window.clear(bgColor); // заполняем окно заданным цветом
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
