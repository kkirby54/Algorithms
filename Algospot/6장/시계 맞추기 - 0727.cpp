#include <cstdio>
#include <algorithm>

using namespace std;

const int ButtonList[10][5] = {
	{0,1,2,-1,-1},
	{3,7,9,11,-1},
	{4,10,14,15,-1},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15,-1},
	{3,14,15,-1,-1},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};

int C, ret;
int clocks[16];

// index번 버튼을 해결한다.
// 안 누르거나, 1~3번 누르는 선택지.
void Sync(int index, int cnt) {
	if (index == 10) {
		for (int i = 0; i < 16; i++)
			if (clocks[i] != 0) return;
		// 다 0이라면 12시랑 마찬가지임.
		ret = min(ret, cnt);
		return;
	}

	// 0번에서 3번까지 누를 수 있음.
	int curr[5], curr_val[5];
	for (int i = 0; i < 5; i++) {
		curr[i] = ButtonList[index][i];

		if (curr[i] != -1)
			curr_val[i] = clocks[curr[i]];
	}

	for (int i = 0; i < 4; i++) {
		// i번 돌린다는 얘기임.

		for (int j = 0; j < 5; j++) {
			if (ButtonList[index][j] == -1) continue;

			//clock를 바꿔야함.
			clocks[ButtonList[index][j]] = (clocks[ButtonList[index][j]] + i * 3) % 12;
		}

		Sync(index + 1, cnt + i);

		// 이제 원래대로 돌려야 한다.
		for (int j = 0; j < 5; j++) {
			if (ButtonList[index][j] == -1) continue;
			clocks[ButtonList[index][j]] = curr_val[j];
		}

	}


}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		for (int i = 0; i < 16; i++) {
			scanf("%d", clocks + i);
		}

		ret = 987654321;

		Sync(0, 0);

		printf("%d\n", ret == 987654321 ? -1 : ret);
	}

}