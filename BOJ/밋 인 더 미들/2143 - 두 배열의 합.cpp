#include <cstdio>
#include <map>

int T, N, M;
int Narr[1000], Marr[1000];
std::map<int, int> Map;
long long ret;

int main() {
	scanf("%d", &T);
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", Narr + i);
	}
	
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", Marr + i);
	}

	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < N; j++) {
			// Marr[i] ~ Marr[j]까지.
			sum += Narr[j];

			++(Map[sum]);
		}
	}

	// 이제 M
	for (int i = 0; i < M; i++) {
		int sum = 0;
		for (int j = i; j < M; j++) {
			sum += Marr[j];

			ret += (Map[T - sum]);
		}

	}

	printf("%lld", ret);
}