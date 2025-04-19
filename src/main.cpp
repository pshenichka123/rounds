#include <SFML\Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
struct Circle {
    sf::Vector2f position;
    float radius;
    sf::Color color;
};

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Fullscreen", sf::Style::Resize);

    sf::View view(sf::FloatRect(sf::Vector2<float>(0, 0), sf::Vector2<float>(mode.size.x, mode.size.y)));  // Логический размер
    view.setViewport(sf::FloatRect(sf::Vector2<float>(0, 0), sf::Vector2<float>(1, 1)));    // Растянуть на весь экран
    window.setView(view);

    std::vector<Circle> circles;
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distx(0, mode.size.x);
    std::uniform_int_distribution<int> disty(0, mode.size.y);
    clock_t last_time_added = clock();
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    circles.push_back({
                        sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y),
                        5.0f,
                        sf::Color(0, 100, 255)
                        });
                }
            }
        }
        if (clock() - last_time_added > 100)
        {
            int x_coord = distx(engine);
            int y_coord = disty(engine);
            circles.push_back({
                        sf::Vector2f(x_coord,y_coord),
                        5.0f,
                        sf::Color(0, 100, 255)
                });

        }


        window.clear(sf::Color::Black);

        for (auto& circle : circles) {
            circle.radius += 0.6f;
            circle.color.a = static_cast<std::uint8_t>(circle.color.a * 0.97f); // Плавное затухание

            sf::CircleShape shape(circle.radius, 18);
            shape.setPosition(circle.position - sf::Vector2f(circle.radius, circle.radius));
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(circle.color);
            shape.setOutlineThickness(3.7f);
            window.draw(shape);
        }

        // Удаляем "мертвые" круги
        circles.erase(
            std::remove_if(circles.begin(), circles.end(),
                [](const Circle& c) { return c.color.a < 10; }),
            circles.end()
        );

        window.display();
    }

    return 0;
}