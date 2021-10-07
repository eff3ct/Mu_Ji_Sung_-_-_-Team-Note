//have to include this header
#include <vector>

using namespace std;
typedef long long ll;

typedef struct _Point {
    int x;
    int y;
} Point;

//should define these functions(implemented in convex hull source code)
Point getVector(const Point& A, const Point& B);
int ccw(const Point& v, const Point& u);
int ccw(const Point& A, const Point& B, const Point& C);

bool operator<=(const Point A, const Point B) {
    if(A.x < B.x) return true;
    else if(A.x == B.x && A.y <= B.y) return true;
    else return false;
}

//cross test
bool isCross(const Point& A, const Point& B, const Point& C, const Point& D) {
    if(ccw(A, B, C) * ccw(A, B, D) == 0 && ccw(C, D, A) * ccw(C, D, B) == 0) {
        Point _A(A), _B(B), _C(C), _D(D);
        if(_B <= _A) swap(_A, _B);
        if(_D <= _C) swap(_C, _D);

        if(_A <= _D && _C <= _B) return true;
        else return false;
    }
    else if(ccw(A, B, C) * ccw(A, B, D) <= 0 && ccw(C, D, A) * ccw(C, D, B) <= 0) return true;
    else return false;
}