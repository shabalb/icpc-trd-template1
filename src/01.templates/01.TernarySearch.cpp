#include <iostream>
#include <queue>
#include <vector>
using namespace std;

double f(double x) {

}

double ternarySearchMin(double left, double right, double eps) {
	if (right - left < eps){
		return (left + right) / 2;
	}
	double a = (left * 2 + right) / 3;
	double b = (left + right * 2) / 3;
	if (f(a) < f(b)) {
		return ternarySearchMin(left, b, eps);
	}
	else {
		return ternarySearchMin(a, right, eps);
	}
		
}


double ternarySearchMin( double left, double right, double eps) {
	double a, b;
	while (right - left > eps) {
		a = (left * 2 + right) / 3;
		b = (left + right * 2) / 3;
		if (f(a) < f(b)) {
			right = b;
		}
		else {
			left = a;
			return (left + right) / 2;
		}
	}
}


int main() {
	
}