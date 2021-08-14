#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, p, a, b, root, maxWidth;
int parent[10001], lc[10001], rc[10001];
int leftest[10001], rightest[10001]; // i번째 레벨에 대해, 가장 왼쪽 or 오른쪽에 있는 번호 저장.
int loc[10001]; // i번째 노드들의 좌표 평면 상의 위치를 저장한다.

// leftCnt, 내 왼쪽에 있는 노드들의 개수.
int dfs(int curr, int leftCnt, int depth) {

	int leftNums = 0;
	// curr의 왼쪽이 있다면 내려가서 재귀
	if (lc[curr] != -1) {
		leftNums += dfs(lc[curr], leftCnt, depth + 1) + 1;
	}
	if (loc[curr] != -1)
		loc[curr] = leftNums + leftCnt + 1;

	leftest[depth] = min(leftest[depth], loc[curr]);
	rightest[depth] = max(rightest[depth], loc[curr]);
	maxWidth = max(maxWidth, rightest[depth] - leftest[depth] + 1);

	int rightNums = 0;
	// curr의 오른쪽
	if (rc[curr] != -1) {
		rightNums += dfs(rc[curr], loc[curr], depth + 1) + 1;
	}

	return leftNums + rightNums;
}


int main() {
	scanf("%d", &N);
	fill(parent, parent + N + 1, -1);
	fill(lc, lc + N + 1, -1);
	fill(rc, rc + N + 1, -1);
	fill(leftest, leftest + N + 1, 10000);
	fill(rightest, rightest + N + 1, 0);


	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &p, &a, &b);

		if (a != -1) {
			parent[a] = p;
			lc[p] = a;
		}
		if (b != -1) {
			parent[b] = p;
			rc[p] = b;
		}
	}

	for (int i = 1; i <= N; i++)
		if (parent[i] == -1) {
			root = i; break;
		}

	// 이제 루트를 찾았으니,
	// 노드의 개수를 찾아본다.
	dfs(root, 0, 1);

	//for (int i = 1; i <= N; i++) {
	//	printf("%d의 위치 : %d\n", i, loc[i]);
	//}

	int minLevel = 0;
	for (int i = 1; i <= N; i++) {
		if (maxWidth == rightest[i] - leftest[i] + 1) {
			minLevel = i;
			break;
		}
	}

	printf("%d %d\n", minLevel, maxWidth);

}