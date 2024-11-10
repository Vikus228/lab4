#ifndef OCTAGON_H
#define OCTAGON_H

#include <iostream>
#include <cmath>
#include <array>
#include "figure.h"
#include "point.h"
#include "concepts.h"

template <Number T>
class Octagon : public Figure<T> {
private:
    std::array<Point<T>, 8> points;

public:
    Octagon();
    Octagon(const std::array<Point<T>, 8>& pts);
    Octagon(const Octagon<T>& other);
    Octagon(Octagon<T>&& other) noexcept;

    Octagon<T>& operator=(const Octagon<T>& other);
    Octagon<T>& operator=(Octagon<T>&& other) noexcept;

    std::pair<T, T> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure<T>& other) const override;

    void Print(std::ostream& os) const override;

    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream& operator>>(std::istream& is, Octagon<U>& o);
};

#include "octagon.h"

template <Number T>
Octagon<T>::Octagon() : points{} {
}

template <Number T>
Octagon<T>::Octagon(const std::array<Point<T>, 8>& pts) : points(pts) {
}

template <Number T>
Octagon<T>::Octagon(const Octagon<T>& other) : points(other.points) {
}

template <Number T>
Octagon<T>::Octagon(Octagon<T>&& other) noexcept : points(std::move(other.points)) {
}

template <Number T>
Octagon<T>& Octagon<T>::operator=(const Octagon<T>& other) {
    if (this != &other) {
        points = other.points;
    }
    return *this;
}

template <Number T>
Octagon<T>& Octagon<T>::operator=(Octagon<T>&& other) noexcept {
    if (this != &other) {
        points = std::move(other.points);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Octagon<T>::Center() const {
    T x = 0, y = 0;
    for (const auto& point : points) {
        x += point.getX();
        y += point.getY();
    }
    x /= static_cast<T>(8);
    y /= static_cast<T>(8);
    return std::make_pair(x, y);
}

template <Number T>
Octagon<T>::operator double() const {
    double area = 0.0;
    for (int i = 0; i < 8; ++i) {
        const Point<T>& current = points[i];
        const Point<T>& next = points[(i + 1) % 8];
        area += (static_cast<double>(current.getX()) * next.getY()) - (next.getX() * current.getY());
    }
    area = std::fabs(area) / 2.0;
    return area;
}

template <Number T>
bool Octagon<T>::operator==(const Figure<T>& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const Octagon<T>* otherOct = dynamic_cast<const Octagon<T>*>(&other);
    if (!otherOct) return false;
    return points == otherOct->points;
}

template <Number T>
void Octagon<T>::Print(std::ostream& os) const {
    os << "Octagon vertices:\n";
    for (size_t i = 0; i < points.size(); ++i) {
        os << "P" << i + 1 << ": (" << points[i].getX() << ", " << points[i].getY() << ")\n";
    }
}

template <Number T>
Figure<T>* Octagon<T>::Clone() const {
    return new Octagon<T>(*this);
}

template <Number T>
std::istream& operator>>(std::istream& is, Octagon<T>& o) {
    std::array<Point<T>, 8> pts;
    for (auto& point : pts) {
        T x, y;
        if (!(is >> x >> y)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        point = Point<T>(x, y);
    }
    o = Octagon<T>(pts);
    return is;
}

// Explicit instantiation for common numerical types
template class Octagon<int>;
template class Octagon<float>;
template class Octagon<double>;

template std::istream& operator>> <int>(std::istream&, Octagon<int>&);
template std::istream& operator>> <float>(std::istream&, Octagon<float>&);
template std::istream& operator>> <double>(std::istream&, Octagon<double>&);


#endif // OCTAGON_H
