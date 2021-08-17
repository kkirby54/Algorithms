#include <cstdio>
#include <stack>
#include <random>
#include <cmath>
#include <algorithm>
using namespace std;

typedef int KeyType;

struct Node {
	KeyType key;

	int priorty, size;

	Node* left, * right;
	Node(const KeyType& _key) : key(_key), priorty(rand()),
		size(1), left(nullptr), right(nullptr) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;

// key를 중심으로 root를 쪼갠다.
// 결과의 left에는 key보다 작은, right에는 key보다 큰 노드들이 들어있다.
NodePair split(Node* root, KeyType key) {
	if (root == nullptr) return NodePair(nullptr, nullptr);

	// 이러면, root->left들도 다 작음.
	// 그리고 root->right들과 재귀적으로 또 합치기.
	if (root->key < key) {
		NodePair R = split(root->right, key);

		// 그럼 R.first는 key보다 작은 애들.
		// + root와 root->left들도 다 작음.
		root->setRight(R.first);

		// key보다 큰 애들은 R.second
		return NodePair(root,R.second);
	}
	NodePair L = split(root->left, key);
	root->setLeft(L.second);
	return NodePair(L.first, root);
}

// root에 node를 삽입.
Node* insert(Node* root, Node* node) {
	if (root == nullptr) return node;

	if (root->priorty < node->priorty) {
		NodePair ret = split(root, node->key);
		node->setLeft(ret.first);
		node->setRight(ret.second);
		return node;
	}
	else if (root->key > node->key) {
		root->setLeft(insert(root->left, node));
	}
	else {
		root->setRight(insert(root->right, node));
	}

	return root;
}

// 삭제와 합치기 연산

// a노드와 b노드를 합친다.
// a < b라고 가정한다. (트리 상에서)
Node* merge(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	if (a->priorty < b->priorty) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// 삭제 연산
Node* erase(Node* root, KeyType key) {
	if (root == nullptr) return root;

	// 그럼 왼쪽으로 내려가서 찾아야 함.
	if (root->key > key) {
		root->setLeft(erase(root->left, key));
	}
	else if (root->key < key) {
		root->setRight(erase(root->right, key));
	}
	// 찐으로 삭제해야 할 때
	else {
		Node* tmp = merge(root->left, root->right);
		delete root;
		return tmp;
	}

	return root;
}

// k번째 원소를 찾기
Node* kth(Node* root, int k) {
	if (root == nullptr) return nullptr;

	int leftSize = 0;
	if (root->left) leftSize = root->left->size;
	// 왼쪽 크기가 더 크면, 당연히 왼쪽에 있음.
	if (leftSize >= k) {
		return kth(root->left, k);
	}
	else if (leftSize == k - 1) {
		return root;
	}
	// leftSize <= k라면, 오른쪽에 있음.
	else {
		return kth(root->right, k - (leftSize + 1));
	}
}

int countLessThan(Node* root, int key) {
	if (root == nullptr) return 0;

	// root->left에서 찾아
	if (root->key > key) {
		return countLessThan(root->left, key);
	}
	else if (root->key == key) return root->left->size;
	// root->key < key라면, 일단 root->left->size + 1은 다 포함됨.
	else {
		int leftSize = 0;
		if (root->left) leftSize = root->left->size;
		return countLessThan(root->right, key) + leftSize + 1;
	}
}

int C, N, arr[50000];

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		stack<int> S;

		// -1부터, N까지.
		Node* root = new Node(-1);
		for (int i = 2; i <= N; i++) {
			root = insert(root, new Node(i * -1));
		}

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);
		}

		for (int i = N - 1; i >= 0; i--) {
			int cnt = arr[i] + 1;
			
			auto currNode = kth(root, cnt);
			S.push(currNode->key);
			root = erase(root, currNode->key);
		}

		while (!S.empty()) {
			printf("%d ", S.top() * -1);
			S.pop();
		}
		puts("");
	}

}