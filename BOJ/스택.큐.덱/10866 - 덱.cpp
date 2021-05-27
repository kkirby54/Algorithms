#include <cstdio>

#define MAX_SIZE 10000

class Deque {
	int data[MAX_SIZE];
	int nums, head, tail;
public:
	Deque() : nums(0), head(0), tail(0) {}

	void push_front(int x) {
		nums++;
		head = ((head - 1) + MAX_SIZE) % MAX_SIZE;
		data[head] = x;
	}
	void push_back(int x) {
		nums++;
		data[tail] = x;
		tail = (tail + 1 + MAX_SIZE) % MAX_SIZE;
	}

	int pop_front() {
		if (empty()) return -1;
		nums--;
		int ret = data[head];
		head = (head + 1 + MAX_SIZE) % MAX_SIZE;

		return ret;
	}

	int pop_back() {
		if (empty()) return -1;
		nums--;
		tail = (tail - 1 + MAX_SIZE) % MAX_SIZE;
		return data[tail];
	}

	int size() { return nums; }
	bool empty() { return nums == 0; }
	int front() {
		if (empty()) return -1;
		return data[head];
	}

	int back() {
		if (empty()) return -1;
		return data[((tail - 1) + MAX_SIZE) % MAX_SIZE];
	}

};

int main() {
	char str[11];
	int N, tmp;
	scanf("%d", &N);

	Deque Q;

	for (int i = 0; i < N; i++) {
		scanf("%s", str);

		if (str[0] == 'p') {
			if (str[5] == 'b') {
				scanf("%d", &tmp);
				Q.push_back(tmp);
			}
			else if (str[5] == 'f') {
				scanf("%d", &tmp);
				Q.push_front(tmp);
			}
			else if (str[4] == 'f') {
				printf("%d\n", Q.pop_front());
			}
			else printf("%d\n", Q.pop_back());
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
		else printf("%d\n", Q.back());

	}


}