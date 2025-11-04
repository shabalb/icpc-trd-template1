#include <bits/stdc++.h>
using namespace std;
// == СТРУКТУРЫ ==
// Структура Point представляет точку в 2D и вектор
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& v) const {
        return Point(x + v.x, y + v.y);
    }
    Point operator-(const Point& v) const {
        return Point(x - v.x, y - v.y);
    }
    Point operator*(double k) const {
        return Point(x * k, y * k);
    }
    // Скалярное произведение векторов
    double dot(const Point& v) const {
        return x * v.x + y * v.y;
    }
    // Векторное произведение
    double cross(const Point& v) const {
        return x * v.y - y * v.x;
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
};
// Line ax + by + c = 0.
struct Line {
    double a, b, c;
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    // Создание прямой по двум точкам.
    Line(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -a * p1.x - b * p1.y;
    }
};
// == ФУНКЦИИ ==
//пересекаются ли два отрезка
bool segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
    double d1 = (p2 - p1).cross(p3 - p1);
    double d2 = (p2 - p1).cross(p4 - p1);
    double d3 = (p4 - p3).cross(p1 - p3);
    double d4 = (p4 - p3).cross(p2 - p3);
    if (d1 * d2 < 0 && d3 * d4 < 0)
        return true;

    auto onSegment = [](Point a, Point b, Point c) -> bool {
        return (b.x <= max(a.x, c.x) && b.x >= min(a.x, c.x) &&
            b.y <= max(a.y, c.y) && b.y >= min(a.y, c.y));
    };
    if (d1 == 0 && onSegment(p1, p3, p2)) return true;
    if (d2 == 0 && onSegment(p1, p4, p2)) return true;
    if (d3 == 0 && onSegment(p3, p1, p4)) return true;
    if (d4 == 0 && onSegment(p3, p2, p4)) return true;
    return false;
}

//расстояние между двумя точками
double dist(Point p1, Point p2) {
    return (p2 - p1).len();
}

//расстояние от точки до прямой
double distToLine(Point p, Line l) {
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

//площадь треугольника по трем точкам
double triangleArea(Point a, Point b, Point c) {
    return abs((b - a).cross(c - a)) / 2.0;
}
/*
    площадь многоугольника по формуле шнуровки
    points - вершины многоугольника в порядке обхода
*/
double polygonArea(const vector<Point>& points) {
    double area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return abs(area) / 2.0;
}

/*
    находится ли точка внутри оси-выровненного прямоугольника
    rectA и rectB - противоположные вершины прямоугольника
*/
bool pointInRectangle(Point p, Point rectA, Point rectB) {
    double minX = min(rectA.x, rectB.x);
    double maxX = max(rectA.x, rectB.x);
    double minY = min(rectA.y, rectB.y);
    double maxY = max(rectA.y, rectB.y);

    return (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY);
}

// ближайшая к точке p точку на отрезке [a-b]
Point closestPointOnSegment(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;

    double t = ap.dot(ab) / ab.dot(ab);
    t = max(0.0, min(1.0, t));
    return a + ab * t;
}
// является ли многоугольник выпуклым
bool isConvex(const vector<Point>& poly) {
    int n = poly.size();
    if (n < 3)
        return false;

    int sign = 0;
    for (int i = 0; i < n; i++) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];
        Point c = poly[(i + 2) % n];
        double cross = (b - a).cross(c - b);
        if (abs(cross) < 1e-9)
            continue;
        int currSign = (cross > 0) ? 1 : -1;
        if (sign == 0)
            sign = currSign;
        else if (sign != currSign)
            return false;
    }
    return true;
}

// == ФОРМУЛЫ ПЛОЩАДЕЙ И ОБЪЕМОВ ==

double circleArea(double r) { return M_PI * r * r; }
double circleCircumference(double r) { return 2 * M_PI * r; }
double sphereArea(double r) { return 4 * M_PI * r * r; }
double sphereVolume(double r) { return (4.0 / 3.0) * M_PI * r * r * r; }
double rectangleArea(double w, double h) { return w * h; }
double trapezoidArea(double a, double b, double h) { return (a + b) * h / 2.0; }
double cylinderVolume(double r, double h) { return M_PI * r * r * h; }
double coneVolume(double r, double h) { return (1.0 / 3.0) * M_PI * r * r * h; }
double pyramidVolume(double baseArea, double h) { return (1.0 / 3.0) * baseArea * h; }

// == ПРИМЕРЫ ==

int main() {
    setlocale(LC_ALL, "");

    // Тест пересечения отрезков
    Point a(0, 0), b(2, 2), c(0, 2), d(2, 0);
    wcout << L"Отрезки пересекаются: " << segmentsIntersect(a, b, c, d) << endl;

    // Тест площади
    vector<Point> square = { Point(0,0), Point(1,0), Point(1,1), Point(0,1) };
    wcout << L"Площадь квадрата: " << polygonArea(square) << endl;

    // Тест формул
    wcout << L"Площадь круга r=3: " << circleArea(3) << endl;
    wcout << L"Объем сферы r=2: " << sphereVolume(2) << endl;
    wcout << L"Объем конуса r=2,h=5: " << coneVolume(2, 5) << endl;

    // Тест ближайшей точки
    Point p(0.5, 0.5);
    Point segA(0, 0), segB(1, 0);
    Point closest = closestPointOnSegment(p, segA, segB);
    wcout << L"Ближайшая точка: (" << closest.x << "," << closest.y << ")" << endl;

    return 0;
}