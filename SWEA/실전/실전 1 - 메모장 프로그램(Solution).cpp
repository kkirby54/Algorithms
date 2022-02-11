#include <cstdio>
#include <cstring>
#define MAX_NODE 90400

struct Node {
	char ch;
	Node* prev, * next;

	Node* alloc(char _ch, Node* _prev, Node* _next) {
		ch = _ch;
		prev = _prev;
		next = _next;
		return this;
	}
};

int memPoolCnt;
int len;
int R, C, cursorR;
Node buf[MAX_NODE];
Node* head[305]; // 300개의 행마다 헤드를 저장한다.
Node* tail; // 현재 마지막을 저장하고 있는다.
Node* cursor;
int cntFromHead[305][26];

void print(Node* cur) {
	Node* ptr = cur;
	printf("================출력 시작==================\n");
	while (ptr) {
		printf("%c->", ptr->ch);
		ptr = ptr->next;
	} puts("");
}

void init(int H, int W, char mStr[])
{
	memPoolCnt = 0;
	memset(head, 0, sizeof(head));
	memset(buf, 0, sizeof(buf));
	memset(cntFromHead, 0, sizeof(cntFromHead));
	R = H;
	C = W;

	int mstrIdx = 0;
	len = strlen(mStr);

	int headCnt = 0;
	for (int i = 0; i < len; i++) {
		Node* newNode = buf[memPoolCnt].alloc(mStr[mstrIdx++], memPoolCnt > 0 ? &buf[memPoolCnt - 1] : nullptr, nullptr);
		if (newNode->prev)
			newNode->prev->next = newNode;
		memPoolCnt++;

		// 그리고 나서 헤드를 설정한다.
		if (i % W == 0)
			head[headCnt++] = newNode;

		cntFromHead[headCnt - 1][mStr[mstrIdx - 1] - 'a']++;
	}

	tail = buf[memPoolCnt].alloc('-1', &buf[memPoolCnt - 1], nullptr);
	tail->prev->next = tail;
	memPoolCnt++;

	cursor = head[0];
	cursorR = 0;
	//print(head[0]);
}

void insert(char mChar)
{
	Node* newNode = buf[memPoolCnt++].alloc(mChar, cursor->prev, cursor);
	if (cursor->prev)
		cursor->prev->next = newNode;
	cursor->prev = newNode;

	// 현재 Head에 cnt도 증가
	cntFromHead[cursorR][mChar - 'a']++;

	// cursorR + 1부터 쭉.
	// 또는 커서 자체가 head[cursorR]에 있었다면.
	// cursorR도 헤드 조정해줘야 한다.
	if (cursor == head[cursorR])
		head[cursorR] = head[cursorR]->prev;
	
	for (int i = cursorR + 1; i < R; i++) {
		if (head[i]) {
			head[i] = head[i]->prev;

			// 그 다음에, 바꾼 head[i]에 해당하는 char를 i번째 cnt에 더해준다.
			// 그리고 내려왔으면 또 그 이전 헤드에서도 삭제를 해야한다.
			cntFromHead[i][head[i]->ch - 'a']++;
			cntFromHead[i - 1][head[i]->ch - 'a']--;
		}
		else break;
	}
	len++;
	if (len % C == 1) {
		// 이러면 새롭게 헤드를 만들어야 한다.
		head[len / C] = tail->prev;
		cntFromHead[len / C][head[len / C]->ch - 'a']++; // 처음 들어오는 녀석.
		cntFromHead[len / C - 1][head[len / C]->ch - 'a']--;
		memPoolCnt++;
	}

	// 그리고 cursorR 조정
	if (head[cursorR + 1]) {
		if (cursor->prev == head[cursorR + 1]->prev)
			cursorR++;
	}
	
	//	print(head[0]);
}

char moveCursor(int mRow, int mCol)
{
	// printf("========================cursor 움직이기 시작!=================\n");
	mRow--; mCol--;

	if (head[mRow]) {
		cursorR = mRow;
		cursor = head[mRow];
		for (int i = 0; i < mCol; i++) {
			if (cursor == tail) break;
			cursor = cursor->next;
		}
	}
	else {
		cursor = tail;
		cursorR = (len-1) / C;
	}

	if (cursor == tail) {
		return '$';
	}
	return cursor->ch;
}

int countCharacter(char mChar)
{
	int ret = 0;
	Node* ptr = cursor;
	while (ptr != head[cursorR + 1]) {
		if (ptr->ch == mChar) ret++;
		ptr = ptr->next;
	}
	for (int i = cursorR + 1; i < R; i++) {
		if (head[i]) {
			ret += (cntFromHead[i][mChar - 'a']);
		}
		else break;
	}

	return ret;
}