#include <cstdio>
#include <algorithm>

using namespace std;
const int MOD = 20091101;

int T, N, K, num, ret, ret2;
int pSum[100001];
long long cnt[100001] = { 1, };
int hasPair[100001];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		fill(cnt, cnt + K, 0);
		fill(pSum, pSum + N + 1, 0);
		cnt[0] = 1;
		ret = 0;
		ret2 = 0;

		for (int i = 0; i < N; i++) {
			scanf("%d", &num);
			pSum[i + 1] = (pSum[i] + num) % K;
			++(cnt[pSum[i + 1]]);
		}
		for (int i = 0; i < K; i++) {
			ret += ((cnt[i] * (cnt[i] - 1)) / 2) % MOD;
			ret %= MOD;
		}
		/*printf("pSum : ");
		for (int i = 0; i <= N; i++) printf("%d ", pSum[i]);
		puts("");*/
		
		// pSum[i] = 0 이거나
		// hasPair[ ] = 2;
		fill(hasPair, hasPair + K + 1, 0);
		for (int i = 0; i <= N; i++) {
			if (++hasPair[pSum[i]] == 2) {
				ret2++;
				fill(hasPair, hasPair + K + 1, 0);
				hasPair[pSum[i]] = 1;
			}
		}


		printf("%d %d\n", ret, ret2);
	}

}