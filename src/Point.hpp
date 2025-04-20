#include <SFML/Graphics.hpp>


class Point
{
private:
    sf::Vector2f coords;
    clock_t time_of_creation;

public:
    Point(sf::Vector2f coords, clock_t time);
    ~Point();
    float getx()const;
    float gety() const;
    clock_t getCreationTime() const;
};

float Point::getx()const
{
    return coords.x;
}
float Point::gety()const
{
    return coords.y;
}

clock_t Point::getCreationTime()const
{
    return time_of_creation;
}

Point::Point(sf::Vector2f coords, clock_t time)
{
    this->coords = coords;
    time_of_creation = time;


}

Point::~Point()
{
}
