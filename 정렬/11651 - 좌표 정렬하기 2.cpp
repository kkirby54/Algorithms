#include <cstdio>
#include <algorithm>

typedef std::pair<int, int> P;

int N;
P points[100000];

bool comp(const P& a, const P& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &points[i].first, &points[i].second);
	}
	std::sort(points, points+N, comp);
	for (int i = 0; i < N; i++) {
		printf("%d %d\n", points[i].first, points[i].second);
	}

}