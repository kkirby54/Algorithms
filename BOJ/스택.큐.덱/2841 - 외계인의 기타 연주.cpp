#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;
int N, P, melody, flat;
int ret = 0;
stack<int> S[7];

int main() {
	scanf("%d %d", &N, &P);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &melody, &flat);

		while (!S[melody].empty() && S[melody].top() > flat) {
			S[melody].pop();
			ret++;
		}
		if (S[melody].empty() || S[melody].top() != flat) {
			S[melody].push(flat);
			ret++;
		}
	}
	printf("%d\n", ret);
}