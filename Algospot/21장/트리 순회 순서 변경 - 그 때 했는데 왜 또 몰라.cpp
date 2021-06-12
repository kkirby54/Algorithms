#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int C, N, rootPos;
vector<int> preorder;
vector<int> inorder;

// start부터 end까지의..
void PrintPostOrder(int start, int end) {
	if (start > end) return;

	int root = preorder[rootPos++];
	int inPos = std::find(inorder.begin(), inorder.end(), root) - inorder.begin();

	PrintPostOrder(start, inPos-1);
	PrintPostOrder(inPos + 1, end);

	printf("%d ", root);
}


int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		// 전위, 중위 순회했을 때의 방문 순서

		rootPos = 0;
		preorder.resize(N);
		inorder.resize(N);

		for (int i = 0; i < N; i++) {
			scanf("%d", &preorder[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &inorder[i]);
		}

		PrintPostOrder(0, N - 1);

	}

}