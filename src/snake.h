#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

using namespace std;

enum Direction {
    Up, Down, Left, Right
};

struct Pt {
    int x;
    int y;

    Pt(): x(0), y(0) {};
    Pt(int x, int y): x(x), y(y) {};
    Pt& operator+(const Pt& p);
    bool operator==(const Pt& p);
};

/* Used for converting the directions into relative coordinates
 */
static vector<Pt> DirectionMask = {
    Pt(0, -1),      // Up
    Pt(0, 1),       // Down
    Pt(-1, 0),      // Left
    Pt(1, 0)        // Right
};

/* The snake class
 * d - direction the head is moving in
 * parts - the different coordinates of the different parts of the snake
 *         first part is head, last part is tail, rest is the rest
 */
class Snake {
    private:
        Direction d;
        vector<Pt> parts;

    public:
        Snake(Direction, Pt);

        /* Sets a new direction for the snake
         * Note that the snake cannot make swift 180deg turns
         */
        void setDirection(Direction n);

        /* Updates the snake in movement
         * Meant to be called every frame
         * eaten - true if snake has eaten; false if otherwise
         */
        void update(bool eaten);

        /* Checks if snake is within bounds
         * w - bound width
         * h - bound height
         */
        bool inBounds(int w, int h);

        /* Gets a vector of snake parts
         */
        vector<Pt> getParts() const {return parts;};

        /* Gets the head of the snake
         */
        Pt getHead() const {return parts.front();};

        /* Gets the current orientation of snake
         */
        Direction getDir() const {return d;};
};

#endif
