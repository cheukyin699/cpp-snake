#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "snake.h"

using namespace sf;

const double FPS = 30;
const unsigned Width = 100;
const unsigned Height = 100;
const unsigned Tile_Width = 7;
const unsigned Tile_Height = 7;

Pt randomPt() {
    return Pt(rand() % Width, rand() % Height);
}

/* Board is 100x100 in dimensions (grid)
 * Split everything down by 7
 */
int main() {
    RenderWindow w(VideoMode(Width * Tile_Width, Height * Tile_Height),
                   "Snake", Style::Close);
    Event evt;
    Snake s(Direction::Down, Pt(0, 0));
    RectangleShape r(Vector2f(Tile_Width, Tile_Height));
    Pt food = randomPt();

    w.setFramerateLimit(FPS);

    while (w.isOpen()) {
        while (w.pollEvent(evt)) {
            switch (evt.type) {
            case Event::Closed:
                w.close();
                break;
            case Event::KeyPressed:
                switch (evt.key.code) {
                case Keyboard::W:
                case Keyboard::Up:
                    // Move up if possible
                    s.setDirection(Direction::Up);
                    break;
                case Keyboard::S:
                case Keyboard::Down:
                    // Move down if possible
                    s.setDirection(Direction::Down);
                    break;
                case Keyboard::A:
                case Keyboard::Left:
                    // Move left if possible
                    s.setDirection(Direction::Left);
                    break;
                case Keyboard::D:
                case Keyboard::Right:
                    // Move right if possible
                    s.setDirection(Direction::Right);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        // Food collection
        bool foodCollides = food == s.getHead();
        // Bounds detection
        bool isInBounds = s.inBounds(Width, Height);
        // Self collision detection
        bool selfCollides = false;
        if (s.getParts().size() > 4) {
            for (unsigned i = 4; i < s.getParts().size(); ++i) {
                if (s.getParts()[i] == s.getHead()) {
                    selfCollides = true;
                    break;
                }
            }
        }
        // You can only lose
        bool isLose = !isInBounds || selfCollides;

        if (foodCollides) food = randomPt();

        w.clear(isLose? Color::Red: Color::Black);

        r.setFillColor(Color::White);
        // Draw snake!
        for (auto p : s.getParts()) {
            r.setPosition(p.x * Tile_Width, p.y * Tile_Height);
            w.draw(r);
        }
        // Draw snake food!
        r.setFillColor(Color::Green);
        r.setPosition(food.x * Tile_Width, food.y * Tile_Height);
        w.draw(r);

        w.display();

        if (!isLose)
            s.update(foodCollides);
    }

    return 0;
}
