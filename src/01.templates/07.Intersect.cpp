#include <iostream>

using namespace std;

struct pt {
	int x, y;
};

inline int area(pt a, pt b, pt c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1(int a, int b, int c, int d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d);
}

bool intersect(pt a, pt b, pt c, pt d) {
	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

const double EPS = 1E-9;
inline int det(int a, int b, int c, int d) {
	return a * d - b * c;
}

inline bool between(int a, int b, double c) {
	return min(a, b) <= c + EPS && c <= max(a, b) + EPS;
}

bool intersect1(pt a, pt b, pt c, pt d) {
	int A1 = a.y - b.y, B1 = b.x - a.x, C1 = -A1 * a.x - B1 * a.y;
	int A2 = c.y - d.y, B2 = d.x - c.x, C2 = -A2 * c.x - B2 * c.y;
	int zn = det(A1, B1, A2, B2);
	if (zn != 0) {
		double x = -det(C1, B1, C2, B2) * 1. / zn;
		double y = -det(A1, C1, A2, C2) * 1. / zn;
		return between(a.x, b.x, x) && between(a.y, b.y, y)
			&& between(c.x, d.x, x) && between(c.y, d.y, y);
	}
	else
		return det(A1, C1, A2, C2) == 0 && det(B1, C1, B2, C2) == 0
		&& intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y);
}
int main() {
	pt p1{ 1,1 }, p2{ 2,2 }, p3{ 1,3 }, p4{ 2,0 };
	cout << intersect1(p1, p2, p3, p4) << endl;
}
