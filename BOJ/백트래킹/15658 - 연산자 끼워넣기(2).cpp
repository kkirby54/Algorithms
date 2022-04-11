#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 1000000000;

int N, arr[11];
int opr[4];
int minVal = INF, maxVal = -INF;

int calc(int a, int b, int funcNumber) {
	switch (funcNumber)
	{
	case 0: return a + b;
	case 1: return a - b;
	case 2: return a * b;
	case 3: return a / b;
	default:
		break;
	}
	return 0;
}

void solve(int curr, int cnt) {
	if (cnt == N - 1) {
		minVal = min(minVal, curr);
		maxVal = max(maxVal, curr);

		return;
	}

	// 써본다.
	for (int i = 0; i < 4; i++) {
		if (opr[i]) {
			opr[i]--;
			solve(calc(curr, arr[cnt + 1], i), cnt + 1);
			opr[i]++;
		}

	}


}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d ", arr + i);
	}
	for (int i = 0; i < 4; i++) {
		scanf("%d", opr + i);
	}

	solve(arr[0], 0);

	printf("%d\n%d", maxVal, minVal);
}