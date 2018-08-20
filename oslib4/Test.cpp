#include"Runner.h"
#include<iostream>
using namespace std;
const int numOfRound = 5;
const int tableSize = 600;

int main() {
	Runner runner(numOfRound, tableSize);
	runner.run();
	system("pause");
	return 0;
}
