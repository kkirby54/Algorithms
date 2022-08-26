#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

struct Group {
	int a, b, c;

	bool operator<(const Group& g) const {
		if (a == g.a) {
			if (b == g.b)
				return c < g.c;
			return b < g.b;
		}
		return a < g.a;
	}
};

int A, B, C;
set<Group> visited;

Group getSorted(int a, int b, int c) {
	int maxVal = max(c, max(a, b));
	int minVal = min(c, min(a, b));

	return { minVal, a + b + c - minVal - maxVal, maxVal };
}

int main() {
	scanf("%d %d %d", &A, &B, &C);

	visited.insert(getSorted(A,B,C));
	queue<Group> Q;
	Q.push(getSorted(A, B, C));
	int level = 0;

	while (!Q.empty()) {
		int currA = Q.front().a;
		int currB = Q.front().b;
		int currC = Q.front().c;
		Q.pop();

		if (currA == currB && currB == currC) {
			printf("1");
			return 0;
		}

		// A vs B
		Group ret;
		if (currA < currB) {
			ret = getSorted(currA + currA, currB - currA, currC);
			if (visited.find(ret) == visited.end()) {
				visited.insert(ret);
				Q.push(ret);
			}
		}

		// B vs C
		if (currB < currC) {
			ret = getSorted(currA, currB + currB, currC - currB);
			if (visited.find(ret) == visited.end()) {
				visited.insert(ret);
				Q.push(ret);
			}
		}

		// A vs C
		if (currA < currC) {
			ret = getSorted(currA + currA, currB, currC - currA);
			if (visited.find(ret) == visited.end()) {
				visited.insert(ret);
				Q.push(ret);
			}
		}
	}

	printf("0");
}