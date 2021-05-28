#include <cstdio>
#include <vector>

int C, in;
int clock[17];
int ans;

std::vector<int> Switch[10] = {
	{0,1,2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15}, 
	{1,2,3,4,5}, 
	{3,4,5,9,13 }
};

// Switch[i]로 접근하면
// for (int e : switch[i])에 대해
// clock[e]를 3 늘리면 됨.

// 확인하는 함수
bool isOK() {
	for (int i = 0; i < 16; i++)
		if (clock[i] != 0) return false;

	return true;
}

void SyncClock(int curr, int currentCnt) {
	// 마지막 종료 조건.
	if (curr == 10) {
		if (isOK()) {
			ans = std::min(ans, currentCnt);
		}
		return;
	}
	// curr 3번 쓰기
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] + 9) % 12;
	}
	SyncClock(curr + 1, currentCnt + 3);

	// 되돌리기
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] - 9 + 12) % 12;
	}

	// curr 안 쓰기
	SyncClock(curr + 1, currentCnt);

	// curr 쓰기
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] + 3) % 12;
	}
	SyncClock(curr + 1, currentCnt + 1);

	// 되돌리기
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] - 3 + 12) % 12;
	}
	

	// curr 2번 쓰기
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] + 6) % 12;
	}
	SyncClock(curr + 1, currentCnt + 2);
	for (int e : Switch[curr]) {
		clock[e] = (clock[e] - 6 + 12) % 12;
	}

}

int main() {
	scanf("%d", &C);

	for (int tc = 0; tc < C; tc++) {
		for (int i = 0; i < 16; i++) {
			scanf("%d", &in);
			clock[i] = in % 12;
		}

		// 모두를 0 0 0 0 0 0 0 0을 만들어야 함.
		ans = 987654321;

		SyncClock(0, 0);

		printf("%d\n", ans == 987654321 ? -1 : ans);
	}
	

}