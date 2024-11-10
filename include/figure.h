#ifndef FIGURE_H
#define FIGURE_H

#include <utility>
#include <stdexcept>
#include <iostream>
#include "concepts.h"
#include "point.h"

template <Number T>
class Figure {
public:
    virtual ~Figure() noexcept = default;

    virtual std::pair<T, T> Center() const = 0;

    virtual explicit operator double() const = 0;

    virtual Figure<T>* Clone() const = 0;

    virtual bool operator==(const Figure<T> &other) const = 0;

    virtual void Print(std::ostream &os) const = 0;

    template <Number U>
    friend std::ostream &operator<<(std::ostream &os, const Figure<U> &figure);
};

template <Number T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
    figure.Print(os);
    return os;
}

#endif //FIGURE_H
