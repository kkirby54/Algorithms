#include <cstdio>
#include <algorithm>
#include <cstring>

int N, M, S, E;
int arr[2000];

int dp[2001][2001];

int felindrome(int s, int e) {
	int& ret = dp[s][e];
	if (ret != -1) return ret;

	if (s == e) return ret = 1;
	if (s + 1 == e) return ret = arr[s] == arr[e];

	// 일단 arr[s] == arr[e]여야 함.
	if (arr[s] != arr[e]) return ret = 0;
	else {
		// 같으면, s+1, e-1로 확인.
		return ret = felindrome(s + 1, e - 1);
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	scanf("%d", &M);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &S, &E);
		S--; E--;
		printf("%d\n", felindrome(S, E));
	}


}