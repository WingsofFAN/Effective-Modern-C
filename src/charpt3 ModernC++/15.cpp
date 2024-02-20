#include <iostream>

// 只要有可能使用 constexpr, 就使用它; 它不仅是const, 而且在编译阶段就已知

class Point {
public:
    constexpr Point(double xVal = 0.0, double yVal = 0.0) noexcept : x(xVal), y(yVal){}
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }

    // void setX(double newX) noexcept { x = newX; }
    // void setY(double newY) noexcept { y = newY; }
    constexpr void setX(double newX) noexcept { x = newX; }
    constexpr void setY(double newY) noexcept { y = newY; }

private:
    double x, y;
}; 


constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return { (p1.xValue() + p2.xValue()) / 2, // 周用 constexpr
    (p1. yValue() + p2. yValue()) / 2 } ;     // 成员由数
}

constexpr Point reflection(const Point& p) noexcept
{
    Point result;
    result.setX(-p.xValue());
    result.setY(-p.yValue());

    return result;
} 


int main()
{
    constexpr Point p1(9.4, 27.7); 
    constexpr Point p2(28.8, 5.3);
    constexpr auto mid= midpoint(p1, p2);
    constexpr auto reflectedMid = reflection(mid);  // reflectedMid 的值为 (-19.1 -16.5),且在编译期生成



}