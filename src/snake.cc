#include "snake.h"

Pt& Pt::operator+(const Pt& p) {
    x += p.x; y += p.y;
    return *this;
}

bool Pt::operator==(const Pt& p) {
    return x == p.x && y == p.y;
}

Snake::Snake(Direction d, Pt p): d(d), parts({p}) {
}

void Snake::setDirection(Direction n) {
    switch (d) {
    case Up:
    case Down:
        if (n == Left || n == Right) d = n;
        break;
    case Left:
    case Right:
        if (n == Up || n == Down) d = n;
        break;
    }
}

void Snake::update(bool eaten) {
    Pt head = parts.front() + DirectionMask[int(d)];
    if (!eaten) parts.pop_back();
    parts.insert(parts.begin(), head);
}

bool Snake::inBounds(int w, int h) {
    return getHead().x >= 0 && getHead().x < w &&
           getHead().y >= 0 && getHead().y < h;
}
