#include <bits/stdc++.h>
#include <map>
#include <math.h>
using namespace std;

double error = 1e-10;
class Point
{
	public:
		double x, y;
		Point()
		{
			return;
		}
		Point(double x, double y)
		{
			this->x = x;
			this->y = y;
		}
		double distance(Point &b)
		{
			return sqrt(pow((b.x - this->x), 2) + pow((b.y - this->y), 2));
		}
};

class Segment
{
	public:
		//mx + b
		double m, b;
		Point start, end;
		Segment()
		{
			return;
		}
		Segment(Point &start, Point &end)
		{
			this->start = start;
			this->end = end;
			this->m = (end.y - start.y) / (end.x - start.x);
			this->b = start.y - this->m * start.x;
		}
		Segment bisector()
		{
			// this process can be obtained using simple linear equation
			Segment perp;
			Point mid_point((this->start.x + this->end.x) / 2, 
				(this->start.y + this->end.y) / 2);

			perp.m = (double)(-1)/(this->m);

			perp.b = mid_point.y - perp.m * mid_point.x;
			return perp;
		}
		Point intersect(Segment s)
		{
			double x = (s.b - this->b) / (this->m - s.m);
			double y = s.m * x + s.b;
			return Point(x, y);
		}

};
class Circle
{
	public:
		double radius;
		Point center;
		Circle()
		{
			return;
		}
		Circle(Point &center, double radius)
		{
			this->center = center;
			this->radius = radius;
		}
		Circle(Point &a, Point &b, Point &c)
		{
			// to create a circumcircle get the bisector of two segment (3 different points)
			// and intersect them with this you can obtain the center of the circle
			// which is x distance to the points
			Segment s1(a, b), s2(b, c);
			this->center = s1.bisector().intersect(s2.bisector());
			this->radius = this->center.distance(a);
		}
		bool is_inside(Point &a)
		{
			return pow((a.x - this->center.x), 2) + pow((a.y - this->center.y), 2) < pow(this->radius, 2);
		}
};

map<pair<int,int>, vector<int>> triangles;
map<int, Point> points;

void update(int id_begin_point, int id_end_point,
			int id_to_update, int id_to_replace,
			map<pair<int,int>, vector<int>> &not_checked)
{
	// only update the id which not belong to the new triangle
	// formed by the flip this is due to the fact that flip an id
	// change the bottom or the upper point of a triangle

	int min_id=min(id_begin_point, id_end_point);
	int max_id=max(id_begin_point, id_end_point);
	if(triangles[{min_id, max_id}][0] == id_to_replace)
		triangles[{min_id, max_id}][0] = id_to_update;
	else
		triangles[{min_id, max_id}][1] = id_to_update;
	not_checked[{min_id, max_id}] = triangles[{min_id, max_id}];

}
int legalize()
{
	// create a map of every triangule (segment with upper or lower points)
	// which was in the input
	map<pair<int,int>, vector<int>> not_checked(triangles);
	int flips = 0;
	while(!not_checked.empty())
	{
		auto triangle = not_checked.begin();
		// check if this triangule has more than 1 point 
		// if it only has one point it is no necessary to optimize
		// because it is a unique triangule
		if(triangle->second.size() < 2){
			not_checked.erase(triangle);
			continue;
		}
		// the first two are the id points that create the segment which create the triangule
		// the last two are the points upper and lower of that segment 
		//
		int seg_begin_point = triangle->first.first;
		int seg_end_point = triangle->first.second;
		int top_point = triangle->second[0];
		int bottom_point = triangle->second[1];
		// erase the triangule 
		not_checked.erase(triangle);
		// create a circumcircle with the diameter being the segment 
		// that create the triangle and take any of the point
		// could be the top or the bottom it doesn't matter
		Circle circumcircle (points[seg_begin_point], 
							points[seg_end_point], 
							points[top_point]);
		// check if the other point is inside the circle
		if(circumcircle.is_inside(points[bottom_point]))
		{
			// erase the triangle from triangles
			triangles.erase(triangle->first);
			int min_id=min(top_point, bottom_point);
			int max_id=max(top_point, bottom_point);
			// create a new triangle (segment with the condition given below)
			triangles[{min_id,max_id}].push_back(seg_begin_point);
			triangles[{min_id,max_id}].push_back(seg_end_point);
			// update the triangle because we flip a segment
			update(seg_begin_point, top_point, bottom_point, seg_end_point, not_checked);
			update(seg_begin_point, bottom_point, top_point, seg_end_point, not_checked);
			update(seg_end_point, top_point, bottom_point, seg_begin_point, not_checked);
			update(seg_end_point, bottom_point, top_point, seg_begin_point, not_checked);
			flips++;
		}

	}
	return flips;
}
int main()
{
	int n, m;
	cin >> n >> m;

	for(int i=0; i<n; i++)
	{
		double x, y;
		int id;
		cin >> id >> x >> y;
		points[id] = Point(x, y);
	}
	for(int i=0; i<m; i++)
	{
		int id1, id2, id3;
		cin >> id1 >> id2 >> id3;
		triangles[{min(id1, id2), max(id1, id2)}].push_back(id3);
		triangles[{min(id1, id3), max(id1, id3)}].push_back(id2);
		triangles[{min(id2, id3), max(id2, id3)}].push_back(id1);
		
	}
	
	cout << legalize() << endl;

	return 0;
}