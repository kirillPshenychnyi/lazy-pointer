#include "Lazy_ptr.hpp"
#include <cassert>
#include <string>

struct Point {

	double x, y;

	Point() {
		x = y = 0;
	}

	Point(double _x, double _y) : x(_x), y(_y) {};

	bool operator == (const Point B) const {
		return (x == B.x && y == B.y);

	}
};

int main() {

	lazy_array_ptr<int > lazy(10);
	assert(!lazy);
	assert(lazy[2] == 0);
	assert(lazy);

	lazy_array_ptr<Point> lazy_points(5);

	assert(!lazy_points);
	assert(lazy_points[2].x == lazy_points[2].y && lazy_points[2].x == 0);
	assert(lazy_points);
	lazy_points.reset();
	
	const Point * address = lazy_points.getAdress();
	assert(!address);
	assert((*lazy_points).x == 0);
	assert(lazy_points);
	
	Point A{ 5.0 , -3.0 };
	(*lazy_points) = A;

	assert(lazy_points[0] == A);
	
	Point B{ 5.0 , -5.0 };

	lazy_points[0] = B;

	assert(lazy_points[0] == B);



	return 0;

}