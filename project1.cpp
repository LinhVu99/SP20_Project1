#include <iostream>
using namespace std;

double squareroot(double var) {
	double eps = 1e-6;
	double k = var;
	double l = 0.0, r, mid;

	if (k >= 1)
		r = k;
	if (k < 1)
		r = 1;

	while ((l - k/l > eps) || (l - k/l < -eps)) {
		mid = l + (r -l)/2;
		if (mid < k/mid)
			l = mid;
		else
			r = mid;
	}

	return l;
}

// round to two decimals
double round(double var)
{
	double value = (int)(var*100.0);
	return (double)value/100.0;
}

class Point {
protected:
	double x;
	double y;
public:
	Point(); //default constructor
	Point(double xValue, double yValue);
	void setLocation(double xValue, double yValue); //set x = xValue and y = yValue
	double getXValue(); //return x
	double getYValue(); //return y
	void display();
};

Point::Point() {
	x = 0.0;
	y = 0.0;
}

Point::Point(double xValue, double yValue) {
	x = xValue;
	y = yValue;
}

void Point::setLocation(double xValue, double yValue) {
	x = xValue;
	y = yValue;
}

double Point::getXValue() {
	return round(x);
}

double Point::getYValue() {
	return round(y);
}

void Point::display() {
	cout << "(" << this->getXValue() << ", " << this->getYValue() << ")"; //display the point in form (x, y)
}

class LineSegment {
public:
	Point p1;
	Point p2;
public:
	LineSegment(); //default structure
	LineSegment(Point one, Point two);
	double length(); //return the length of the segment
	Point midPoint(); //return the midpoint of the segment
	double xIntercept(); //return x-intercept of the segment
	double yIntercept(); //return y-intercept of the segment
	double yInterceptUnrounded(); //for finding intersection point
	double slope(); //return the slope of the segment
	double slopeUnrounded(); //for finding intersection point
	bool isIntersects(LineSegment L); //return true if L intersects with this segment
	Point intersectionPoint(LineSegment L);
	bool isParallel(LineSegment L); //return true if L and this segment are parallel
	void displayEquation();
};

LineSegment::LineSegment() {
	p1 = Point(0.0, 0.0);
	p2 = Point(0.0, 0.0);
}

LineSegment::LineSegment(Point one, Point two) {
	p1 = one;
	p2 = two;
}

double LineSegment::length() {
	return round(squareroot((p1.getXValue() - p2.getXValue())*(p1.getXValue() - p2.getXValue()) + (p1.getYValue() - p2.getYValue())*(p1.getYValue() - p2.getYValue())));
}

Point LineSegment::midPoint() {
	double xValue = round((p1.getXValue() + p2.getXValue())/2);
	double yValue = round((p1.getYValue() + p2.getYValue())/2);
	Point mPoint = Point(xValue, yValue);
	return mPoint;
}

double LineSegment::xIntercept() {
	return round(p1.getXValue() - p1.getYValue()*(p2.getXValue() - p1.getXValue())/(p2.getYValue() - p1.getYValue()));
}

double LineSegment::yIntercept() {
	return round(p1.getYValue() - (p2.getYValue() - p1.getYValue())/(p2.getXValue() - p1.getXValue())*p1.getXValue());
}

double LineSegment::yInterceptUnrounded() {
	return p1.getYValue() - (p2.getYValue() - p1.getYValue())/(p2.getXValue() - p1.getXValue())*p1.getXValue();
}

double LineSegment::slope() {
	return round((p2.getYValue() - p1.getYValue())/(p2.getXValue() - p1.getXValue()));
}

double LineSegment::slopeUnrounded() {
	return (p2.getYValue() - p1.getYValue())/(p2.getXValue() - p1.getXValue());
}

bool LineSegment::isIntersects(LineSegment L) {
	double d1 = (this->p2.getXValue() - this->p1.getXValue())*(L.p1.getYValue() - this->p1.getYValue()) - (L.p1.getXValue() - this->p1.getXValue())*(this->p2.getYValue() - this->p1.getYValue());
	double d2 = (this->p2.getXValue() - this->p1.getXValue())*(L.p2.getYValue() - this->p1.getYValue()) - (L.p2.getXValue() - this->p1.getXValue())*(this->p2.getYValue() - this->p1.getYValue());
	double d3 = (L.p2.getXValue() - L.p1.getXValue())*(this->p1.getYValue() - L.p1.getYValue()) - (this->p1.getXValue() - L.p1.getXValue())*(L.p2.getYValue() - L.p1.getYValue());
	double d4 = (L.p2.getXValue() - L.p1.getXValue())*(this->p2.getYValue() - this->p1.getYValue()) - (this->p2.getXValue() - this->p1.getXValue())*(L.p2.getYValue() - L.p1.getYValue());
	if ((d1*d2 <= 0) && (d3*d4 <= 0))
		return true;
	else
		return false;
}

Point LineSegment::intersectionPoint(LineSegment L) {
	double xValue = round((L.yInterceptUnrounded() - this->yInterceptUnrounded())/(this->slopeUnrounded() - L.slopeUnrounded()));
	double yValue = round((this->yInterceptUnrounded()*L.slopeUnrounded() - L.yInterceptUnrounded()*this->slopeUnrounded())/(L.slopeUnrounded() - this->slopeUnrounded()));
	Point iPoint = Point(xValue, yValue);
	return iPoint;
}

bool LineSegment::isParallel(LineSegment L) {
	if ((this->slope() == L.slope()) && (this->xIntercept() != L.xIntercept()))
		return true;
	else
		return false;
}

void LineSegment::displayEquation() {
	cout << "y=" << this->slope() << "*x+" << this->yIntercept() << endl; //display the equation in form y=m*x+c
}

class Intervals {
protected:
	LineSegment* segments;
	int count;
	int maxSize;
public:
	Intervals();
	Intervals(int size);
	void addLineSegment(LineSegment L);
	void display();
	void compare();
};

Intervals::Intervals() {
	segments = NULL;
	count = 0;
	maxSize = 0;
}

Intervals::Intervals(int size) {
	segments = new LineSegment[size];
	count = 0;
	maxSize = size;
}

void Intervals::addLineSegment(LineSegment L) {
	segments[count] = L;
	count++;
}

//display properties of each segment
void Intervals::display() {
	for (int i = 0; i < maxSize; i++) {
		cout << "Line Segment " << i+1 << ":" << endl;
		segments[i].p1.display();
		cout << ",";
		segments[i].p2.display();
		cout << "" << endl;
		cout << "Slope:" << segments[i].slope() << endl;
		cout << "Midpoint:";
		segments[i].midPoint().display();
		cout << "" << endl;
		cout << "X Intercept:" << segments[i].xIntercept() << endl;
		cout << "Y Intercept:" << segments[i].yIntercept() << endl;
		cout << "Length:" << segments[i].length() << endl;
		segments[i].displayEquation();
	}
}

//display if each pair of segments in the array is intersecting or parallel or neither
void Intervals::compare() {
	for (int i = 0; i < maxSize-1; i++) {
		for (int j = i+1; j < maxSize; j++) {
			if (i != j) {
				if (segments[i].isIntersects(segments[j]) == true) {
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: Intersection Point :";
					segments[i].intersectionPoint(segments[j]).display();
					cout << "" << endl;
				}
				else if (segments[i].isParallel(segments[j]) == true)
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: Lines are Parallel" << endl;
				else
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: Not Parallel and not Intersecting" << endl;
			}
		}
	}
}

int main() {
	int numOfSegments;
	double x1, y1, x2, y2;

	cin >> numOfSegments;
	Intervals interval = Intervals(numOfSegments); //create an array with the size of numOfSegments

	for (int i = 0; i < numOfSegments; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		Point p1 = Point(x1, y1); //create Point 1
		Point p2 = Point(x2, y2); //create Point 2
		LineSegment segment = LineSegment(p1, p2); //create a segment from Point 1 and Point 2
		interval.addLineSegment(segment); //store segments in array
	}

	interval.display();
	interval.compare();

	return 0;
}
