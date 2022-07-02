#include <cstdio>
#include <vector>
#include <queue>

int N, board[100][100];
int K, L;

int trans_t[100];
int trans_dir[100];
int currTransIdx = 0;


int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };
int currDir = 0;
int currT = 0;
// dr[currDir], dc[currDir]로 접근


// 뱀 몸이 있는 곳 저장한다.
bool isHear[100][100];
bool isFin = false;

struct Node {
	int r, c;
	Node* next;
	Node* prev;

	Node(int r = -1, int c = -1, Node* n = nullptr, Node* p = nullptr) : r(r), c(c), next(n), prev(p) {}
};

struct LinkedList {
	Node* head, * tail;
	int size;

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// 헤드에 추가하기. (즉 apple 먹기)
	void addFront(int r, int c) {
		if (size == 0) {
			head = tail = new Node(r, c, nullptr, nullptr);
			isHear[r][c] = true;
		}
		else {
			Node* newNode = new Node(r, c, nullptr, nullptr);
			newNode->next = head;
			head->prev = newNode;
			head = newNode;

			isHear[r][c] = true;
			// 그냥 하나만 있었다면, tail 처리를 해줘야함.
			if (size == 1) {
				tail = newNode->next;
			}
		}
		size++;
	}
	
	// 이동하기.
	void move() {
		// 전진 방향에 대해, head를 추가한다.

		// 전진 방향은?
		int nR = head->r + dr[currDir];
		int nC = head->c + dc[currDir];

		// 근데 현재 뱀의 몸이 있으면 안됨.
		if (isHear[nR][nC]) {
			//printf("충돌! %d초, (%d, %d)에서\n", currT, nR, nC);
			isFin = true;
		}
		else {
			addFront(nR, nC);
		}

		// tail을 뺀다.
		Node* removed = tail;
		isHear[removed->r][removed->c] = false;
		tail = removed->prev;
		tail->next = nullptr;
		delete removed;
		size--;

	}


	void print() {
		Node* tmp = head;

		while (tmp) {
			printf("(%d, %d) -> ", tmp->r, tmp->c);
			tmp = tmp->next;
		}
		puts("");
	}


};


int main() {
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		int tR, tC;
		scanf("%d %d", &tR, &tC);
		tR--; tC--;
		board[tR][tC] = 1;
	}

	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		char tmp[3];
		scanf("%d %s", trans_t + i, tmp);
		// D라면 오른쪽. 1)
		if (tmp[0] == 'D')
			trans_dir[i] = 1;
		// L이라면 왼쪽. -1)
		else trans_dir[i] = -1;
	}

	// 우선 0,0 시작.
	LinkedList snake;
	snake.addFront(0, 0);

	while (!isFin) {

		// 기본적으로는 move인데.
		// 내 바로 앞을 본다.
		int nR = snake.head->r + dr[currDir];
		int nC = snake.head->c + dc[currDir];

		// 근데 아예 못간다면?
		if (nR < 0 || nR >= N || nC < 0 || nC >= N) {
			//printf("%d초에 벽에 닿음\n", currT);
			isFin = true;
		}
		// 사과가 있는 곳이었다면
		else if (board[nR][nC] == 1) {
			snake.addFront(nR, nC);
			board[nR][nC] = 0;	// 사과 먹음 처리
		}
		else {
			snake.move();
		}
		//snake.print();
		

		currT++;
		// 시간이 되면, 방향 전환
		if (trans_t[currTransIdx] == currT) {
			// printf("%d 시간이 되어서 %d방향으로 전환\n", currT, trans_dir[currTransIdx]);
			// 이러면 오른쪽으로 틀기
			if (trans_dir[currTransIdx] == 1) {
				currDir = (currDir + 1) % 4;
			}
			// 왼쪽 틀기
			else {
				currDir = (4 + (currDir - 1)) % 4;
			}

			currTransIdx++;
		}

	}

	printf("%d", currT);



}