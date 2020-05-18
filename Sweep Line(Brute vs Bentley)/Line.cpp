#include "stdafx.h"
#include "Line.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(float x, float y) {
	//use float since intersection can be fractional
	this->x = x;
	this->y = y;
}

float Point::getX() { return x; }
float Point::getY() { return y; }

bool Point::isInYRange(Line* line) {
	if (line->getPoint(0)->getY() > line->getPoint(1)->getY()) {
		if (y >= line->getPoint(1)->getY() && y <= line->getPoint(0)->getY()) {
			return true;
		}
	} else {
		if (y >= line->getPoint(0)->getY() && y <= line->getPoint(1)->getY()) {
			return true;
		}
	}
	return false;
}


Line::Line() {

}

Line::Line(std::string name, Point *p0, Point *p1) {
	this->name = name;
	points = new Point*[2];
	this->points[0] = p0;
	this->points[1] = p1;
	if (points[1]->getX() - points[0]->getX() != 0) {
		m = (points[1]->getY() - points[0]->getY()) / (points[1]->getX() - points[0]->getX());
	}
	else {
		m = 0;
	}
	c = points[0]->getY() - m*points[0]->getX();
}

std::string Line::getName() { return name; }
Point *Line::getPoint(int index) { return points[index]; }
float Line::getM() { return m; }
float Line::getC() { return c; }
float Line::getX(float y) { return (y-c) / m; }