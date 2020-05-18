#include "stdafx.h"
#include "Bruteforce.h"


Bruteforce::Bruteforce() {
	intersectionCount = 0;
}

Bruteforce::~Bruteforce() {
}

void Bruteforce::start(vector<Line*> lines) {
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines.size(); j++) {
			if (i != j) {
				float x = (lines[j]->getC() - lines[i]->getC()) / (lines[i]->getM() - lines[j]->getM());
				float y = lines[i]->getM() * x + lines[i]->getC();
				Point *intersectionPoint = new Point(x, y);
				if (intersectionPoint->isInYRange(lines[i]) && intersectionPoint->isInYRange(lines[j])) {
					intersectionCount++;
					//cout << "Intersect at (" << x << ", " << y << ")" << endl;
				}
			}
		}
	}
	cout << endl << "intersections: " << intersectionCount/2 << endl;
}
