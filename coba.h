#include <iostream>

using namespace std;

class Coba {
	public:
	Coba() {
		a = 0;
	}
	int total() {
		int b = 10;
		a = 10;
		return b;
	}

	void print() {
		cout << "a: " << a << endl;
	}

	private:
		int a;
};