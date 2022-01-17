#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

int N, A[50], B[50];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", A + i);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", B + i);
	}

	sort(A, A + N, greater<int>());
	sort(B, B + N);
	int ret = 0;
	for (int i = 0; i < N; i++) {
		ret += (A[i] * B[i]);
	}
	printf("%d", ret);
}