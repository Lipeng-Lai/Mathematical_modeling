#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const double pi = acos(-1.0);
const double eps = 1e-5;

double d[N], theta[N]; // 距离和角度
struct Point{ // 点类
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }

    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator * (const double &b) const { return Point(x * b, y * b); }
    Point operator / (const double &b) const { return Point(x / b, y / b); }
}p[N], ass[N];

// 理解为typedef 
using Vector = Point;

// 叉积
double cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}

struct Circle{ // 圆类
    Point O;
    double r;

    Circle() {}
    Circle(Point _O, double _r) : O(_O), r(_r) {}

    bool operator == (Circle const &b){
        return (O - b.O).norm() < eps && fabs(r - b.r) < eps;
    }
};

// id1, id2, vectex 所成角为alpha, 角顶点为vertex
struct Angle{ // 角类
    int id1, id2;
    int vertex;
    double alpha;

    Angle(int _id1, int _id2, int _ver, double _alpha){
        id1 = _id1, id2 = _id2;
        vertex = _ver, alpha = _alpha;
    }

    bool operator < (Angle &b){
        return alpha < b.alpha;
    }
};

// 若无人机到达标准位置
// id1, id2, vertex所成角(以vertex为顶点)的大小
int get_angle_ass(int id1, int vertex, int id2){
    assert(id1 != id2 && id1 != vertex && vertex != id2); // 避免共点
    if (id1 > id2) swap(id1, id2);
    if (vertex == 0)
    {
        int del = id2 - id1;
        if (del > 4) del = 9 - del;
        return 40 * del;
    }
    else if (id1 == 0)
    {
        int del = abs(id2 - vertex);
        if (del > 4) del = 9 - del;
        return (180 - 40*del) / 2;
    }
    else
    {
        int del = id2 - id1;
        if (del <= 4)
        {
            if (id1 < vertex && vertex < id2) return 180-40*del/2;
            else return 40*del/2;
        }
        else
        {
            del = 9 - del;
            if (id1 < vertex && vertex < id2) return 40*del/2;
            else return 180-40*del/2;
        }
    }
}


// id1, id2, vertex 实际所成角(以vertex为顶点)的大小
double get_angle_real(int id1, int vertex, int id2)
{
    assert(id1 != id2 & id1 != vertex && vertex != id2);
    double l1 = (p[vertex] - p[id1]).norm();
    double l2 = (p[vertex] - p[id2]).norm();
    double l3 = (p[id1] - p[id2]).norm();

    double tmp = (l1*l1 + l2*l2 - l3*l3) / (2*l1*l2);
    assert(-1.01 <= tmp && tmp <= 1.01);

    if (tmp > 1) tmp = 1;
    if (tmp < -1) tmp = -1;

    double alpha = acos(tmp);
    return alpha;
}

// P, Q, vertex 实际所成角(以vertex为顶点)的大小
double get_angle_real(Point P, Point vertex, Point Q)
{
    double l1 = (vertex - P).norm();
    double l2 = (vertex - Q).norm();
    double l3 = (P - Q).norm();

    double tmp = (l1*l1 + l2*l2 - l3*l3) / (2*l1*l2);
    assert(-1.01 <= tmp && tmp <= 1.01);

    if (tmp > 1) tmp = 1;
    if (tmp < -1) tmp = -1;

    double alpha = acos(tmp);
    return alpha;
}

int sgn(double x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

// 过点P, Q的张角为alpha的圆
Circle get_circle(int id, Point P, Point Q, double alpha)
{
    Point O, O1, O2, M;
    M = (P + Q) / 2;
    Vector v(Q - P);

    double h = v.norm() / 2 * tan(abs(pi / 2 - alpha));
    double r;

    if (abs(pi/2 - alpha) > eps) r = h / sin(pi/2 - alpha);
    else r = v.norm() / 2;
    
    v = v / v.norm() * h;
    swap(v.x, v.y);
    v.x *= -1;

    O1 = M + v, O2 = M - v;
    int f1 = sgn(cross(p[id] - P, Q - P));
    int f2 = sgn(cross(O1 - P, Q - P));

    if (alpha > pi/2)
    {
        if (f1 == f2) O = O2;
        else O = O1;
    }
    else
    {
        if (f1 == f2) O =O1;
        else O = O2;
    }
    return Circle(O, r);
}
