#ifndef HEXAGON_H
#define HEXAGON_H

#include <iostream>
#include <cmath>
#include "figure.h"
#include "point.h"
#include "concepts.h"
#include <memory>

template <Number T>
class Hexagon : public Figure<T> {
private:
    std::array<Point<T>, 6> points;

public:
    Hexagon();
    Hexagon(const std::array<Point<T>, 6>& pts);
    Hexagon(const Hexagon<T>& other);
    Hexagon(Hexagon<T>&& other) noexcept;

    Hexagon<T>& operator=(const Hexagon<T>& other);
    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept;

    std::pair<T, T> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure<T>& other) const override;

    void Print(std::ostream& os) const override;

    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream& operator>>(std::istream& is, Hexagon<U>& h);
};

template <Number T>
Hexagon<T>::Hexagon() : points{} {
}

template <Number T>
Hexagon<T>::Hexagon(const std::array<Point<T>, 6>& pts) : points(pts) {
}

template <Number T>
Hexagon<T>::Hexagon(const Hexagon<T>& other) : points(other.points) {
}

template <Number T>
Hexagon<T>::Hexagon(Hexagon<T>&& other) noexcept : points(std::move(other.points)) {
}

template <Number T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon<T>& other) {
    if (this != &other) {
        points = other.points;
    }
    return *this;
}

template <Number T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon<T>&& other) noexcept {
    if (this != &other) {
        points = std::move(other.points);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Hexagon<T>::Center() const {
    T x = 0, y = 0;
    for (const auto& point : points) {
        x += point.getX();
        y += point.getY();
    }
    x /= static_cast<T>(6);
    y /= static_cast<T>(6);
    return std::make_pair(x, y);
}

template <Number T>
Hexagon<T>::operator double() const {
    double area = 0.0;
    for (int i = 0; i < 6; ++i) {
        const Point<T>& current = points[i];
        const Point<T>& next = points[(i + 1) % 6];
        area += (static_cast<double>(current.getX()) * next.getY()) - (next.getX() * current.getY());
    }
    area = std::fabs(area) / 2.0;
    return area;
}

template <Number T>
bool Hexagon<T>::operator==(const Figure<T>& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const Hexagon<T>* otherHex = dynamic_cast<const Hexagon<T>*>(&other);
    if (!otherHex) return false;
    return points == otherHex->points;
}

template <Number T>
void Hexagon<T>::Print(std::ostream& os) const {
    os << "Hexagon vertices:\n";
    for (size_t i = 0; i < points.size(); ++i) {
        os << "P" << i + 1 << ": (" << points[i].getX() << ", " << points[i].getY() << ")\n";
    }
}

template <Number T>
Figure<T>* Hexagon<T>::Clone() const {
    return new Hexagon<T>(*this);
}

template <Number T>
std::istream& operator>>(std::istream& is, Hexagon<T>& h) {
    std::array<Point<T>, 6> pts;
    for (auto& point : pts) {
        T x, y;
        if (!(is >> x >> y)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        point = Point<T>(x, y);
    }
    h = Hexagon<T>(pts);
    return is;
}

template class Hexagon<int>;
template class Hexagon<float>;
template class Hexagon<double>;

template std::istream& operator>> <int>(std::istream&, Hexagon<int>&);
template std::istream& operator>> <float>(std::istream&, Hexagon<float>&);
template std::istream& operator>> <double>(std::istream&, Hexagon<double>&);


#endif // HEXAGON_H
