#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int pSum[100001];

int main() {
	int N, M, num, A,B;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		pSum[i + 1] = pSum[i] + num;
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		A--; B--;
		printf("%d\n", pSum[B+1] - pSum[A]);
	}

}