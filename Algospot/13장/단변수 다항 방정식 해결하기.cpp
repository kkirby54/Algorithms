#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int C, N;
const double L = 25;

// poly를 미분한 결과를 벡터에 담아 리턴
vector<double> differentiate(const vector<double>& poly) {
	vector<double> ret;

	double MxDegree = poly.size() - 1;
	for (int i = 0; i < MxDegree; i++) {
		ret.push_back((MxDegree - i) * poly[i]);
	}

	return ret;
}

// 1,2차 방정식이면 푼다.
vector<double> solveNaive(const vector<double>& poly) {
	vector<double> ret;

	// 1차 방정식
	if (poly.size() == 2) {
		// poly[0]x + poly[1] = 0;
		ret.push_back(-poly[1] / poly[0]);
	}
	// 2차 방정식
	else {
		// poly[0], poly[1], poly[2].
		double F = -1 * poly[1] / (2 * poly[0]);
		double S = (sqrt((poly[1] * poly[1]) - (4 * poly[0] * poly[2]))) / (2 * poly[0]);
		ret.push_back(F - S);
		ret.push_back(F + S);
	}
	
	return ret;
}

// poly(x0)의 결과를 리턴
double evaluate(const vector<double>& poly, double x0) {

	double ret = 0;
	double MxDegree = poly.size() - 1;
	for (int i = 0; i < poly.size(); i++) {
		ret += (pow(x0, (MxDegree - i)) * poly[i]);
	}

	return ret;
}

vector<double> solve(const vector<double>& poly) {
	// poly의 차수가 2차면 그냥 풀어도 됨.
	if (poly.size() <= 3) {
		return solveNaive(poly);
	}
	// 아니면 미분해서 찾아야 돼.
	// 재귀로 poly를 미분한 애의 극값을 찾아서 extremes에 넣는다.
	vector<double> derivative = differentiate(poly);
	vector<double> extremes = solve(derivative);
	vector<double> ret; // 결과 담을 배열.

	// 여기에 가장 끝점인 -L-1과 L+1을 넣는다.
	extremes.insert(extremes.begin(), -L - 1);
	extremes.insert(extremes.end(), L + 1);

	// 재귀로 자동으로 극값이 나왔다고 그럼 이 극값에 대해서
	// 이분 탐색을 돌려야 함.

	// extremes에 있는 극값들에 대해서,
	double x1, x2, y1, y2;
	for (int i = 0; i < extremes.size() - 1; i++) {
		x1 = extremes[i], x2 = extremes[i + 1];
		y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);

		// 일단 y1과 y2의 부호 같으면 그냥 continue. 해가 없다는 뜻임.
		if (y1 * y2 > 0) continue;

		// 초기 조건. 무조건 y1 <= 0 < y2로 한다.
		// 이러면 x1, x2도 바꿔준다.
		if (y1 > y2) {
			swap(y1, y2);
			swap(x1, x2);
		}

		// 이제 이 두 좌표를 가지고 이분 탐색 돌린다.
		for (int k = 0; k < 100; k++) {
			double mx = (x1 + x2) / 2;
			double my = evaluate(poly, mx);

			if (my > 0) {
				x2 = mx;
			}
			else {
				x1 = mx;
			}
		}

		ret.push_back((x1 + x2) / 2);
	}

	sort(ret.begin(), ret.end());
	return ret;
}


int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		vector<double> coefficient(N+1);

		for (int i = 0; i < N + 1; i++)
			scanf("%lf", &coefficient[i]);
		
		vector<double> ans = solve(coefficient);
		for (auto e : ans) {
			printf("%.10lf ", e);
		}
		puts("");
		
	}

}