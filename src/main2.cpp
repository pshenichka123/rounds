#include "Randomizer777.hpp"
#include <iostream>


//удаление сттарых кругов
// привязка ко времени нормальная

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Fullscreen", sf::Style::Resize);
    window.setFramerateLimit(12);


    sf::Shader waveShader;
    if (!waveShader.loadFromFile("wave.vert", "wave.frag")) {
        std::cout << "couldnt load";
        return 0;
    }

    sf::RectangleShape rect(sf::Vector2f(mode.size.x, mode.size.y));
    rect.setPosition(sf::Vector2f(0, 0));
    sf::Clock Clock;

    Randomizer777 randomizer = (mode);
    clock_t last_time_added = clock();








    std::vector<sf::Vector2f> points;
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        if (clock() - last_time_added > 10)
        {
            sf::Vector2f new_rand_vec = randomizer.get_random_vector2f();
            points.push_back(new_rand_vec);
            last_time_added = clock();
        }

        if (points.size() > 300)
        {
            std::cout << "to much points";
            return 0;
        }
        // uniform vec2 u_points[500];  // Массив точек (максимум 10)
        // uniform int u_points_count;
        waveShader.setUniform("u_resolution", sf::Vector2f(mode.size.x, mode.size.y));
        //   std::cout << mouse.x / 800.0f << "   " << mouse.y / 600.0f << "\n";
        //  std::cout << mode.size.x << "   " << mode.size.y << "\n";

        std::cout << points.size() << "\n";


        waveShader.setUniform("u_points_count", static_cast<int>(points.size()));
        for (int i = 0; i < points.size(); i++) {
            std::string uniform_name = "u_points[" + std::to_string(i) + "]";
            waveShader.setUniform(uniform_name,
                sf::Vector2f(
                    points[i].x,
                    points[i].y // Инверсия Y

                )
            );
            std::cout << points[i].x << "  " << points[i].y << "\n";
        }
        waveShader.setUniform("u_time", Clock.getElapsedTime().asSeconds());





        window.clear();
        window.draw(rect, &waveShader);
        window.display();
        while (points.size() > 1)
        {
            points.erase(points.begin());
        }



    }

    return 0;
}