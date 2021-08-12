#include <cstdio>
#include <algorithm>
using namespace std;
const int MOD = 20091101;

int T, N, K, num;
int pSum[100001];
int cnt[100001];
int cnt2[100001];
long long ret1, ret2;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		fill(cnt, cnt + K, 0);
		fill(cnt2, cnt2 + K, 0);
		cnt[0] = 1;

		for (int i = 0; i < N; i++) {
			scanf("%d", &num);
			pSum[i + 1] = (pSum[i] + num) % K;
			++cnt[pSum[i + 1]];
		}

		ret1 = 0;
		// Problem 1. 한 번 주문할 때, 가능한 주문 방법?
		for (int i = 0; i < K; i++) {
			ret1 += (1LL * cnt[i] * (cnt[i] - 1) / 2) % MOD;
			ret1 %= MOD;
		}

		ret2 = 0;
		// Problem 2. 여러 번 주문할 때, 겹치지 않고 최대 몇 번?
		// pSum[]을 돌면서, i번째 나온 수를 저장한다.
		// 돌다가 j번째에 중복되는 수가 나왔다고 하자.
		// 이 의미는 [i, j-1]로 살 수 있으며, 
		// 왼쪽부터 훑으므로, 가장 먼저 마주치는 (i,j)쌍을 택하는게
		// 구간을 최대한으로 늘릴 수 있다.
		for (int i = 0; i <= N; i++) {
			if (cnt2[pSum[i]] != 0) {
				fill(cnt2, cnt2 + K, 0);
				ret2++;
			}
			cnt2[pSum[i]]++;
		}



		printf("%lld %lld\n", ret1, ret2);

	}

}