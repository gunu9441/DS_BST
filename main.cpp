#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
	Manager manager;
	manager.run("command.txt");

	return 0;
}