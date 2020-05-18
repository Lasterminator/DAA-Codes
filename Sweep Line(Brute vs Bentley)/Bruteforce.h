#pragma once
#include "Line.h"
#include <iostream>
#include <vector>

using namespace std;

class Bruteforce {
public:
	Bruteforce();
	~Bruteforce();

	void start(vector<Line*> lines);
private:
	int intersectionCount;
};

