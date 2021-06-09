#include <cstdio>

struct ListNode {
	int data;
	// 양방향 연결 리스트
	ListNode* prev, * next;

	ListNode(int d) : data(d), prev(nullptr), next(nullptr) {}
	ListNode(int d, ListNode* p, ListNode* n) : data(d), prev(p), next(n) {}
};


class List {
public:
	ListNode* head, * tail;
	int size;

	List() : size(0), head(nullptr), tail(nullptr) {}

	void push_back(int x) {
		if (size) {
			ListNode* node = new ListNode(x, tail, tail->next);
			tail->next->prev = node;
			tail->next = node;
			tail = node;
		}
		// 없다는 얘기는 head, tail이 비었다는 말
		else {
			head = tail = new ListNode(x);
			head->next = head->prev = tail;
			tail->next = tail->prev = head;
		}

		size++;
	}

	void print() {
		ListNode* curr = head;
		for (int i = 0; i < size; i++) {
			printf("%d ", curr->data);
			curr = curr->next;
		}
		puts("");
	}

	// Node를 삭제해버려
	// 그리고 삭제한 다음걸 리턴
	ListNode* remove(ListNode* node) {
		if (!size) return nullptr;

		ListNode* nextNode = node->next;

		// 걍 다 일반적인 케이스로 처리한 다음에
		// 그 다음에 노드가 만약 tail이었다면
		node->prev->next = node->next;
		node->next->prev = node->prev;

		// 그 다음에 node가 만약 head였으면 바꾸줘
		if (node == head) {
			head = head->next;
		}
		if (node == tail) tail = tail->prev;

		delete node;

		size--;
		if (!size) {
			head = tail = nullptr;
			return nullptr;
		}

		return nextNode;
	}

};

int C, N, K;

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &K);

		List A;
		for (int i = 1; i <= N; i++)
			A.push_back(i);

		// 그냥 이제 N-2번 삭제하면 됨
		ListNode* curr = A.head;
		for (int i = 0; i < N - 2; i++) {
			// 삭제 후 K-1만큼 앞으로 가
			curr = A.remove(curr);
			for (int k = 0; k < K-1; k++)
				curr = curr->next;
		}

		A.print();
	}


}