#include "Randomizer777.hpp"
#include "Point.hpp"
#include <iostream>
#include <time.h>

//удаление сттарых кругов
// привязка ко времени нормальная




void add_point(std::vector<Point>& points, Randomizer777& randomizer)
{
    sf::Vector2f new_rand_vec = randomizer.get_random_vector2f();
    points.push_back(Point(new_rand_vec, clock()));
}




int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Fullscreen", sf::Style::Resize);
    window.setFramerateLimit(60);


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








    std::vector<Point> points;
    add_point(points, randomizer);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        if (clock() - last_time_added > 10)
        {

            // add_point(points, randomizer);
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
                    points[i].getx(),
                    points[i].gety() // Инверсия Y

                )
            );
            std::cout << points[i].getx() << "  " << points[i].gety() << "   " << points[i].getCreationTime() << "   " << clock() << "\n";
        }
        waveShader.setUniform("u_time", Clock.getElapsedTime().asSeconds());
        std::cout << clock() << "\n";


        window.clear();
        window.draw(rect, &waveShader);
        window.display();
        points.erase(
            std::remove_if(points.begin(), points.end(),
                [](const Point& c) { return clock() - c.getCreationTime() > 5000;}),
            points.end()
        );



    }

    return 0;
}