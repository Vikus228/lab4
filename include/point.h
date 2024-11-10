#ifndef POINT_H
#define POINT_H

#include "concepts.h"

template <Number T>
class Point {
private:
    T x;
    T y;
public:
    Point() : x(0), y(0) {}

    Point(T xVal, T yVal) : x(xVal), y(yVal) {}

    T getX() const;
    T getY() const;

    void setX(T xVal);
    void setY(T yVal);

    bool operator==(const Point<T>& other) const;
};

template <Number T>
T Point<T>::getX() const {
    return x;
}

template <Number T>
T Point<T>::getY() const {
    return y;
}

template <Number T>
void Point<T>::setX(T xVal) {
    x = xVal;
}

template <Number T>
void Point<T>::setY(T yVal) {
    y = yVal;
}

template <Number T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x == other.x && y == other.y;
}

#endif // POINT_H
