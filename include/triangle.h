#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include "point.h"
#include "figure.h"
#include <memory>

template <Number T>
class Triangle : public Figure<T> {
private:
    Point<T> p1;
    Point<T> p2;
    Point<T> p3;

public:
    Triangle();
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3);
    Triangle(const Triangle<T> &other);
    Triangle(Triangle<T> &&other) noexcept;
    Triangle& operator= (const Triangle<T> &other);
    Triangle& operator= (Triangle<T> &&other) noexcept;

    std::pair<T, T> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure<T> &other) const override;

    void Print(std::ostream &os) const override;

    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream &operator>>(std::istream &is, Triangle<U> &r);
};


template <Number T>
Triangle<T>::Triangle() : p1(), p2(), p3() {
}

template <Number T>
Triangle<T>::Triangle(Point<T> p1, Point<T> p2, Point<T> p3)
    : p1(p1), p2(p2), p3(p3) {
}

template <Number T>
Triangle<T>::Triangle(const Triangle<T> &other)
    : p1(other.p1), p2(other.p2), p3(other.p3) {
}

template <Number T>
Triangle<T>::Triangle(Triangle<T> &&other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)), p3(std::move(other.p3)) {
}

template <Number T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T> &other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
    }
    return *this;
}

template <Number T>
Triangle<T>& Triangle<T>::operator=(Triangle<T> &&other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Triangle<T>::Center() const {
    T x = (p1.getX() + p2.getX() + p3.getX()) / static_cast<T>(3);
    T y = (p1.getY() + p2.getY() + p3.getY()) / static_cast<T>(3);
    return std::make_pair(x, y);
}

template <Number T>
Triangle<T>::operator double() const {
    double area = 0.5 * std::fabs(
        static_cast<double>(p1.getX()) * (p2.getY() - p3.getY()) +
        static_cast<double>(p2.getX()) * (p3.getY() - p1.getY()) +
        static_cast<double>(p3.getX()) * (p1.getY() - p2.getY())
    );
    return area;
}

template <Number T>
bool Triangle<T>::operator==(const Figure<T> &other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const Triangle<T>* otherTriangle = dynamic_cast<const Triangle<T>*>(&other);
    if (!otherTriangle) return false;
    return p1 == otherTriangle->p1 && p2 == otherTriangle->p2 && p3 == otherTriangle->p3;
}

template <Number T>
void Triangle<T>::Print(std::ostream &os) const {
    os << "Triangle vertices:\n";
    os << "P1: (" << p1.getX() << ", " << p1.getY() << ")\n";
    os << "P2: (" << p2.getX() << ", " << p2.getY() << ")\n";
    os << "P3: (" << p3.getX() << ", " << p3.getY() << ")\n";
}

template <Number T>
Figure<T>* Triangle<T>::Clone() const {
    return new Triangle<T>(*this);
}

template <Number T>
std::istream &operator>>(std::istream &is, Triangle<T> &r) {
    T x1, y1, x2, y2, x3, y3;
    if (!(is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Triangle<T>(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3));
    return is;
}

template class Triangle<int>;
template class Triangle<float>;
template class Triangle<double>;

template std::istream& operator>> <int>(std::istream&, Triangle<int>&);
template std::istream& operator>> <float>(std::istream&, Triangle<float>&);
template std::istream& operator>> <double>(std::istream&, Triangle<double>&);

#endif