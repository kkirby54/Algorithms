#include <cstdio>
#include <algorithm>

class Node {
public:
	int data;
	Node* next;

	Node(int d, Node* n = nullptr) : data(d), next(n) {}
};

class LinkedList {
public:
	Node* head, * tail;
	int size;

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}

	void addLast(int val) {
		Node* new_node = new Node(val);
		if (!size) {
			head = tail = new_node;
			size++;
			return;
		}
		else if (size == 1) {
			head->next = tail;
		}

		tail->next = new_node;
		tail = new_node;

		size++;
	}

	// pos 위치 앞에 val 노드를 추가한다.
	void insert(int pos, int val) {
		Node* new_node = new Node(val);

		if (!size) {
			head = tail = new_node;
			size++;
			return;
		}
		// 이러면 헤드를 바꿔
		if (pos == 0) {
			new_node->next = head;
			head = new_node;
			size++;
			return;
		}
		else if (pos == size) {
			tail->next = new_node;
			tail = new_node;
			size++;
			return;
		}

		Node* curr = head;
		for (int i = 0; i < pos - 1; i++) {
			curr = curr->next;
		}
		new_node->next = curr->next;
		curr->next = new_node;

		size++;
	}

	void remove(int pos) {
		if (!size) return;

		if (pos == 0) {
			head = head->next;
			size--;
			return;
		}

		Node* curr = head;
		for (int i = 0; i < pos - 1; i++) {
			curr = curr->next;
		}

		curr->next = curr->next->next;
		if (pos == size - 1) tail = curr;
		size--;
	}

	void update(int pos, int val) {
		Node* curr = head;
		for (int i = 0; i < pos; i++) {
			curr = curr->next;
		}
		curr->data = val;
	}
};

int main() {

	int T, N, M, L, num, pos, val;
	char opr[2];
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %d", &N, &M, &L);

		LinkedList LL;
		for (int i = 0; i < N; i++) {
			scanf("%d", &num);
			LL.insert(i, num);
		}


		for (int i = 0; i < M; i++) {
			scanf("%s", opr);
			if (opr[0] == 'I') {
				scanf("%d %d", &pos, &val);
				LL.insert(pos, val);
			}
			else if (opr[0] == 'D') {
				scanf("%d", &pos);
				LL.remove(pos);

			}
			else {
				scanf("%d %d", &pos, &val);
				LL.update(pos, val);
			}
			//LL.print();
		}


		// L번째 위치한 인덱스 번호
		int ret;
		if (L >= LL.size) {
			ret = -1;
		}
		else {
			Node* curr = LL.head;
			for (int i = 0; i < L; i++) {
				curr = curr->next;
			}

			ret = curr->data;
		}

		printf("#%d %d\n", t, ret);
	}


}