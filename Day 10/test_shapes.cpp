#include <gtest/gtest.h>
#include "Shapes.cpp"  
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

TEST(CircleTest, AreaIsCorrectForRadius5) {
    // Arrange
    Circle c(5.0);
    // Act
    double result = c.area();
    // Assert — M_PI * 5 * 5 = 78.5398...
    EXPECT_NEAR(result, 78.5398, 0.001);
}

TEST(CircleTest, PerimeterIsCorrectForRadius5) {
    // Arrange
    Circle c(5.0);
    // Act
    double result = c.perimeter();
    // Assert — 2 * M_PI * 5 = 31.4159...
    EXPECT_NEAR(result, 31.4159, 0.001);
}

TEST(CircleTest, AreaIsZeroForRadiusZero) {
    // Arrange — edge case: radius 0
    Circle c(0.0);
    // Act
    double result = c.area();
    // Assert
    EXPECT_NEAR(result, 0.0, 0.0001);
}

TEST(RectangleTest, AreaIsWidthTimesHeight) {
    // Arrange
    Rectangle r(4.0, 6.0);
    // Act
    double result = r.area();
    // Assert
    EXPECT_EQ(result, 24.0);
}

TEST(RectangleTest, PerimeterIsTwiceWidthPlusHeight) {
    // Arrange
    Rectangle r(4.0, 6.0);
    // Act
    double result = r.perimeter();
    // Assert
    EXPECT_EQ(result, 20.0);
}

TEST(RectangleTest, SquareIsSpecialCaseOfRectangle) {
    // Arrange — edge case: width == height
    Rectangle square(5.0, 5.0);
    // Act
    double area = square.area();
    double perimeter = square.perimeter();
    // Assert
    EXPECT_EQ(area, 25.0);
    EXPECT_EQ(perimeter, 20.0);
}

TEST(TriangleTest, AreaIsHalfBaseTimesHeight) {
    // Arrange
    Triangle t(6.0, 4.0, 5.0, 5.0); // base=6, height=4, sides=5,5
    // Act
    double result = t.area();
    // Assert — 0.5 * 6 * 4 = 12
    EXPECT_EQ(result, 12.0);
}

TEST(TriangleTest, PerimeterIsSumOfThreeSides) {
    // Arrange
    Triangle t(6.0, 4.0, 5.0, 5.0); // base + side1 + side2
    // Act
    double result = t.perimeter();
    // Assert — 6 + 5 + 5 = 16
    EXPECT_EQ(result, 16.0);
}


TEST(ShapeSortTest, ShapesSortCorrectlyByArea) {
    // Arrange
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));      // area ≈ 12.57
    shapes.push_back(std::make_unique<Rectangle>(10, 10)); // area = 100
    shapes.push_back(std::make_unique<Triangle>(4, 3, 5, 5)); // area = 6

    // Act
    std::sort(shapes.begin(), shapes.end(),
        [](const std::unique_ptr<Shape>& a, const std::unique_ptr<Shape>& b) {
            return a->area() < b->area();
        });

    // Assert — smallest to largest: Triangle(6), Circle(12.57), Rectangle(100)
    EXPECT_NEAR(shapes[0]->area(), 6.0, 0.01);
    EXPECT_NEAR(shapes[1]->area(), 12.57, 0.01);
    EXPECT_NEAR(shapes[2]->area(), 100.0, 0.01);
}

TEST(ShapeSortTest, FindFirstShapeWithAreaGreaterThan100) {
    // Arrange
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));       // ~12.57
    shapes.push_back(std::make_unique<Rectangle>(20, 20));  // 400
    shapes.push_back(std::make_unique<Triangle>(4, 3, 5, 5)); // 6

    // Act
    auto it = std::find_if(shapes.begin(), shapes.end(),
        [](const std::unique_ptr<Shape>& s) { return s->area() > 100; });

    // Assert
    ASSERT_NE(it, shapes.end());           // a match was found
    EXPECT_NEAR((*it)->area(), 400.0, 0.01);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}