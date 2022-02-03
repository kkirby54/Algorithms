#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
const int INF = 987654321;
using namespace std;
int N, M, broken[10];
//bool visited[9999999];

int nDigit;
int ret = INF;

int useCnt = 0;
int usable[10];

// digit이 nDigit보다 -1이거나, +1이어야 함.
void dfs(int curr, int digit, bool isStart) {
	if (!isStart) {
		if (curr == N) {
			ret = min(ret, digit);
			return;
		}
		// 직접 ++이나 --로 구한다.
		if (digit - nDigit >= -1 && digit - nDigit <= 1) {

			if (ret > abs(curr - N) + digit) {
				ret = abs(curr - N) + digit;
				//printf("%d에서 %d로 갱신\n", curr, ret);
			}
			// 지금 digit이 더 크다면, 더 최적화 불가능.
			if (digit > nDigit)
				return;
		}
	}

	for (int i = 0; i < 10; i++) {
		if (usable[i]) {
			// 그럼 curr에다가 그걸 더해
			int next = curr * 10 + i;
			dfs(next, digit + 1, false);
		}
	}

}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < 10; i++) usable[i] = true;

	for (int i = 0; i < M ; i++) {
		scanf("%d", broken + i);
		usable[broken[i]] = false;
	}
	
	int tmp = N;
	while (tmp) {
		nDigit++;
		tmp /= 10;
	}
	// 일단 0으로 시작하고 버튼을 누르는 걸로 하자.
	// => but, 그렇게 하면 0으로 못 쓰는 경우 처리 못함.
	// 따라서 visited 배열 없애고 그냥 raw하게 함.
	// 여기서는 사실 visited가 큰 의미가 없음.
	dfs(0, 0, true);

	// 또 처음 시작점인 100에서 시작할 수도 있음.
	ret = min(ret, abs(100 - N));
	printf("%d\n", ret);
}