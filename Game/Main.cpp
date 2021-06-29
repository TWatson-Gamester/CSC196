#include "Helper.h"
#include "Dynamic.h"
#include <iostream>

using namespace std;

int main() {
	cout << nc::sqr(5) << endl;

	nc::point p1(10, 10);
	nc::point p2(10, 10);
	nc::point p3 = p1 + p2;

	cout << p3.x << " " << p3.y << endl;

	system("pause"); //Makes the console pause until a key is pressed

}