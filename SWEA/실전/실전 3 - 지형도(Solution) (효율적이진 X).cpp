#include <cstring>

#define MAX_MAP_SIZE 2000

struct Point
{
	int r;
	int c;
};


int board[MAX_MAP_SIZE][MAX_MAP_SIZE];
int k;
int delta[65][65];

// Max Heap으로 짠다.
class Heap {
public:
	Point heap[2505] = { 0 };
	int size = 0;

	void pushHeap(Point x) {
		heap[size++] = x;

		int curr = size - 1;
		while (curr != 0) {
			int currR = heap[curr].r, currC = heap[curr].c;
			int parentR = heap[(curr - 1) / 2].r, parentC = heap[(curr - 1) / 2].c;

			// 기본적으로, 부모가 더 높이가 크다면 종료
			if (board[currR][currC] + delta[currR/k][currC / k] < board[parentR][parentC] + delta[parentR / k][parentC / k]) break;

			// 높이가 같다면,
			else if (board[currR][currC] + delta[currR / k][currC / k] == board[parentR][parentC] + delta[parentR / k][parentC / k]) {
				// 근데 r좌표가 parent가 더 작다면, 종료
				if (currR > parentR) break;
				else if (currR == parentR) {
					if (currC > parentC) break;
				}
			}

			// curr과 parent를 바꾼다.
			Point tmp = heap[curr];
			heap[curr] = heap[(curr - 1) / 2];
			heap[(curr - 1) / 2] = tmp;
			curr = (curr - 1) / 2;
		}
	}

	Point pop() {
		if (size == 0) return Point();
		Point ret = heap[0];

		// 가장 마지막을 루트로 올린다.
		heap[0] = heap[size - 1];
		// 그리고 사이즈를 아예 줄인다.
		size--;

		int curr = 0;
		// 이제 자식 노드로 내려가면서 swap한다.
		while ((curr * 2 + 1) < size) {
			int child;

			// 왼쪽 자식만 있는 경우
			if (curr * 2 + 2 == size) {
				child = curr * 2 + 1;
			}
			else {
				// 왼쪽, 오른쪽 자식 중에 더 큰 걸 고른다.
				// 그 기준은?
				// 1. 둘 중 높이가 더 큰 것.
				int leftCh = curr * 2 + 1;
				int rightCh = curr * 2 + 2;
				
				int leftChR = heap[leftCh].r, leftChC = heap[leftCh].c;
				int rightChR = heap[rightCh].r, rightChC = heap[rightCh].c;

				if (board[leftChR][leftChC] + delta[leftChR / k][leftChC / k] > board[rightChR][rightChC] + delta[rightChR / k][rightChC / k])
					child = leftCh;
				else if (board[leftChR][leftChC] + delta[leftChR / k][leftChC / k] < board[rightChR][rightChC] + delta[rightChR / k][rightChC / k])
					child = rightCh;
				else {
					// 높이가 같다면, r좌표가 작은 것이.
					if (leftChR < rightChR) child = leftCh;
					else if (leftChR > rightChR) child = rightCh;
					else {
						// r좌표도 같다면, c좌표가 작은 것이 우선
						if (leftChC < rightChC) child = leftCh;
						else child = rightCh;
					}
				}
			}

			// 이제 curr과 child를 비교한다.
			int currR = heap[curr].r, currC = heap[curr].c;
			int childR = heap[child].r, childC = heap[child].c;
			if (board[currR][currC] + delta[currR / k][currC / k] > board[childR][childC] + delta[childR / k][childC / k]) break;
			else if (board[currR][currC] + delta[currR / k][currC / k] == board[childR][childC] + delta[childR / k][childC / k]) {
				// currR이 더 작으면, 바꿀 필요 없음
				if (currR < childR) break;
				else if (currR == childR) {
					// r이 같을 때, currC가 더 작으면 바꿀 필요 없음.
					if (currC < childC) break;
				}
			}
			
			Point tmp = heap[curr];
			heap[curr] = heap[child];
			heap[child] = tmp;

			curr = child;
		}

		return ret;
	}

};


Heap boundary[65][65];

void init(int N, int K, int mHeight[][MAX_MAP_SIZE])
{
	memset(board, 0, sizeof(board));
	memset(delta, 0, sizeof(delta));
	memset(boundary, 0, sizeof(boundary));
	// (N/K)+1 * (N/K)+1 로 구간들을 쪼갠다는 말임.
	k = K;
	//printf("%d x %d, K = %d\n", N, N, K);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = mHeight[i][j];
			Point tmp;
			tmp.r = i, tmp.c = j;
			boundary[i / K][j / K].pushHeap(tmp);
		}
	}

}

void destroy()
{

}

void query(Point mA, Point mB, int mCount, Point mTop[])
{

	// 기준이 되는 mA.
	int startR = (mA.r - 1);
	int startC = (mA.c - 1);
	
	// 바운더리를 찾으려면 여기서 K로 나눠줘야 한다.
	int startBoundaryR = (startR / k);
	int startBoundaryC = (startC / k);

	int endR = (mB.r);
	int endC = (mB.c);

	// 바운더리를 찾으려면 여기서 K로 나눠줘야 한다.
	int endBoundaryR = ((endR-k) / k);
	int endBoundaryC = ((endC-k) / k);


	// 일단 전체 힙을 준비한다.
	Heap totalHeap;

	// 그럼 그 바운더리에 있는 것들 중 mCount개씩 빼본다.
	for (int i = startBoundaryR; i <= endBoundaryR; i++) {
		for (int j = startBoundaryC; j <= endBoundaryC; j++) {
			//printf("바운더리 (%d, %d) 확인 중\n", i, j);
			
			Point tmp[5];
			for (int cnt = 0; cnt < mCount; cnt++) {
				tmp[cnt] = boundary[i][j].pop();
				totalHeap.pushHeap(tmp[cnt]);
			}

			// 끝나고 나면 다시 다 5개를 집어넣어야 한다.
			for (int cnt = 0; cnt < mCount; cnt++) {
				boundary[i][j].pushHeap(tmp[cnt]);
			}

		}
	}
	
	// 그럼 이제 그것 중에 mCount개를 빼서 결과에 반환한다.
	for (int i = 0; i < mCount; i++) {
		mTop[i] = totalHeap.pop();
		mTop[i].r++, mTop[i].c++;
	}
}

int getHeight(Point mP)
{
	return board[mP.r - 1][mP.c - 1] + delta[(mP.r - 1) / k][(mP.c - 1) / k];
}

// Boundary.
void work(Point mA, Point mB, int mH)
{
	// 기준이 되는 mA.
	int startR = (mA.r - 1);
	int startC = (mA.c - 1);

	// 바운더리를 찾으려면 여기서 K로 나눠줘야 한다.
	int startBoundaryR = (startR / k);
	int startBoundaryC = (startC / k);

	int endR = (mB.r);
	int endC = (mB.c);

	// 바운더리를 찾으려면 여기서 K로 나눠줘야 한다.
	int endBoundaryR = ((endR - k) / k);
	int endBoundaryC = ((endC - k) / k);

	//printf("바운더리 (%d,%d) ~ (%d, %d)까지\n", startBoundaryR, startBoundaryC, endBoundaryR, endBoundaryC);

	for (int i = startBoundaryR; i <= endBoundaryR; i++) {
		for (int j = startBoundaryC; j <= endBoundaryC; j++) {
			//printf("바운더리 (%d, %d) 확인 중\n", i, j);

			delta[i][j] += mH;
		}

	}

}