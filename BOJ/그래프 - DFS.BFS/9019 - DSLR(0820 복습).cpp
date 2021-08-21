#include <cstdio>
#include <algorithm>
#include <functional>
#include <queue>
#include <stack>
using namespace std;
typedef pair<int, int> P;

int T, A, B;
bool visited[10000];
P previous[10000];
char getDSLR[] = { 'D','S','L','R' };

int func(int a, int opr) {
	if (opr == 0) return (2 * a % 10000);
	else if (opr == 1) return (a + 9999) % 10000;
	else if (opr == 2) return (a * 10) % 10000 + a / 1000;
	else return a % 10 * 1000 + (a / 10);
}


int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &A, &B);
		fill(visited, visited + 10000, false);
		memset(previous, 0, sizeof(previous));

		// A -> B로 가야한다.
		queue<int> Q;
		Q.push(A);
		visited[A] = true;
		bool isFound = false;
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			//printf("현재 : %d\n", curr);
			if (curr == B) {
				isFound = true;
				
				stack<char> S;
				while (curr != A) {
					S.push(getDSLR[previous[curr].second]);
					curr = previous[curr].first;
				}
				while (!S.empty()) {
					printf("%c", S.top());
					S.pop();
				}
				puts("");
				break;
			}

			for (int i = 0; i < 4; i++) {
				int next = func(curr, i);

				if (visited[next]) continue;

				previous[next].first = curr;
				previous[next].second = i;
				visited[next] = true;
				Q.push(next);
			}

			if (isFound) break;
		}
	}

}