#include <cstdio>
#include <algorithm>

int N;
int dp[31];

int tile(int curr) {
	if (curr == 2) return 3;
	if (curr == 0) return 1;
	//if (curr == 4) return 11;
	if (curr % 2 == 1) return 0;

	int& ret = dp[curr];
	if (ret) return ret;

	ret = 3 * tile(curr - 2);

	for (int i = 4; curr - i >= 0; i += 2) {
		ret += 2 * tile(curr - i);
	}
	
	return ret;
}

int main() {
	scanf("%d", &N);

	printf("%d", tile(N));


}