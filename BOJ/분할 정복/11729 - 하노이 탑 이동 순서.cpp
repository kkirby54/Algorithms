#include <cstdio>
#include <algorithm>

int N;

int hanoi(int curr) {
	if (curr == 1) return 1;

	return 2*hanoi(curr - 1) + 1;
}
	
void track(int curr, int sub, int goal, int size) {
	if (size == 1) {
		printf("%d %d\n", curr, goal);
		return;
	}

	// 위에 N-1개를 curr -> sub로 옮기기
	track(curr, sub, goal, size - 1);

	// 남은 1개를 curr -> goal로 옮기기
	track(curr, goal, sub, 1);

	// N-1개를 sub -> goal로 옮기기
	track(sub, goal, curr, size - 1);

}


int main() {
	scanf("%d", &N);
	printf("%d\n", hanoi(N));
	track(1, 2,3, N);

}