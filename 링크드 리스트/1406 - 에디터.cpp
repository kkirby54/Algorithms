#include <cstdio>

class Node {
public:
	char data;
	Node* next, *prev;

	Node(char d) : data(d), next(nullptr), prev(nullptr) {}
};

class List {
public:
	Node* head, * tail, *cursor;

	List() {
		cursor = new Node(0);
		head = new Node(0);
		tail = cursor;

		head->next = cursor;
		cursor->prev = head;
	}

	void L();
	void D();
	void B();
	void P(char x);

	void print();

};

void List::L() {
	if (cursor == head->next) return;
	cursor = cursor->prev;
}

void List::D() {
	if (cursor == tail) return;
	cursor = cursor->next;
}

// cursor.prev를 삭제한다.
void List::B() {
	if (cursor == head->next) return;

	Node* removed_node = cursor->prev;
	removed_node->prev->next = cursor;
	removed_node->next->prev = removed_node->prev;
	delete removed_node;
}

void List::P(char x) {
	Node* newbie = new Node(x);
	newbie->prev = cursor->prev;
	newbie->next = cursor;

	cursor->prev->next = newbie;
	cursor->prev = newbie;
}

void List::print() {
	Node* curr = head->next;
	while (curr != tail) {
		printf("%c", curr->data);
		curr = curr->next;
	}
}

int main() {
	List L;
	int M, tmp;
	char ch, str[2];

	while ((ch = getchar()) != '\n') {
		L.P(ch);
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%s", str);

		switch (str[0])
		{
		case 'L':
			L.L();
			break;
		case 'D':
			L.D();
			break;
		case 'B':
			L.B();
			break;
		case 'P':
			scanf("%s", str);
			L.P(str[0]);
			break;
		}
	}

	L.print();
}