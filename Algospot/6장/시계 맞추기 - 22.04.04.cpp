#include <cstdio>
#include <algorithm>
#include <cstring>

int switchList[10][5] = {
	{0,1,2,-1,-1},
	{3,7,9,11,-1},
	{4, 10, 14, 15, -1},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15, -1},
	{3, 14, 15, -1, -1},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13}
};

int timeNow[16];
int switchCnt[10]; // 눌린 횟수.
int C, ret;

// currSwitch를 켰을 때.
void timeFlow(int currSwitch, int cnt) {
	// currSwitch를 키고, cnt++

	// 초기확인, 다 돌았는데, 전부 0
	bool isFin = true;
	for (int i = 0; i < 16; i++) {
		if (timeNow[i] != 0) {
			isFin = false;
			break;
		}
	}
	if (isFin) {
		ret = std::min(ret, cnt);
		return;
	}

	for (int i = currSwitch; i < 10; i++) {
		if (switchCnt[i] >= 3) continue;

		// i번째 스위치를 켜는 작업을 하고, 넘긴다.

		for (int j = 0; j < 5 && switchList[i][j] != -1; j++) {
			int currClock = switchList[i][j];
			timeNow[currClock] = (timeNow[currClock] + 3) % 12;
		}
		switchCnt[i] += 1;

		timeFlow(i, cnt + 1);

		// 되돌리기
		for (int j = 0; j < 5 && switchList[i][j] != -1; j++) {
			int currClock = switchList[i][j];
			timeNow[currClock] = (timeNow[currClock] - 3 + 12) % 12;
		}
		switchCnt[i] -= 1;

	}


}

int main() {
	scanf("%d", &C);
	while (C--) {
		for (int i = 0; i < 16; i++) {
			scanf("%d", timeNow + i);
			timeNow[i] %= 12;
		}

		ret = 987654321;
		memset(switchCnt, 0, sizeof(switchCnt));

		// timeNow를 조작.
		// 10개의 스위치를 0, 1, 2, 3 => 4^10의 케이스.
		timeFlow(0, 0);

		printf("%d\n", (ret == 987654321) ? -1 : ret);
	}

}