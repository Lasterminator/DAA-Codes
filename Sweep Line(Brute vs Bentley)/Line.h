#pragma once
#include <string>

class Line;

class Point {
private:
	float x;
	float y;
public:
	Point();
	Point(float x, float y);
	float getX();
	float getY();
	bool isInYRange(Line* line);
};

class Line {
private:
	std::string name;
	Point **points;
	float m;
	float c;
public:
	Line();
	Line(std::string name, Point *p0, Point *p1);
	std::string getName();
	Point *getPoint(int index);
	float getM();
	float getC();
	float getX(float y);
};