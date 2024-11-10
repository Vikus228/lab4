#ifndef FIGUREARRAY_H
#define FIGUREARRAY_H

#include "figure.h"
#include "concepts.h"
#include <memory>

template <Number T>
class FigureArray {
public:
    FigureArray();
    ~FigureArray();

    void add(std::shared_ptr<Figure<T>> figure);
    void remove(size_t index);
    std::shared_ptr<Figure<T>> operator[](size_t index) const;
    T totalArea() const;
    size_t size() const;

private:
    std::unique_ptr<std::shared_ptr<Figure<T>>[]> array;
    size_t capacity;
    size_t count;

    void resize(size_t newCapacity);
};

template <Number T>
FigureArray<T>::FigureArray() : capacity(2), count(0) {
    array = std::make_unique<std::shared_ptr<Figure<T>>[]>(capacity);
}

template <Number T>
FigureArray<T>::~FigureArray() = default;

template <Number T>
void FigureArray<T>::resize(size_t newCapacity) {
    auto newArray = std::make_unique<std::shared_ptr<Figure<T>>[]>(newCapacity);

    for (size_t i = 0; i < count; ++i) {
        newArray[i] = std::move(array[i]);
    }

    capacity = newCapacity;
    array = std::move(newArray);
}

template <Number T>
void FigureArray<T>::add(std::shared_ptr<Figure<T>> figure) {
    if (count >= capacity) {
        resize(capacity * 2);
    }
    array[count++] = std::move(figure);
}

template <Number T>
std::shared_ptr<Figure<T>> FigureArray<T>::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template <Number T>
T FigureArray<T>::totalArea() const {
    T result = 0;
    for (size_t i = 0; i < count; ++i) {
        if (array[i] != nullptr) {
            result += static_cast<double>(*array[i]);
        }
    }
    return result;
}

template <Number T>
void FigureArray<T>::remove(size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < count - 1; ++i) {
        array[i] = std::move(array[i + 1]);
    }

    array[count - 1].reset();
    --count;
}

template <Number T>
size_t FigureArray<T>::size() const {
    return count;
}

#endif // FIGUREARRAY_H
