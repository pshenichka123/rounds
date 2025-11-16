#include <SFML\Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
struct Circle
{
    sf::Vector2f position;
    float radius;
    sf::Color color;
};

int main()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Fullscreen", sf::Style::Resize);

    sf::View view(sf::FloatRect(sf::Vector2<float>(0, 0), sf::Vector2<float>(mode.size.x, mode.size.y))); // Логический размер
    view.setViewport(sf::FloatRect(sf::Vector2<float>(0, 0), sf::Vector2<float>(1, 1)));                  // Растянуть на весь экран
    window.setView(view);

    std::vector<Circle> circles;
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distx(0, mode.size.x);
    std::uniform_int_distribution<int> disty(0, mode.size.y);
    clock_t last_time_added = clock();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Добавляем новую точку каждые 500 мс
        if (clock() - last_time_added > 500)
        {
            add_point(points, randomizer);
            last_time_added = clock();
        }

        // Ограничиваем количество точек
        if (points.size() > 30)
        {
            points.erase(points.begin()); // Удаляем самую старую точку
        }

        // Обновляем шейдер
        waveShader.setUniform("u_resolution", sf::Vector2f(mode.size.x, mode.size.y));
        waveShader.setUniform("u_points_count", static_cast<int>(points.size()));

        for (int i = 0; i < points.size(); i++)
        {
            std::string uniform_name = "u_points[" + std::to_string(i) + "]";
            waveShader.setUniform(uniform_name,
                                  sf::Vector2f(
                                      points[i].getx(),
                                      points[i].gety()));
        }

        waveShader.setUniform("u_time", Clock.getElapsedTime().asSeconds());

        // Отрисовка
        window.clear();
        window.draw(rect, &waveShader);
        window.display();

        // Удаляем точки старше 3 секунд
        points.erase(
            std::remove_if(points.begin(), points.end(),
                           [](const Point &c)
                           { return clock() - c.getCreationTime() > 3000; }),
            points.end());
    }

    return 0;
}