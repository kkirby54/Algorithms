#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode {
	vector<TreeNode*> children;
};

// 지금까지 찾은 잎-잎 경로 길이 저장
int longest;

// root를 루트로 하는 서브트리의 높이를 반환.
int height(TreeNode* root) {
	vector<int> heights;

	for (int i = 0; i < root->children.size(); i++) {
		heights.push_back(height(root->children[i]));
	}

	// 그럼 이제 자식들의 높이가 다 들어가 있다.
	
	// 비어있으면 leaf인 거임
	if (heights.empty()) return 0;

	// 그거를 정렬하면, 
	// 높이가 작은 순으로 ..
	sort(heights.begin(), heights.end());

	int len = heights.size();
	if (heights.size() >= 2) {
		longest = max(longest, 2 + heights[len - 1] + heights[len - 2]);
	}

	return heights.back() + 1;
}

int solve(TreeNode* root) {
	longest = 0;
	int h = height(root);
	return max(longest, h);
}

int N, C, X[100], Y[100], R[100];

int sqr(int x) { return x * x; }
int sqrdist(int a, int b) {
	return sqr(X[a] - X[b]) + sqr(Y[a] - Y[b]);
}

// 성벽 a가 b를 포함하는지 확인하는 함수
bool encloses(int a, int b) {
	return R[a] > R[b] && sqrdist(a, b) < sqr(R[b] - R[a]);
}

// parent가 child의 부모인지 확인. 꼭 직접 포함해야 함.
bool isChild(int parent, int child) {
	if (!encloses(parent, child)) return false;

	// 논리는,
	// for문을 돌면서 다른 애들이 parent에 포함되면서, child를 포함하면
	// 이 둘은 직접적인 포함관계가 아니다. 그래서 false.
	for (int i = 0; i < N; i++) {
		if (i != parent && i != child &&
			encloses(parent, i) && encloses(i, child))
			return false;
	}

	return true;
}

// root 성벽을 루트로 하는 트리를 생성한다.
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < N; ch++) {
		if (isChild(root, ch)) {
			// 이거도 다 재귀로 짰네
			ret->children.push_back(getTree(ch));
		}
	}
	
	return ret;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", X + i, Y + i, R + i);
		}

		TreeNode* root = getTree(0);
		printf("%d\n", solve(root));

	}


}


