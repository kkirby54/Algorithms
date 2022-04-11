#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int S[20];
int ret = 0;

bool visited[2000005];

void backtrack(int curr) {
	if (curr == N) {
		return;
	}

	// 이걸 취한다.
	ret += S[curr];
	visited[ret] = true;
	backtrack(curr + 1);
	ret -= S[curr];

	visited[ret] = true;
	backtrack(curr + 1);

}

int main() {
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		scanf("%d", S + i);
	}

	backtrack(0);

	for (int i = 1; i < 2000005; i++) {
		if (!visited[i]) {
			printf("%d\n", i);
			return 0;
		}
	}

}