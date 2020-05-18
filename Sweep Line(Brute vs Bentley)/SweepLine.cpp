#include "stdafx.h"
#include "SweepLine.h"

Event::Event(EventType type, Line *line, Point *point) {
	this->type = type;
	this->line = line;
	this->point = point;
}

bool Event::operator < (const Event &event2) const {
	if (this->point->getY() != event2.point->getY()) {
		return this->point->getY() < event2.point->getY();
	}
	else if (this->type != event2.type) {
		return this->type < event2.type;
	}
	else {
		return this->point->getX() < event2.point->getX();
	}
}


Status::Status(Line *line, Point *currentPoint) {
	this->line = line;
	this->currentPoint = currentPoint;
}

bool Status::operator > (Point &point2) {
	return this->currentPoint->getX() > point2.getX();
}


SweepLine::SweepLine() {
}


SweepLine::~SweepLine() {
}


void SweepLine::initEvents(vector<Line*> lines) {
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				events.push_back(Event(EventType::Start, lines[i], lines[i]->getPoint(j)));
			}
			else {
				events.push_back(Event(EventType::End, lines[i], lines[i]->getPoint(j)));
			}
		}
	}

	sort(events.begin(), events.end());
	reverse(events.begin(), events.end());
}

void SweepLine::startSweep(vector<Line*> lines) {
	for (int i = 0; i < events.size(); i++) {
		//std::cout << "EventType: " << events[i].type << " LineName: " << events[i].line->getName() << " x: " << events[i].point->getX() << " y: " << events[i].point->getY() << endl;

		if (events[i].type == EventType::Start) {
			int j = 0;
			for (j = 0; j < status.size(); j++) {
				//std::cout << "(" << status[j].currentPoint->getX() << ", " << status[j].currentPoint->getY() << ") " << " > " << "(" << events[i].point->getX() << ", " << events[i].point->getY() << ") ";
				if (status[j] > *events[i].point /*&& status[j].line->getName() != events[i].line->getName()*/) {
					status.insert(status.begin() + j, Status(events[i].line, events[i].point));
					break;
				}
			}
			if (j == status.size()) {
				status.push_back(Status(events[i].line, events[i].point));
			}

		}
		else if (events[i].type == EventType::Middle) {

		}
		else {
			/*std::cout << endl;
			for (int j = 0; j < status.size(); j++) {
				std::cout << status[j].line->getName() << " , ";
			}
			std::cout << endl;*/
			for (int j = 0; j < status.size(); j++) {
				if (status[j].line == events[i].line) {
					bool intersect = false;
					if (j < status.size() - 1) {
						//std::cout << endl << "NEXT";
						if (status[j+1].currentPoint->getX() <= events[i].point->getX()) {
							//std::cout << endl << "INTERSECT!";
							intersectionCount++;
							intersect = true;
						}
					}
					if (!intersect && j > 0) {
						//std::cout << endl << "PREV";
						if (status[j].currentPoint->getX() >= events[i].point->getX()) {
							//std::cout << endl << "INTERSECT!";
							intersectionCount++;
						}
					}
					//std::cout << "delete " << status[j].line->getName();
					status.erase(status.begin() + j);
					j--;
				}
			}
		}
	}
	std::cout << endl << "Total Intersections: " << intersectionCount << endl;
}

