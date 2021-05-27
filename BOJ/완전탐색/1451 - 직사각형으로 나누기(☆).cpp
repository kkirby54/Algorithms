#include <cstdio>
#include <algorithm>

int N, M, tmp;
long long prefix[105][105] = { 0 };

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &tmp);
			prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + tmp;
		}
	}

	long long ret = 0;
	long long s1, s2, s3;
	// 1번
	// prefix 배열을 보면..
	// prefix[?][M] 배열들에 다 적혀있음.

	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			s1 = prefix[i][M];
			s2 = prefix[j][M] - prefix[i][M];
			s3 = prefix[N][M] - s1 - s2;
			ret = std::max(ret, s1 * s2 * s3);
		}
	}

	// 2번 모양
	for (int i = 1; i < M; i++) {
		for (int j = i + 1; j < M; j++) {
			s1 = prefix[N][i];
			s2 = prefix[N][j] - prefix[N][i];
			s3 = prefix[N][M] - s1 - s2;

			ret = std::max(ret, s1 * s2 * s3);
		}
	}

	// 3번 모양
	for (int i = 1; i < N; i++) {
		s1 = prefix[i][M];

		for (int j = 1; j < M; j++) {
			s2 = prefix[N][j] - prefix[i][j];
			s3 = prefix[N][M] - s1 - s2;

			ret = std::max(ret, s1 * s2 * s3);
		}
	}

	// 4번 모양
	for (int i = 1; i < N; i++) {
		s1 = prefix[N][M] - prefix[i][M];
		for (int j = 1; j < M; j++) {
			s2 = prefix[i][j];
			s3 = prefix[N][M] - s1 - s2;

			ret = std::max(ret, s1 * s2 * s3);
		}
	}

	// 5번
	for (int i = 1; i < M; i++) {
		s1 = prefix[N][i];

		for (int j = 1; j < N; j++) {
			s2 = prefix[j][M] - prefix[j][i];
			s3 = prefix[N][M] - s1 - s2;

			ret = std::max(ret, s1 * s2 * s3);
		}
	}

	// 6번

	for (int i = 1; i < M; i++) {
		s1 = prefix[N][M] - prefix[N][i];
		for (int j = 1; j < N; j++) {
			s2 = prefix[j][i];
			s3 = prefix[N][M] - s1 - s2;

			ret = std::max(ret, s1 * s2 * s3);
		}
	}


	printf("%lld", ret);
}