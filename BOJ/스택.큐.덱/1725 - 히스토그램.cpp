#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;
int N, arr[100000];

int main() {
	scanf("%d", &N);
	stack<int> S;
	int ret = 0;

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);

		// 스택에 있는 걸 보면서,
		// 지금보다 높거나 같은 사각형이 스택에 들어있으면 계속 시행한다.
		// 지금 들어온 i번째 사각형이, 스택에 존재하는 모든 사각형의 right[i]가 된다. (오른쪽을 가로막음)
		while (!S.empty() && arr[S.top()] >= arr[i]) {
			// curr번째 사각형을 처리한다.
			// 이 말은, left[curr]과 right[curr]을 알아야 한다는 말과 같다.
			// right[curr] = i이므로, left[curr]의 값을 알아야 한다.
			int curr = S.top();
			S.pop();

			// 스택이 비어있다면, 왼쪽에 가로막는 사각형이 없다. 즉 left[curr] = 0. 즉, 0번 인덱스부터 계산.
			if (S.empty()) ret = max(ret, arr[curr] * i);
			// 스택에 요소가 있다면, 그 요소가 바로 left[curr]이 된다.
			// 이유는 스택의 요소들은 항상 높이 순으로 저장되기 때문에,
			// S.top()의 높이는 현재 curr의 높이보다 항상 작다. 그렇게 스택에 넣었기 때문임.
			else ret = max(ret, arr[curr] * (i - S.top() - 1));
		}
		
		S.push(i);
	}
	// 마지막까지 push한 이후에도
	// 남아있는 요소들을 pop하면서 넓이를 갱신한다.
	while (!S.empty()) {
		int curr = S.top();
		S.pop();
		if (S.empty()) ret = max(ret, arr[curr] * N);
		else ret = max(ret, arr[curr] * (N - S.top() - 1));
	}

	printf("%d\n", ret);
}