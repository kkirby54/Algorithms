#include <iostream>
#include <cstring>
#include <cmath>

#define MAX_N (10000)
#define MAX_M (10)

int N, M;
long long digit;
long long bitSave[MAX_N][2];
long long totalBits[MAX_N];

void init(int n, int m, char mImageList[MAX_N][MAX_M][MAX_M])
{
	N = n; M = m;

	memset(bitSave, 0, sizeof(bitSave));
	memset(totalBits, 0, sizeof(totalBits));
	
	for (int i = 0; i < N; i++) {
		int cnt = 0;
		int idx = 0;
		digit = 1;
		for (int j = 0; j < M; j++) {
			for (int k =0; k < M; k++) {
				bitSave[i][idx] += (1LL * digit * mImageList[i][j][k]);
				digit *= 2;
				// 최대 64비트. 편의상 그냥 50비트에서 끊는다.
				if (++cnt == 50) {
					idx++;
					digit = 1;
				}
				if (mImageList[i][j][k] == 1) totalBits[i]++;
			}
		}
	}

}
int findImage(char mImage[MAX_M][MAX_M])
{
	long long targetBit[2] = { 0 };
	int bitNums = 0;
	int cnt = 0, idx = 0;
	long long digit = 1;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			targetBit[idx] += (digit * mImage[i][j]);
			digit *= 2;

			if (++cnt == 50) {
				idx++;
				digit = 1;
			}
			if (mImage[i][j] == 1) bitNums++;
		}
	}

	int ret = -1;
	int minV = 100000;
	for (int i = 0; i < N; i++) {
		if (abs(totalBits[i] - bitNums) > 2) continue;

		int incorrectNums = 0;

		// vscode에서는 popcnt, gcc에서는 __builtin_popcount.
		incorrectNums += __popcnt64(bitSave[i][0] ^ targetBit[0]);
		incorrectNums += __popcnt64(bitSave[i][1] ^ targetBit[1]);

		if (incorrectNums < minV) {
			minV = incorrectNums;
			ret = i + 1;
			if (incorrectNums == 0)
				break;
		}
	}

	return ret;
}