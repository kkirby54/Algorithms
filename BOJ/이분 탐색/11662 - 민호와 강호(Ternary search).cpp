#include <cstdio>
#include <cmath>
#include <algorithm>

int x[4], y[4];

double getDist(double a, double b, double c, double d) {
	return (c - a) * (c - a) + (d - b) * (d - b);
}

double get_point(double a, double b, double percentage) {
	return a + (b - a) * (percentage / 100);
}

int main() {
	for (int i = 0; i < 4; i++) {
		scanf("%d %d", x + i, y + i);
	}

	double s = 0, e = 100;
	double ret = 1000000000;

	while (e - s >= 1e-6) {
		//printf("퍼센트 : %lf, %lf\n", s, e);
		double p = (2 * s + e) / 3;
		double q = (2 * e + s) / 3;

		double PMx = get_point(x[0], x[1], p);
		double PMy = get_point(y[0], y[1], p);
		double PKx = get_point(x[2], x[3], p);
		double PKy = get_point(y[2], y[3], p);

		double QMx = get_point(x[0], x[1], q);
		double QMy = get_point(y[0], y[1], q);
		double QKx = get_point(x[2], x[3], q);
		double QKy = get_point(y[2], y[3], q);

		double PDistance = getDist(PMx, PMy, PKx, PKy);
		double QDistance = getDist(QMx, QMy, QKx, QKy);

		ret = std::min(ret, std::min(PDistance, QDistance));

		// P가 더 크면 
		if (PDistance >= QDistance) {
			s = p;
		}
		else e = q;
	}

	printf("%.6lf", sqrt(ret));
}