#include <iostream>
#include "UnitTest.h"
#include "Board.h"
using namespace std;

int main (int argc, char* argv[]) {

	bool success = true;

	if(!Board::Test(cout)) success = false;

	if (success) {
		cout << "Tests Succeeded!" << endl;
	}
	else {
		cout << "Tests Failed!" << endl;
	}

	return 0;
}
