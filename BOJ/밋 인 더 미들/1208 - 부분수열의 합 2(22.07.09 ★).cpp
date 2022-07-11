#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>

int N, S, arr[40];
int isInUpper[4000005];
int isInLower[4000005];

void backtrackUpper(int curr, int sum) {
	if (curr == (N / 2)) {
		isInUpper[sum + 2000000]++;
		return;
	}

	backtrackUpper(curr + 1, sum);
	backtrackUpper(curr + 1, sum + arr[curr]);

}

void backtrackLower(int curr, int sum) {
	if (curr == N) {
		isInLower[sum + 2000000]++;
		return;
	}

	backtrackLower(curr + 1, sum);
	backtrackLower(curr + 1, sum + arr[curr]);

}


int main() {
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	backtrackUpper(0, 0);
	backtrackLower(N / 2, 0);

	long long ret = 0;
	for (int i = -2000000; i <= 2000000; i++) {
		// i와 S - i가 있는지 확인한다.
		if (S - i + 2000000 < 0 || S - i + 2000000 > 4000000) continue;

		if (isInUpper[i + 2000000] && isInLower[S - i + 2000000]) {

			ret += (1LL * isInUpper[i + 2000000] * isInLower[S - i + 2000000]);
			//printf("%d vs %d로 가능\n", i, S - i);
		}

	}
	// S가 0이었다면 아무 것도 포함안하는 경우 1개 빼기.
	if (S == 0) ret--;

	printf("%lld\n", ret);
}