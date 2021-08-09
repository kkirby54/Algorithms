#include <cstdio>
#include <algorithm>

char str[100001];
int M;
char opr, ch;

class ListNode {
public:
	char data;
	ListNode* next, * prev;

	ListNode(char data, ListNode* prev = nullptr, ListNode* next = nullptr) : data(data), prev(prev), next(next) {}
};

class LinkedList {
public:
	ListNode* head, * tail, * cursor;
	int size;

	LinkedList() : size(0) {
		head = new ListNode(-1);
		tail = new ListNode(-1);

		head->next = tail;
		tail->prev = head;
		cursor = tail;
	}

	// 커서 왼쪽에 추가
	void push(int X) {
		ListNode* newbie = new ListNode(X, cursor->prev, cursor);
		cursor->prev->next = newbie;
		cursor->prev = newbie;

		size++;
	}

	// 커서를 왼쪽으로 한 칸 옮김.
	// 여기서, head->next까지 최대로 가자.
	void left() {
		if (cursor == head->next) return;
		cursor = cursor->prev;
	}

	void right() {
		if (cursor == tail) return;
		cursor = cursor->next;
	}

	// 커서 왼쪽 문자를 삭제.
	void erase() {
		if (!size || cursor == head->next) return;

		ListNode* removed = cursor->prev;
		removed->prev->next = removed->next;
		removed->next->prev = removed->prev;
		delete removed;
	}

	void print() {
		ListNode* tmp = head->next;
		while (tmp != tail) {
			printf("%c", tmp->data);
			tmp = tmp->next;
		}
	}

};

int main() {
	scanf("%s", str);

	LinkedList list;
	for (int i = 0; str[i]; i++)
		list.push(str[i]);

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		getchar();
		scanf("%c", &opr);
		switch (opr)
		{
		case 'P':
			getchar();
			scanf("%c", &ch);
			list.push(ch);
			break;

		case 'L':
			list.left();
			break;
		case 'D':
			list.right();
			break;
		case 'B':
			list.erase();
			break;
		default:
			break;
		}

	}
	list.print();
}