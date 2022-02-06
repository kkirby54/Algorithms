#include <cstdio>
#include <algorithm>
#include <cstring>

int T, N, M;
char str[51];

struct Node {
	char key[51];
	int data;
	Node* next;

	Node* alloc(char _key[], int _data, Node* _next) {
		strcpy(key, _key);
		data = _data;
		next = _next;
		return this;
	}

	// key가 없을 수도 있다.
	Node* getPrevNode(char _key[]) {
		Node* ptr = this;
		while (ptr->next) {
			if (strcmp(_key, ptr->next->key) == 0) {
				return ptr;
			}
			ptr = ptr->next;
		}
		return nullptr; // 없다면 nullptr 반환.
	}
};

int bCnt;
Node buf[100000];
Node hashTable[1 << 18];

void init() {
	bCnt = 0;
	for (int i = 0; i < (1 << 18); i++)
		hashTable[i].next = 0;
}

// str -> hashVal로 변환
int getKey(char str[]) {
	unsigned long long val = 5318;

	for (int i = 0; str[i]; i++) {
		val = ((val << 5) + val) + (str[i] - 'a' + 1);
	}
	return (int)(val % ((1 << 18) - 1));
}

int find(char str[]) {
	int target = getKey(str);

	Node* prevNode = hashTable[target].getPrevNode(str);
	
	if (prevNode == nullptr) {
		//printf("%s는 없다\n", str);
		return -1;
	}


	return prevNode->next->data;
}

void add(char str[], int data) {
	int target = getKey(str);
	hashTable[target].next = buf[bCnt++].alloc(str, data, hashTable[target].next);
}

int remove(char str[]) {
	int target = getKey(str);
	
	Node* prevNode = hashTable[target].getPrevNode(str);
	Node* targetNode = prevNode->next;

	prevNode->next = targetNode->next;

	return targetNode->data;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		init();
		int ret = 0;
		for (int i = 0; i < N; i++) {
			scanf("%s", str);

			add(str, i);
		}
		for (int i = 0; i < M; i++) {
			scanf("%s", str);
			if (find(str) != -1) {
				ret++;
			}
		}
		printf("#%d %d\n", t, ret);

	}
}