#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int INF = 987654321;

int C, N, K, M, L, tmp;
int preq_size, semester_size;

int preq[12] = { 0 };
int semester[10] = { 0 };
int dp[5000][10];

// m에 대한 비트를 카운트한다.
int bitCount(int m) {
	//return __builtin_popcount(m);
	return __popcnt(m);
}

int Graduate(int classes, int curr_sem) {
	// 종료 조건은 classes의 카운트가 K개 이상이라면
	if (bitCount(classes) >= K) {
		return 0;
	}
	if (curr_sem == M) return INF;

	int& ret = dp[classes][curr_sem];
	if (ret != -1) return ret;

	ret = INF;

	int currLessons = (semester[curr_sem]);

	// 이제 선수과목 안 들은 수업을 빼내야 한다.

	// i 과목의 선수과목은 preq[i]이라고.
	// 그럼 classes와 preq[i]를 비교하면서,
	// 그게 preq[i]가 아니라면, 얘는 못 듣는 애임.
	// i번째 과목에 대해 비트를 꺼버린다. currLessons의.
	for (int i = 0; i < N; i++) {
		if ((classes & preq[i]) != preq[i]) {
			currLessons &= ~(1 << i);
		 }
	}

	// 이 과정을 하고 나면 currLessons에는 들을 수 있는 과목들만 있다.

	for (int CLesson = currLessons; CLesson > 0; CLesson = ((CLesson - 1) & currLessons)){
		// 이 수업들을 들었으면 꺼져
		// 이게 L 초과하면 그것도 넘겨
		if (bitCount(CLesson) > L) continue;
		if ((classes & CLesson) == CLesson) continue;

		// 이제 들어보고 그리고 넘기기
		int this_semester = (classes | CLesson);
		ret = std::min(ret, Graduate(this_semester, curr_sem + 1) + 1);
	}

	ret = std::min(ret, Graduate(classes, curr_sem + 1));
	return ret;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d %d %d", &N, &K, &M, &L);

		memset(dp, -1, sizeof(dp));
		memset(preq, 0, sizeof(preq));
		memset(semester, 0, sizeof(semester));

		for (int i = 0; i < N; i++) {
			scanf("%d", &preq_size);

			for (int j = 0; j < preq_size; j++) {
				scanf("%d", &tmp);
				preq[i] |= (1 << tmp);
			}
		}

		for (int i = 0; i < M; i++) {
			scanf("%d", &semester_size);
			for (int j = 0; j < semester_size; j++) {
				scanf("%d", &tmp);
				semester[i] |= (1 << tmp);
			}

		}
		int ans = Graduate(0, 0);
		if (ans != INF) printf("%d\n", ans);
		else puts("IMPOSSIBLE");

	}
}