#include <cstdio>
#include <algorithm>

typedef std::pair<int, int> P;

P arr[100001];

bool comp(const P& a, const P& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

int main() {
	int N;
	int cnt = 1;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
	}
	std::sort(arr, arr + N, comp);


	int curr = arr[0].second;
	for (int i = 1; i < N; i++) {
		if (curr <= arr[i].first) {
			curr = arr[i].second;
			cnt++;
		}
	}

	printf("%d", cnt);
}