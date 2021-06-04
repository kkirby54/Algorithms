#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

const int INF = 2000000000;
using namespace std;

struct Point {
	double r, c;
};

int C, N, M;
vector<Point> hull1, hull2;
vector<pair<Point, Point>> upper, lower;

// hull 껍질을 위 껍질, 아래 껍질로 나눈다.
void decompose(const vector<Point>& hull) {
	// hull[i]와 hull[i+1]
	int len = hull.size();
	for (int i = 0; i < len; i++) {
		// x1 < x2 이러면 lower.
		if (hull[i].r < hull[(i + 1) % len].r)
			lower.push_back(make_pair(hull[i], hull[(i + 1) % len]));
		else
			upper.push_back(make_pair(hull[i], hull[(i + 1) % len]));
	}
}

// min(up) - max(down) 하면 됨.

// x 좌표에서의 y좌표 구하는 함수
double at(const Point& a, const Point& b, double x) {
	double dy = a.c - b.c, dx = a.r - b.r;
	return a.c + (dy * (x - a.r) / dx);
}

// x가 a,b를 잇는 선분에 포함되는지 확인
bool between(const Point& a, const Point& b, double x) {
	return (a.r <= x && x <= b.r) || (b.r <= x && x <= a.r);
}

// x = x에서의 최대값을 리턴한다.
double vertical(double x) {

	double MinUp = INF;
	double MaxDown = -INF;

	// MinUp을 구한다.
	for (int i = 0; i < upper.size(); i++) {
		// 근데 x가 선분 사이에 있어야만 함.
		if (between(upper[i].first, upper[i].second, x))
			MinUp = min(MinUp, at(upper[i].first, upper[i].second, x));
	}

	// MaxDown을 구한다.
	for (int i = 0; i < lower.size(); i++) {
		if (between(lower[i].first, lower[i].second, x))
			MaxDown = max(MaxDown, at(lower[i].first, lower[i].second, x));
	}

	return MinUp - MaxDown;
}

double MinR(const vector<Point>& hull) {
	double MinVal = INF;
	for (int i = 0; i < hull.size(); i++) {
		MinVal = min(MinVal, hull[i].r);
	}
	return MinVal;
}

double MaxR(const vector<Point>& hull) {
	double MaxVal = -INF;
	for (int i = 0; i < hull.size(); i++) {
		MaxVal = max(MaxVal, hull[i].r);
	}
	return MaxVal;
}

double solve() {
	// x좌표를 기준으로 간다.
	double lo = max(MinR(hull1), MinR(hull2));
	double hi = min(MaxR(hull1), MaxR(hull2));

	if (lo > hi) return 0;

	for (int itr = 0; itr < 100; itr++) {
		double aab = (2 * lo + hi) / 3;
		double abb = (lo + 2 * hi) / 3;

		// 이러면, 
		if (vertical(aab) >= vertical(abb)) {
			hi = abb;
		}
		else lo = aab;
	}

	return max(0.0, vertical(hi));
}


int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);
		hull1.resize(N);
		hull2.resize(M);
		upper.clear(); lower.clear();

		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &hull1[i].r, &hull1[i].c);
		for (int i = 0; i < M; i++)
			scanf("%lf %lf", &hull2[i].r, &hull2[i].c);

		// 위 껍질 아래 껍질로 분해한다.
		decompose(hull1);
		decompose(hull2);

		printf("%.10lf\n", solve());

	}

}