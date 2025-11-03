#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
sn=a1*(q^n-1)/1-q)
sin^2(a)=(1-cos(2a))/2
sin(a)+sin(b)=2sin((a+b)/2)*cos((a-b)/2)
sin(a)-sin(b)=2sin((a-b)/2)*cos((a+b)/2)
cos(a)+cos(b)=2cos((a+b)/2)*cos((a-b)/2)
cos(a)-cos(b)=-2sin((a+b)/2)*sin((a-b)/2)
cos(a+b)=cos(a)*cos(b)-sin(a)*sin(b)
sin(a+b)=sin(a)*cos(b)+cos(a)*sin(b)
s(ABC)=0.5*abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))
s(ABC)=sqrt(p(p-a)*(p-b)*(p-c))
*/


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