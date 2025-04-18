#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>




//удаление сттарых кругов
// привязка ко времени нормальная

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Fullscreen", sf::Style::Resize);
    window.setFramerateLimit(1);


    sf::Shader waveShader;
    if (!waveShader.loadFromFile("src/wave.vert", "src/wave.frag")) {
        std::cout << "couldnt load";
        return 0;
    }

    sf::RectangleShape rect(sf::Vector2f(mode.size.x, mode.size.y));
    rect.setPosition(sf::Vector2f(0, 0));
    sf::Clock Clock;
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distx(0, mode.size.x);
    std::uniform_int_distribution<int> disty(0, mode.size.y);
    clock_t last_time_added = clock();








    std::vector<sf::Vector2f> points;
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        if (clock() - last_time_added > 10)
        {
            int x_coord = distx(engine);
            int y_coord = disty(engine);
            points.push_back(sf::Vector2f(
                x_coord / static_cast<float>(mode.size.x),
                1.0f - y_coord / static_cast<float>(mode.size.y)
            ));
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