#include <bits/stdc++.h>
using namespace std;

#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)), EPS)

class Point {
  public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(Point &p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point &p) { return Point(x - p.x, y - p.y); }
    Point operator*(double a) { return Point(a * x, a * y); }
    Point operator/(double a) { return Point(x / a, y / a); }
    double norm() { return x * x + y * y; }
    double abs() { return sqrt(norm()); }
    bool operator<(const Point &p) const {
        return x != p.x ? x < p.x : y < p.y;
    }
    bool operator==(const Point &p) const {
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
    }
};
typedef Point Vector;
double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }   // 内积
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.y; } // 外积
// 判断a,b是否正交
bool isOrthogonal(Vector a, Vector b) { return equals(dot(a, b), 0.0); }
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
}
bool isOrthogonal(Segment a, Segment b) {
    return equals(dot(a.p2 - a.p1, b.p2 - b.p1), 0.0);
}
// 判断a,b是否平行
bool isParallel(Vector a, Vector b) { return equals(cross(a, b), 0.0); }
bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
}
bool isParallel(Segment a, Segment b) {
    return equals(cross(a.p2 - a.p1, b.p2 - b.p1), 0.0);
}
// 线段声明
struct Segment {
    Point p1, p2;
};
typedef Segment Line;
// 点p在线段s的投影
Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / base.norm();
    Point tmp = base * r;
    return s.p1 + tmp;
}
// 点p关于线段s为对称轴对称的点
Point reflect(Segment s, Point p) {
    Point tmp = (project(s, p) - p) * 2.0;
    return p + tmp;
}
// 两点间的距离
double getDistance(Point a, Point b) { return (a - b).abs(); }
// 直线l与点p的距离
double getDistanceLP(Line l, Point p) {
    return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}
// 线段s与点p的距离
double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0)
        return (p - s.p1).abs();
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0)
        return (p - s.p2).abs();
    return getDistanceLP(s, p);
}
// 逆时针方向
const int COUNTER_CLOCKWISE = 1; // p0, p1, p2 成逆时针方向
const int CLOCKWISE = -1;        // p0, p1, p2 成顺时针方向
const int ONLINE_BACK = 2;       // p2, p0, p1 依次排列在一条直线上
const int ONLINE_FRONT = -2;     // p0, p1, p2 依次排列在同一条直线上
const int ON_SEGMENT = 0;        // p2在线段p0p1上
int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > EPS)
        return COUNTER_CLOCKWISE;
    if (cross(a, b) < -EPS)
        return CLOCKWISE;
    if (dot(a, b) < -EPS)
        return ONLINE_BACK;
    if (a.norm() < b.norm())
        return ONLINE_FRONT;
    return ON_SEGMENT;
}
// 判断线段p1p2和p3p4相交
bool intersect(Point p1, Point p2, Point p3, Point p4) {
    return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
            ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}
bool intersect(Segment s1, Segment s2) {
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
// 线段s1与线段s2的距离
double getDistance(Segment s1, Segment s2) {
    if (intersect(s2, s1))
        return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
// 线段s1与线段s2的交点
Point getCrossPoint(Segment s1, Segment s2) {
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    Point tmp = (s1.p2 - s1.p1) * t;
    return s1.p1 + tmp;
}
class Circle {
  public:
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};
typedef vector<Point> Polygon;
// 圆c与直线l的交点（有交点的情况下）
pair<Point, Point> getCrossPoints(Circle c, Line l) {
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
    double base = sqrt(c.r * c.r - (pr - c.c).norm());
    Point t = e * base;
    return make_pair(pr + t, pr - t);
}
// 圆c1与圆c2的交点(有交点的情况下)
double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double r) { return Point(cos(r) * a, sin(r) * a); }

pair<Point, Point> getCrossPoints(Circle c1, Circle c2) {
    double d = (c1.c - c2.c).abs();
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    double t = arg(c2.c - c1.c);
    Point tmp1 = polar(c1.r, t + a);
    Point tmp2 = polar(c1.r, t - a);
    return make_pair(c1.c + tmp1, c1.c + tmp2);
}