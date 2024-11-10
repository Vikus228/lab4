#include "gtest/gtest.h"
#include "point.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "figurearray.h"
#include <memory>

TEST(PointTest, Equality) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    EXPECT_TRUE(p1 == p2);
}

TEST(PointTest, Inequality) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(2.0, 3.0);
    EXPECT_FALSE(p1 == p2);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<double> triangle(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    double area = static_cast<double>(triangle);
    EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(TriangleTest, CenterCalculation) {
    Triangle<double> triangle(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    auto center = triangle.Center();
    EXPECT_NEAR(center.first, 2.0, 1e-9);
    EXPECT_NEAR(center.second, 1.0, 1e-9);
}

TEST(HexagonTest, AreaCalculation) {
    std::array<Point<double>, 6> points = {
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, std::sqrt(0.75)),
        Point<double>(1, std::sqrt(3)), Point<double>(0, std::sqrt(3)),
        Point<double>(-0.5, std::sqrt(0.75))
    };
    Hexagon<double> hexagon(points);
    double area = static_cast<double>(hexagon);
    EXPECT_NEAR(area, 2.598076211, 1e-6);
}

TEST(HexagonTest, CenterCalculation) {
    std::array<Point<double>, 6> points = {
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, std::sqrt(0.75)),
        Point<double>(1, std::sqrt(3)), Point<double>(0, std::sqrt(3)),
        Point<double>(-0.5, std::sqrt(0.75))
    };
    Hexagon<double> hexagon(points);
    auto center = hexagon.Center();
    EXPECT_NEAR(center.first, 0.5, 1e-9);
    EXPECT_NEAR(center.second, std::sqrt(0.75), 1e-9);
}

TEST(OctagonTest, AreaCalculation) {
    std::array<Point<double>, 8> points = {
        Point<double>(1, 0), Point<double>(2, 0), Point<double>(3, 1), Point<double>(3, 2),
        Point<double>(2, 3), Point<double>(1, 3), Point<double>(0, 2), Point<double>(0, 1)
    };
    Octagon<double> octagon(points);
    double area = static_cast<double>(octagon);
    EXPECT_NEAR(area, 8.0, 1e-9);
}

TEST(OctagonTest, CenterCalculation) {
    std::array<Point<double>, 8> points = {
        Point<double>(1, 0), Point<double>(2, 0), Point<double>(3, 1), Point<double>(3, 2),
        Point<double>(2, 3), Point<double>(1, 3), Point<double>(0, 2), Point<double>(0, 1)
    };
    Octagon<double> octagon(points);
    auto center = octagon.Center();
    EXPECT_NEAR(center.first, 1.5, 1e-9);
    EXPECT_NEAR(center.second, 1.5, 1e-9);
}

TEST(FigureArrayTest, AddAndSize) {
    FigureArray<double> figures;
    auto triangle = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    figures.add(triangle);
    EXPECT_EQ(figures.size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray<double> figures;
    auto triangle = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    auto hexagon = std::make_shared<Hexagon<double>>(std::array<Point<double>, 6>{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, std::sqrt(0.75)),
        Point<double>(1, std::sqrt(3)), Point<double>(0, std::sqrt(3)),
        Point<double>(-0.5, std::sqrt(0.75))
    });
    figures.add(triangle);
    figures.add(hexagon);
    double totalArea = figures.totalArea();
    EXPECT_NEAR(totalArea, 8.598076211, 1e-6);
}

TEST(FigureArrayTest, Remove) {
    FigureArray<double> figures;
    auto triangle = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    auto hexagon = std::make_shared<Hexagon<double>>(std::array<Point<double>, 6>{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, std::sqrt(0.75)),
        Point<double>(1, std::sqrt(3)), Point<double>(0, std::sqrt(3)),
        Point<double>(-0.5, std::sqrt(0.75))
    });
    figures.add(triangle);
    figures.add(hexagon);
    figures.remove(0);
    EXPECT_EQ(figures.size(), 1);
    double totalArea = figures.totalArea();
    EXPECT_NEAR(totalArea, 2.598076211, 1e-6);
}

TEST(FigureArrayTest, OutOfRangeAccess) {
    FigureArray<double> figures;
    auto triangle = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    figures.add(triangle);
    EXPECT_THROW(figures[1], std::out_of_range);
}

TEST(FigureArrayTest, RemoveOutOfRange) {
    FigureArray<double> figures;
    EXPECT_THROW(figures.remove(0), std::out_of_range);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
