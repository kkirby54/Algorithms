#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;

int T, N, a, b;

int main() {
	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		P students[400];

		for (int i = 0; i < N; i++) {
			scanf("%d %d", &a, &b);
			int minV = min(a, b);
			int maxV = a + b - minV;
			if (minV % 2 == 0) minV--;
			if (maxV % 2 == 1) maxV++;
			students[i].first = minV;
			students[i].second = maxV;
		}
		sort(students, students + N);


		int ret = 0;

		bool isDone[401] = { 0 };
		for (int i = 0; i < N; i++) {
			if (isDone[i]) continue;
			ret++;
			isDone[i] = true;
			int currEnd = students[i].second;

			for (int j = i + 1; j < N; j++) {
				if (isDone[j]) continue;

				if (currEnd < students[j].first) {
					currEnd = students[j].second;
					isDone[j] = true;
				}
			}
		}
		printf("#%d %d\n", t, ret);
	}

}