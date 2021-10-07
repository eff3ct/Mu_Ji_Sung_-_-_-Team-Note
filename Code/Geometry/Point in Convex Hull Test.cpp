//have to include this header
#include <vector>

using namespace std;

typedef struct _Point {
    int x;
    int y;
} Point;

Point getVector(const Point& A, const Point& B);
int ccw(const Point& v, const Point& u);
int ccw(const Point& A, const Point& B, const Point& C);

//convexHull size >= 3
bool isInside(vector<Point>& convexHull, Point& A) {
    int O = 0;
    int L = 1, R = (int)convexHull.size() - 1;
    int M = (L + R) / 2;

    Point vecOL = getVector(convexHull[O], convexHull[L]);
    Point vecOA = getVector(convexHull[O], A);
    Point vecOR = getVector(convexHull[O], convexHull[R]);
    Point vecOM = getVector(convexHull[O], convexHull[M]);

    if(ccw(vecOL, vecOA) < 0) return false;
    if(ccw(vecOR, vecOA) > 0) return false;

    while(L + 1 != R) {
        M = (L + R) / 2;
        vecOM = getVector(convexHull[O], convexHull[M]);

        if(ccw(vecOM, vecOA) > 0) L = M;
        else R = M;
    }

    if(ccw(convexHull[L], A, convexHull[R]) <= 0) return true; 
    else return false;
}