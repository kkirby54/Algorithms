#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char B[500001];
char S[100001];
int fail[100001];

int T;

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf(" %s", B);
		getchar();
		scanf(" %s", S);
		int ret = 0;
		int N = strlen(B);
		int M = strlen(S);
		// 일단 S의 failure 배열을 채운다.
		for (int i = 0; i < M; i++)
			fail[i] = 0;

		for (int i = 1, j = 0; i < M; i++) {
			while (j > 0 && S[i] != S[j]) {
				j = fail[j - 1];
			}

			if (S[i] == S[j])
				fail[i] = ++j;
		}

		// KMP 알고리즘 적용
		for (int i = 0, j = 0; i < N; i++) {
			while (j > 0 && B[i] != S[j]) {
				j = fail[j - 1];
			}

			// 같다면,
			if (B[i] == S[j]) {
				if (j == M - 1) {
					//printf("i = %d에서 같\n", i);
					ret++;
					j = fail[j];
				}
				else j++;
			}
		}

		printf("#%d %d\n", t, ret);

	}

}