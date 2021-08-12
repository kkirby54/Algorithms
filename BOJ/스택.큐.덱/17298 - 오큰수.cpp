#include <cstdio>
#include <stack>

using namespace std;
int N, arr[1000000];
int ret[1000000];

int main() {
	scanf("%d", &N);
	stack<int> S;
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);

		// 비어 있거나,
		// 현재 값 < arr[S.top]
		while (!S.empty() && arr[S.top()] < arr[i]) {
			ret[S.top()] = arr[i];
			S.pop();
		}

		S.push(i);
	}
	for (int i = 0; i < N; i++) {
		printf("%d ", ret[i] ? ret[i] : -1);
	}

}