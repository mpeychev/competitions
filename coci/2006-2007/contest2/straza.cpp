#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define x first
#define y second
#define pb push_back
#define mp make_pair

using namespace std;

const double eps = 1e-9;

typedef pair<double, double> Point;
typedef pair<Point, Point> Segment;

struct line {
    double A, B, C;

    line() {}
    line(double _A, double _B, double _C): A(_A), B(_B), C(_C) {}
};

int n;
vector< Segment > seg;
line coef[32];
vector< Point > vec;
bool ma3x[1024][1024];
int ans;

inline bool eq(double a, double b) {
    return fabs(a - b) < eps;
}

inline double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline int det(Point a, Point b, Point c) {
    double d = (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
    if(d > eps) return 1;
    if(d < -eps) return -1;
    return 0;
}

bool intersect(Segment a, Segment b) {
    if(det(a.x, a.y, b.x) * det(a.x, a.y, b.y) != -1) return false;
    if(det(b.x, b.y, a.x) * det(b.x, b.y, a.y) != -1) return false;
    return true;
}

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        Segment s;
        scanf("%lf %lf %lf %lf", &s.x.x, &s.x.y, &s.y.x, &s.y.y);
        seg.pb(s);
    }
}

void add(Point p) {
    for(int i = 0; i < vec.size(); i ++)
        if(eq(vec[i].x, p.x) && eq(vec[i].y, p.y))
            return;
    vec.pb(p);
}

bool lie(Point a, Segment b) {
    if(det(a, b.x, b.y) != 0) return false;
    return eq(dist(a, b.x) + dist(a, b.y), dist(b.x, b.y));
}

bool cmp(Point a, Point b) {
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    return a.y < b.y;
}

bool merge() {
    for(int i = 0; i < seg.size(); i ++)
        for(int j = i + 1; j < seg.size(); j ++)
            if(det(seg[i].x, seg[j].x, seg[j].y) == 0 && det(seg[i].y, seg[j].x, seg[j].y) == 0 &&
               (lie(seg[i].x, seg[j]) || lie(seg[i].y, seg[j]))) {
                Point group[4];
                group[0] = seg[i].x;
                group[1] = seg[i].y;
                group[2] = seg[j].x;
                group[3] = seg[j].y;
                sort(group, group + 4, cmp);
                seg.pb(mp(group[0], group[3]));
                seg.erase(seg.begin() + i);
                seg.erase(seg.begin() + j - 1);
                return true;
            }
    return false;
}

void solve() {
    for(int i = 0; i < n; i ++) {
        add(seg[i].x);
        add(seg[i].y);
    }

    for(int i = 0; i < n; i ++)
        coef[i] = line(seg[i].first.y - seg[i].second.y, seg[i].second.x - seg[i].first.x,
                       seg[i].first.x * seg[i].second.y - seg[i].second.x * seg[i].first.y);

    for(int i = 0; i < n; i ++)
        for(int j = i + 1; j < n; j ++)
            if(intersect(seg[i], seg[j])) {
                if(!eq(coef[i].A, 0.0)) {
                    double Y = (coef[j].A * coef[i].C - coef[j].C * coef[i].A) /
                               (coef[i].A * coef[j].B - coef[j].A * coef[i].B);
                    double X = (-coef[i].C - coef[i].B * Y) / coef[i].A;
                    add(mp(X, Y));
                }
                else {
                    double Y = -coef[i].C / coef[i].B;
                    double X = (-coef[j].C - coef[j].B * Y) / coef[j].A;
                    add(mp(X, Y));
                }
            }

    for( ; ; ) {
        if(!merge())
            break;
    }

    for(int i = 0; i < vec.size(); i ++)
        for(int j = i + 1; j < vec.size(); j ++)
            for(int k = 0; k < seg.size(); k ++)
                if(lie(vec[i], seg[k]) && lie(vec[j], seg[k]))
                    ma3x[i][j] = ma3x[j][i] = 1;

    for(int i = 0; i < vec.size(); i ++)
        for(int j = i + 1; j < vec.size(); j ++)
            if(ma3x[i][j])
                for(int k = j + 1; k < vec.size(); k ++)
                    if(ma3x[i][k] && ma3x[j][k] && det(vec[i], vec[j], vec[k]) != 0)
                        ans ++;

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
