#include <SFML\Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
class Randomizer777
{
private:

    std::random_device rd;
    std::mt19937* engine;
    std::uniform_int_distribution<int>* distx;
    std::uniform_int_distribution<int>* disty;
    sf::Vector2f res;
public:
    Randomizer777(sf::VideoMode mode);

    sf::Vector2f get_random_vector2f();
    Randomizer777(const Randomizer777&);
    ~Randomizer777();
};

sf::Vector2f Randomizer777::get_random_vector2f() {

    sf::Vector2f vector;

    vector.x = (*distx)(*engine) / static_cast<float>(res.x);
    vector.y = 1.0f - (*disty)(*engine) / static_cast<float>(res.y);


    return vector;
}

Randomizer777::Randomizer777(const Randomizer777&) {


}

Randomizer777::Randomizer777(sf::VideoMode mode)
{
    res.x = mode.size.x;
    res.y = mode.size.y;
    engine = new std::mt19937(rd());
    distx = new std::uniform_int_distribution<int>(0, mode.size.x);
    disty = new std::uniform_int_distribution<int>(0, mode.size.y);
}

Randomizer777::~Randomizer777()
{
    delete distx;
    delete disty;
}
