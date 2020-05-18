#pragma once
#include "Line.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "Line.h"

using namespace std;

enum EventType {
	Start, Middle, End
};

class Event {
public:
	EventType type;
	Line *line;
	Point *point;

	Event(EventType type, Line *line, Point *point);
	bool operator < (const Event &event2) const;
};

class Status;

class Status {
public:
	int heapIndex;
	Line *line;
	Point *currentPoint;

	Status(Line *line, Point *currentPoint);
	//bool operator > (Status &status2);
	bool operator > (Point &point2);
};

class SweepLine {
private:
	vector<Event> events;
	vector<Status> status;
	int intersectionCount;
public:
	SweepLine(); //constructor
	~SweepLine(); //destructor

	void initEvents(vector<Line*> lines);
	void startSweep(vector<Line*> lines);
};

