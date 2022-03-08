#include <cstdio>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

int A, B;
queue<long long> Q;
unordered_set<long long> S;

int main() {
	scanf("%d %d", &A, &B);

	int level = 1;

	Q.push(A);
	S.insert(A);
	while (!Q.empty()) {
		int qSize = Q.size();
		for (int k = 0; k < qSize; k++) {
			long long curr = Q.front();
			Q.pop();

			if (curr > 1000000000) continue;
			if (curr == B) {
				printf("%d\n", level);
				return 0;
			}

			long long next = curr * 10 + 1;

			if (S.find(next) == S.end()) {
				S.insert(next);
				Q.push(next);
			}
			
			next = curr * 2;
			if (S.find(next) == S.end()) {
				S.insert(next);
				Q.push(next);
			}

		}
		level++;
	}
	printf("-1");
}