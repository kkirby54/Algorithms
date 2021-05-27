#include <cstdio>

class Stack {
	int data[10001];
	int nums;

public:
	Stack() : nums(0) {}

	void push(int x) {
		data[nums++] = x;
	}

	int pop() {
		if (empty()) return -1;
		return data[--nums];
	}

	int size() {
		return nums;
	}
	int empty() {
		return nums == 0;
	}
	int top() {
		if (empty()) return -1;
		return data[nums - 1];
	}
};

int N;
int tmp;
char order[10];

int main() {
	scanf("%d", &N);

	Stack S;

	for (int i = 0; i < N; i++) {
		scanf("%s", order);
		if (order[0] == 'p') {
			if (order[1] == 'u') {
				scanf("%d", &tmp);
				S.push(tmp);
			}
			else printf("%d\n", S.pop());
		}
		else if (order[0] == 's') {
			printf("%d\n", S.size());
		}
		else if (order[0] == 'e') {
			printf("%d\n", S.empty());
		}
		else {
			printf("%d\n", S.top());
		}

	}

}