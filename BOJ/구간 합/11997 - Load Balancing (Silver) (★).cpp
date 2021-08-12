#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;

int N, xNum, yNum, x[1000], y[1000];
int A[1000][1000];
int pSum[1001][1001];
set<int> xSet, ySet;
unordered_map<int, int> xHash, yHash;


int getRangeSum(int x1, int y1, int x2, int y2) {
	return pSum[x2][y2] - pSum[x1][y2] - pSum[x2][y1] + pSum[x1][y1];
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", x + i, y + i);
		xSet.insert(x[i]);
		ySet.insert(y[i]);
	}

	// 좌표 압축하기. 1000000 -> 1000
	for (auto x : xSet) {
		xHash[x] = xNum++;
	}
	for (auto y : ySet) {
		yHash[y] = yNum++;
	}

	// xNum개의 서로 다른 x좌표
	// yNum개의 서로 다른 y좌표.
	// 접근은 xHash[x[i]]로 한다.
	for (int i = 0; i < N; i++) {
		++A[xHash[x[i]]][yHash[y[i]]]; // 압축된 좌표에 점들을 넣는다.
	}
	
	// 점들이 A[][]에 들어간 상태.
	// (x1,y1) ~ (x2,y2)에 존재하는 점들을 O(1)으로 구하기 위해
	// 부분합으로 구해둔다.
	for (int i = 0; i <= xNum; i++) {
		for (int j = 0; j < yNum; j++) {
			pSum[i + 1][j + 1] = pSum[i][j + 1] + pSum[i + 1][j] - pSum[i][j] + A[i][j];
		}
	}

	// 최대 1000 * 1000의 점들에 대해
	// 모두 그어보고 나뉜 4개의 사분면에 대해 최대 점을 구한다.
	// x = i, y = j에 그어서 확인한다.
	int ret = N;
	for (int i = 0; i < xNum; i++) {
		for (int j = 0; j < yNum; j++) {
			int temp = max(getRangeSum(0, 0, i, j), getRangeSum(i, j, xNum, yNum));
			temp = max(temp, getRangeSum(0, j, i, yNum));
			temp = max(temp, getRangeSum(i, 0, xNum, j));

			ret = min(ret, temp);
		}
	}

	printf("%d\n", ret);
}