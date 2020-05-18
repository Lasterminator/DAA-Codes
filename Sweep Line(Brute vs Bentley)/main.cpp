#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <vector>
#include "Bruteforce.h"
#include "SweepLine.h"
#include "Line.h"

using namespace std;

int main()
{
	vector<Line*> lines;
	
	lines.push_back(new Line("line1", new Point(4, 7), new Point(1, 3)));
	lines.push_back(new Line("line2", new Point(2, 5), new Point(4, 2)));
	lines.push_back(new Line("line3", new Point(5, 5), new Point(6, 2)));
	lines.push_back(new Line("line4", new Point(6, 3), new Point(4, 1)));
	lines.push_back(new Line("line5", new Point(4, 5), new Point(7, 4)));

	// lines.push_back(new Line("line1", new Point(3, 11), new Point(5, 2)));
	// lines.push_back(new Line("line2", new Point(5, 9), new Point(1, 3)));
	// lines.push_back(new Line("line3", new Point(5, 5), new Point(3, 0)));

	clock_t tStart = clock();
	Bruteforce *bruteforce = new Bruteforce();
	bruteforce->start(lines);
	cout << "\n\nBruteforce Time: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " s" << endl;

	SweepLine *sweepLine = new SweepLine();
	sweepLine->initEvents(lines);
	tStart = clock();
	sweepLine->startSweep(lines);
	cout << "\n\nSweep Line Time: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " s" << endl;

	system("PAUSE");
    return 0;
}

