#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "MainMenu.hpp"
#include "Button.hpp"
#include "CesticeSimulacija.hpp"
#include "Solver.hpp"

enum class AppState{MAIN_MENU, CESTICE, SHOWCASE2, SHOWCASE3};

static sf::Color getColorFromFloat(float t)
{
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * M_PI);
    const float b = sin(t + 0.66f * 2.0f * M_PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

int main()
{
    freopen("colors.txt", "r", stdin);
    //freopen("positions.txt", "w", stdout);

    AppState currentState = AppState::MAIN_MENU;
    constexpr int WINDOW_WIDTH = 840;
    constexpr int WINDOW_HEIGHT = 840;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}, 32),"Main Menu", sf::Style::Default, sf::State::Windowed, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    sf::Font Arial;
    if (!Arial.openFromFile("arial/ARIAL.TTF"))
    {
        std::cerr << "Couldn't load font\n";
        return -1;
    }

    const float radius = 5.0f;
    const int max_objects = 8000;
    const sf::Vector2f spawn_position = {10.0f, 10.0f};
    const float spawn_velocity = 1000.0f;
    const float spawn_delay = 0.005f;
    const float max_angle = M_PI * 0.5f;

    const int max_spawner = 24;  
    int num_spawner = 24;
    int spawned_count = 0;


    Solver solver;
    //solver.setBoundary({WINDOW_WIDTH/2, WINDOW_HEIGHT/2}, (WINDOW_WIDTH - 850.0f) / 2);

    sf::Clock respawnClock, timer, fpsTimer;
    bool done = false;
    int r, g, b;

    MainMenu mainMenu(&window, Arial);
    CesticeSimulacija cesticeShowcase(&window, Arial, solver);

    sf::Text broj(Arial, "", 30U);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();

            switch(currentState)
            {
                case AppState::MAIN_MENU:
                {
                    int res = mainMenu.handleInput(window, *event);
                    currentState = static_cast<AppState>(res);
                    break;
                }
                
                case AppState::CESTICE:
                {
                    cesticeShowcase.handleInput(window, *event);
                    break;
                }

                default:
                    break;
            }
        }

        
        window.clear(sf::Color::Black);

        switch(currentState)
        {
            case AppState::MAIN_MENU:
            {
                mainMenu.update(sf::Time::Zero);
                mainMenu.render(window);
                break;
            }

            case AppState::CESTICE:
            {
                /*
                float time = timer.getElapsedTime().asSeconds();
                int num_objects = solver.getObjects().size();
                if (num_objects < max_objects)
                {
                    sf::Color currentColor = getColorFromFloat(time);
                    spawned_count++;
                    for (int i = 0; i < std::min(num_spawner, max_objects - num_objects); i++)
                    {
                        auto& new_object = solver.addObject(spawn_position + sf::Vector2f{0.0f, i * 8.0f}, radius);
                        //std::cin >> r >> g >> b;
                        //new_object.color = {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
                        new_object.setColor(currentColor);
                        solver.setObjectVelocity(new_object, spawn_velocity * sf::Vector2f{0.8, 0.6});
                    }
                    if (spawned_count / 50 >= num_spawner && num_spawner < max_spawner) num_spawner++;
                }*/

                float t = timer.getElapsedTime().asSeconds();
                // if(t > 200 && !done)
                // {
                //     done = true;
                //     for(Cestica& obj : solver.getObjects())
                //     {
                //         std::cout << obj.getPosition().x << ' ' << obj.getPosition().y << std::endl;
                //     }
                // }
                
                if (solver.getObjects().size() < max_objects && respawnClock.getElapsedTime().asSeconds() >= spawn_delay)
                {
                    int r, g, b;
                    for(int i = 0; i < 2; i++)
                    {
                        auto& object = solver.addObject(spawn_position + sf::Vector2f{0.0f, 20.0f * i}, radius);

                        std::cin >> r >> g >> b;
                        object.setColor({static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)});
                        //object.setColor(getColorFromFloat(t));
                        solver.setObjectVelocity(object, spawn_velocity * sf::Vector2f{0.8f, 0.6f});
                    }
                    //float angle = M_PI * 0.5f + max_angle * sin(3 * t);
                   
                    respawnClock.restart();
                }
                cesticeShowcase.update(sf::Time::Zero);
                cesticeShowcase.render(window);

                //Performans
                float ms = 1.0 * fpsTimer.getElapsedTime().asMicroseconds() / 1000;
                float fps = 1000.0f / ms;

                broj.setString(std::to_string(fps) + "fps, " + std::to_string(solver.getObjects().size()) + " cestica");
                broj.setFillColor(sf::Color::Magenta);
                window.draw(broj);
                fpsTimer.restart();

                break;
            }

            default:
                break;
        }

        window.display();
    }
}