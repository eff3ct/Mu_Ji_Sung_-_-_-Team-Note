#include <vector>

using namespace std;
typedef long long ll;

typedef struct _Point {
    int x;
    int y;
} Point;

using namespace std;

//should be defined
int ccw(const Point& v, const Point& u);

double rotCalipers(vector<Point>& convexHull);
    double ret = 987654321.0;
    int b = 1, f = 0;
    int s = (int)convexHull.size();
    bool flag = false;
    while(true) {
        Point frontVector = getVector(convexHull[f], convexHull[(f + 1) % s]);
        Point backVector = getVector(convexHull[b], convexHull[(b + 1) % s]);

        ret = max(ret, getDist(convexHull[f], convexHull[b]));

        if(ccw(frontVecTor, backVector) > 0) b = (b + 1) % s;
        else {
            f = (f + 1) % s;
            flag = true;
        }

        if(f == 0 && flag) break;
    }
}