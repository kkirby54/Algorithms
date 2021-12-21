//#include <cstdio>
//#include <algorithm>
//#include <vector>
//#include <cstring>
//
//int N, L, I;
//int dp[32][32];
//int result[31];
//
//// l개 이하
//int binary(int n, int l) {
//	if (n == 0 || l == 0) return 1;
//	int& ret = dp[n][l];
//	if (ret != -1) return ret;
//
//	ret = binary(n - 1, l);
//	if (l > 0)
//		ret += binary(n - 1, l - 1);
//
//	return ret;
//}
//
//// k번째 수를 찾아야 한다.
//void skip(int n, int l, int k, int p) {
//	if (n == 0) return;
//	if (l == 0) {
//		for (int i = 0; i < n; i++) {
//			result[p + i] = 0;
//		}
//		return;
//	}
//
//	// N자리 중 L개 이하로 1을 써서 만든 이진수 = binary(N,L)
//	// = binary(N-1, L-1) (1을 씀)
//	// + binary(N-1, L) (0을 씀)
//
//	int pivot = binary(n - 1, l);
//	if (pivot > k) {
//		// 그럼 왼쪽 서브트리로.
//		result[p] = 0;
//		skip(n-1, l, k, p+1);
//	}
//	else {
//		result[p] = 1;
//		skip(n - 1, l-1, k - pivot, p + 1);
//
//	}
//
//}
//
//int main() {
//	scanf("%d %d %d", &N, &L, &I);
//	memset(dp, -1, sizeof(dp));
//	I--;
//	//printf("%d개 이하의 %d자리 이진수의 개수 : %d\n", L, N, binary(N, L));
//
//	skip(N, L, I, 0);
//	for (int i = 0; i < N; i++) {
//		printf("%d", result[i]);
//	}
//}

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

int T, K, cost[i];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &K);
		for (int i = 0; i < K; i++) {
			scanf("%d", cost + i);

		}


	}

}