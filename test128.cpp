/*
 * test128.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given 4 points (x1,y1) (x2,y2) (x3,y3) (x4,y4) (left, up, down, right) of a rectangle, and another point (x,y)
// determine whether (x,y)  is inside the rectangle
int isInsideRectangle(const vector<pair<double, double>>& points) {
	if (points.size() != 5) {
		return 0;
	}
	//connect 2 points of 4 points to get the equation of 4 boundaries of the rectangle
	//line1 through (x1,y1) and (x2,y2): (x2 - x1)*(y - y2) = (y2 - y1)*(x - x2)
	//line2 through (x2,y2) and (x4,y4): (x4 - x2)*(y - y4) = (y4 - y2)*(x - x4)
	//line3 through (x3,y3) and (x4,y4): (x4 - x3)*(y - y4) = (y4 - y3)*(x - x4)
	//line4 through (x1,y1) and (x3,y3): (x3 - x1)*(y - y3) = (y3 - y1)*(x - x3)
	//for (x,y) inside rectangle, (x,y) must under line1 and line2, above line3 and line4
	int under1, under2, above3, above4;
	under1 = (points[1].first - points[0].first) * (points[4].second - points[1].second) < (points[1].second - points[0].second) * (points[4].first - points[1].first) ? 1 : 0;
	under2 = (points[3].first - points[1].first) * (points[4].second - points[3].second) > (points[3].second - points[1].second) * (points[4].first - points[3].first) ? 1 : 0;
	above3 = (points[3].first - points[2].first) * (points[4].second - points[3].second) > (points[3].second - points[2].second) * (points[4].first - points[3].first) ? 1 : 0;
	above4 = (points[2].first - points[0].first) * (points[4].second - points[2].second) < (points[2].second - points[0].second) * (points[4].first - points[2].first) ? 1 : 0;
	return under1 && under2 && above3 && above4;
}

//given 3 points (x1,y1) (x2,y2) (x3,y3) (ordered in increading order of x position) of a triangle, and another point (x,y)
//find if (x,y) is inside the triangle
int isInsideTriangle(const vector<pair<double, double>>& points) {
	if (points.size() != 4) {
		return 0;
	}
	//the boundaries of triangle can be represented by the following 3 lines
	//line1: (x2-x1)*(y-y2)=(y2-y1)*(x-x2)
	//line2: (x3-x2)*(y-y3)=(y3-y2)*(x-x3)
	//line3: (x3-x1)*(y-y1)=(y3-y1)*(x-x1)
	//x1<=x2<=x3
	double x1 = points[0].first, y1 = points[0].second, x2 = points[1].first, y2 = points[1].second, x3 = points[2].first, y3 = points[2].second, x = points[3].first, y = points[3].second;
	int pos1 = (x2 - x1) * (y - y2) - (y2 - y1) * (x - x2), pos2 = (x3 - x2) * (y - y3) - (y3 - y2) * (x - x3), pos3 = (x3 - x1) * (y - y1) - (y3 - y1) * (x - x1);
	return (pos1 < 0 && pos2 < 0 && pos3 > 0) || (pos1 > 0 && pos2 > 0 && pos3 < 0);
}

int main(int argc, char* argv[]) {
	cout << "point is inside rectangle: " << (isInsideRectangle({}) ? "true" : "false") << endl;
	return 0;
}




