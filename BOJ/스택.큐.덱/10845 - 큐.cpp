#include <cstdio>

class Queue {
	int data[10001];
	int head, tail, nums;

public:
	Queue() : nums(0), head(0), tail(0) {}

	void push(int x) {
		data[tail++] = x;
		nums++;
	}

	int pop() {
		if (empty()) return -1;
		nums--;
		return data[head++];
	}

	bool empty() {
		return nums == 0;
	}

	int size() {
		return nums;
	}

	int front() {
		if (empty()) return -1;
		return data[head];
	}
	int back() {
		if (empty()) return -1;
		return data[tail - 1];
	}

};

int main() {
	int N, tmp;
	char str[6];
	Queue Q;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);

		if (str[0] == 'p') {
			if (str[1] == 'u') {
				scanf("%d", &tmp);
				Q.push(tmp);
			}
			else printf("%d\n",Q.pop());
		}
		else if (str[0] == 's') {
			printf("%d\n", Q.size());
		}
		else if (str[0] == 'e') {
			printf("%d\n", Q.empty());
		}
		else if (str[0] == 'f') {
			printf("%d\n", Q.front());
		}
		else {
			printf("%d\n", Q.back());
		}

	}

}