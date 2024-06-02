#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using Point = pair<double, double>;
using Polyline = vector<Point>;

void PrintPolyline(Polyline& polyline) {
    int size = polyline.size();
    std::cout << "[";
    for (int i=0; i<size; i++) {
        std::cout << "(" << polyline[i].first << ", "
                         << polyline[i].second << "), ";
    }
    std::cout << std::endl;
}

double GetDistance(const Point& p1, const Point& p2) {
    double dx = p2.first - p1.first;
    double dy = p2.second - p1.second;
    return hypot(dx, dy);
}

double GetDirection(const Point& p1, const Point& p2) {
    double dx = p2.first - p1.first;
    double dy = p2.second - p1.second;
    return atan2(dy, dx);
}

Point GetPointOnLine(Point& start, double direction, double distance) {
    return std::make_pair(start.first + distance * cos(direction),
                          start.second + distance * sin(direction));
}

Polyline GetTrimPointsOnPolyline(const Polyline& polyline, 
                                 const double trim_distance) {
    int polyline_size = polyline.size();
    if (polyline_size == 1) return polyline;
    Polyline result;
    result.push_back(polyline[0]);
    
    int i = 1;
    Point curr = polyline[i-1];

    while (i < polyline_size) {
        double remaining_distance = trim_distance;
        while(remaining_distance != 0) {
            if (i >= polyline_size) break;
            double direction = GetDirection(curr, polyline[i]);
            double distance = GetDistance(curr, polyline[i]);

            if (distance >= remaining_distance) {
                Point p = GetPointOnLine(curr, direction, remaining_distance);
                result.push_back(p);
                curr = p;
                remaining_distance = 0;
            } else {
                remaining_distance -= distance;
                curr = polyline[i];
                i++;
            }
        }
    }
    return result;
}

int main() {
    // Polyline polyline{{0, 0}, {3, 0}, {3, 1}, {4, 1}, {6, 3}, {8, 3}};
    Polyline polyline{{0, 0}, {12, 0}};
    // Polyline polyline{{0, 0}, {1, 0}};
    double distance = 2;
    Polyline result = GetTrimPointsOnPolyline(polyline, distance);
    PrintPolyline(result);
}