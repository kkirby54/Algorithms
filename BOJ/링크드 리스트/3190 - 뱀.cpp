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
// dr[currDir], dc[currDir]�� ����


// �� ���� �ִ� �� �����Ѵ�.
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

	// ��忡 �߰��ϱ�. (�� apple �Ա�)
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
			// �׳� �ϳ��� �־��ٸ�, tail ó���� �������.
			if (size == 1) {
				tail = newNode->next;
			}
		}
		size++;
	}
	
	// �̵��ϱ�.
	void move() {
		// ���� ���⿡ ����, head�� �߰��Ѵ�.

		// ���� ������?
		int nR = head->r + dr[currDir];
		int nC = head->c + dc[currDir];

		// �ٵ� ���� ���� ���� ������ �ȵ�.
		if (isHear[nR][nC]) {
			//printf("�浹! %d��, (%d, %d)����\n", currT, nR, nC);
			isFin = true;
		}
		else {
			addFront(nR, nC);
		}

		// tail�� ����.
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
		// D��� ������. 1)
		if (tmp[0] == 'D')
			trans_dir[i] = 1;
		// L�̶�� ����. -1)
		else trans_dir[i] = -1;
	}

	// �켱 0,0 ����.
	LinkedList snake;
	snake.addFront(0, 0);

	while (!isFin) {

		// �⺻�����δ� move�ε�.
		// �� �ٷ� ���� ����.
		int nR = snake.head->r + dr[currDir];
		int nC = snake.head->c + dc[currDir];

		// �ٵ� �ƿ� �����ٸ�?
		if (nR < 0 || nR >= N || nC < 0 || nC >= N) {
			//printf("%d�ʿ� ���� ����\n", currT);
			isFin = true;
		}
		// ����� �ִ� ���̾��ٸ�
		else if (board[nR][nC] == 1) {
			snake.addFront(nR, nC);
			board[nR][nC] = 0;	// ��� ���� ó��
		}
		else {
			snake.move();
		}
		//snake.print();
		

		currT++;
		// �ð��� �Ǹ�, ���� ��ȯ
		if (trans_t[currTransIdx] == currT) {
			// printf("%d �ð��� �Ǿ %d�������� ��ȯ\n", currT, trans_dir[currTransIdx]);
			// �̷��� ���������� Ʋ��
			if (trans_dir[currTransIdx] == 1) {
				currDir = (currDir + 1) % 4;
			}
			// ���� Ʋ��
			else {
				currDir = (4 + (currDir - 1)) % 4;
			}

			currTransIdx++;
		}

	}

	printf("%d", currT);



}