#include "libs.h"
#include "Vector.h"
#include "LongNumber.h"
#include "LongDotNumber.h"

using namespace std;

int main() {

	LongDotNumber A, B;
	while (true) {
		cin >> A >> B;
		cout << "A = " << A << '\n';
		cout << "B = " << B << '\n';
		cout << "A + B = " << A + B << '\n';
		cout << "A - B = " << A - B << '\n';
		cout << "A * B = " << A * B << '\n';
		cout << "A / B = " << A / B << '\n';
		cout << "----\n";
	}

	return 0;
}