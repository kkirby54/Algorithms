#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stack>

typedef int KeyType;

struct Node {
	KeyType key;

	int priority, size;
	Node* left, * right;

	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(nullptr), right(nullptr) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef std::pair<Node*, Node*> NodePair;

// root를 중심으로 두 subtree를 만든다.
// key를 중심을 나눈다.
NodePair split(Node* root, KeyType key) {
	if (root == nullptr) return NodePair(nullptr, nullptr);
	// key vs root->key
	
	// 이러면 일단 왼쪽애들은 다 left 놈들
	// 이제 root->right에 있는 애들을 또 다시 쪼개면서, Key보다 큰 애를 찾아야돼. 재귀로
	if (root->key < key) {
		// 재귀로 쪼개면, left는 root->right로 들어가고, right는 그대로 리턴한다.
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// root->key > key인 경우는 반대로 한다.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root를 루트로 갖는 트리에 node를 삽입한다.
Node* insert(Node* root, Node* node) {
	// 조건. 일단 기본적으로 노드의 키를 갖고 BST 조건 만족
	// + priority를 보고 가야돼.
	// -> 그럼 차라리 heap처럼 일단 마지막에 삽입하고 봐?
	// 우선순위가 더 높다? -> 우선순위가 더 높으면 무조건 얘는 root보다 위에 있는 애임.
	// 우선순위가 낮다? -> 그럼 key를 보고 판단한다.

	if (root == nullptr) {
		return node;
	}

	// 이제 root의 우선순위 vs node의 우선순위
	if (root->priority >= node->priority) {
		// key를 본다.
		if (root->key < node->key) {
			root->setRight(insert(root->right, node));
		}
		else root->setLeft(insert(root->left, node));
	}
	// 아닌 경우가 이제 존나 빡치는 건데,
	// node를 중심으로 쪼개기 시전. 작은 것들 모은 subtree, 큰 것들 모은 subtree.
	// 이렇게 안 하면 BST 성질을 개무시하는 거임.
	else{
		// node의 key를 중심으로 ls, rs로 나눈다.
		// 그리고 나서 root를 node로 만들어야 한다.
		NodePair splited = split(root, node->key);
		node->setLeft(splited.first);
		node->setRight(splited.second);
		return node;
	}

	// 그리고 root를 리턴해. 
	return root;
}

// 하나의 조건 : max(a) < min(b)
// 그럼 무조건적으로 a->key < b->key임.
Node* merge(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	// 이러면 a를 기준으로 합칠 수 있다.
	if (a->priority > b->priority) {
		a->setRight(merge(a->right, b));
		return a;
	}
	else {
		b->setLeft(merge(a, b->left));
		return b;
	}
}

// root를 루트로 갖는 트리에서 key를 삭제한다.
Node* erase(Node* root, KeyType key) {
	if (root == nullptr) return root;

	// 오른쪽에 있는 경우
	if (root->key < key) {
		root->setRight(erase(root->right, key));
	}
	else if (root->key > key) {
		root->setLeft(erase(root->left, key));
	}
	// 이제 root를 삭제한 다음, 두 subtree를 합친 다음에 그걸 반환한다.
	else {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	return root;
}

// root를 루트로 갖는 트리에서 k번째 노드를 return 한다.
Node* kth(Node* root, int k) {
	int left_size = 0;
	if (root->left != nullptr) left_size = root->left->size;

	// left_size가 더 작거나 같으면 왼쪽에 있다.
	if (k <= left_size) return kth(root->left, k);
	else if (k == left_size + 1) return root;

	// k > left_size 이러면 오른쪽에 있는데,
	// k - (l + 1)번째에 있다.
	return kth(root->right, k - left_size - 1);
}

// X보다 작은 원소 세기
int countLessThen(Node* root, KeyType key) {
	if (root == nullptr) return 0;
	if (root->key >= key) {
		return countLessThen(root->left, key);
	}
	// 왼쪽이 존재 안할 수도 있으니까
	int ls = root->left ? root->left->size : 0;
	
	return ls + 1 + countLessThen(root->right, key);
}

void inorder(Node* root) {
	if (root->left) inorder(root->left);
	printf("%d ", root->key);
	if (root->right) inorder(root->right);
}

void preorder(Node* root) {

	printf("%d ", root->key);
	if (root->left) preorder(root->left);
	if (root->right) preorder(root->right);
}

int C, N;
int count[50000];

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		Node* root = new Node(1);
		std::stack<int> S;

		// 1 ~ N을 후보군에 둔다.
		for (int i = 1; i < N; i++)
			root = insert(root, new Node(i + 1));

		for (int i = 0; i < N; i++) {
			scanf("%d", count + i);
		}

		// 뒤에서부터 보면서,
		// count[i]를 본다
		int len = N;
		for (int i = N - 1; i >= 0; i--) {
			int k = count[i];

			// Candidates에서, candidates.size() - k번째 수를 찾는다.
			// 그리고 그 수를 Cand에서 삭제.

			// 후보들에서 노드를 찾아라.
			S.push((kth(root, len - k))->key);
			// 그리고 잘라버려
			root = erase(root, (kth(root, len - k))->key);
			len--;
		}

		while (!S.empty()) {
			printf("%d ", S.top());
			S.pop();
		}
		puts("");
	}

}