#include <cstdio>
#include <algorithm>

struct Node {
	int data;
	Node* next;
	Node* prev;

	Node(int d, Node* n = nullptr, Node* p = nullptr) : data(d), next(n), prev(p) {}
};

Node* head, * tail;
int size;

// curr 뒤에 넣어. 그리고 그 결과를 반환.
Node* insert(Node* curr, int val) {
	Node* new_node = new Node(val);
	size++;

	if (curr == nullptr) {
		head = tail = new_node;
	}
	// 이게 꼬리에 삽입하는 경우.
	else if (curr->next == nullptr) {
		curr->next = new_node;
		new_node->prev = curr;

		tail = new_node;
	}
	else {
		new_node->prev = curr;
		new_node->next = curr->next;

		curr->next->prev = new_node;
		curr->next = new_node;
	}
	return new_node;
}

// 현재를 지워, 그리고 그 다음을 리턴
Node* remove(Node* curr) {
	if (curr == nullptr) return nullptr;

	Node* ret = curr->next;
	if (curr == head) {
		head = curr->next;

	}
	else if (curr == tail) {
		tail = curr->prev;
		tail->next = nullptr;
	}
	else {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}
	free(curr);

	size--;
	if (!size) head = tail = nullptr;

	return ret;
}

Node* addLast(int val) {
	Node* new_node = new Node(val);

	if (tail == nullptr) {
		head = tail = new_node;
	}
	else {
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}

	size++;
	return new_node;
}

Node* addFirst(int val) {
	Node* new_node = new Node(val);

	if (head == nullptr) head = tail = new_node;
	else {
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	size++;
	return new_node;
}


int main() {
	int N, M, arr[4000], x, y, s;
	char opr[2];

	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		head = tail = nullptr;
		size = 0;

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);
			// printf("%d번째 받는 중\n", i);
			tail = insert(tail, arr[i]);
		}

		//print();

		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			scanf("%s", opr);
			if (opr[0] == 'I') {
				scanf("%d %d", &x, &y);


				Node* curr = head;
				for (int i = 0; i < x - 1; i++) {
					curr = curr->next;
				}

				// curr부터 y개 숫자 삽입.
				for (int j = 0; j < y; j++) {
					scanf("%d", arr + j);

					if (x == 0) {
						curr = addFirst(arr[j]);
						x += 1;
					}
					else
						curr = insert(curr, arr[j]);
					//print();
				}


			}
			else if (opr[0] == 'D') {
				scanf("%d %d", &x, &y);

				Node* curr = head;
				for (int i = 0; i < x; i++) {
					curr = curr->next;
				}

				// curr 다음부터 y개 삭제
				for (int j = 0; j < y; j++) {
					curr = remove(curr);
				}

				//print();
			}
			else {
				scanf("%d", &y);

				for (int i = 0; i < y; i++) {
					scanf("%d", arr + i);

					addLast(arr[i]);
				}
				//print();

			}
		}

		Node* ret = head;
		printf("#%d ", t);
		for (int i = 0; i < 10; i++) {
			printf("%d ", ret->data);
			ret = ret->next;
		}

	}


}