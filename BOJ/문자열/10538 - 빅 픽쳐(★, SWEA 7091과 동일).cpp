#include <cstdio>
#include <cstring>
#include <algorithm>
const int MOD = 1e9 + 7;

int T, H, W, N, M;
char ch;
char tmp[2001];
bool myPic[2000][2000], samPic[2000][2000];
int samLineHash[2000][2000];
int samRealHash[2000][2000];
int lineHash[2000];

int main() {
	scanf("%d %d %d %d", &H, &W, &N, &M);

	for (int i = 0; i < H; i++) {
		scanf("%s", tmp);
		for (int j = 0; j < W; j++) {
			if (tmp[j] == 'o') myPic[i][j] = true;
			else myPic[i][j] = false;
		}
	}
	for (int i = 0; i < N; i++) {
		scanf("%s", tmp);
		for (int j = 0; j < M; j++) {
			if (tmp[j] == 'o') samPic[i][j] = true;
			else samPic[i][j] = false;
		}
	}

	int ret = 0;

	// myPic을 해쉬화해야한다.
	for (int i = 0; i < H; i++) {
		lineHash[i] = 0;
		int power = 1;
		for (int j = 0; j < W; j++) {
			lineHash[i] = (lineHash[i] + (power * (myPic[i][W - 1 - j])));
			if (j != W - 1) power = (power * 37);
		}
		// printf("%d번째 줄 해싱 : %d\n", i, lineHash[i]);
	}

	// 그걸 다시 세로로 이어서 해싱. 여기서는 5831로 한다.
	int power = 1;
	int myHash = 0;
	for (int i = 0; i < H; i++) {
		myHash = (myHash + (lineHash[H - 1 - i] * power));
		if (i < H) power = (power * 5831);
	}

	// 그러면 이제 선생님 Pic도 해야한다.
	// 각 줄마다 구한다.
	for (int i = 0; i < N; i++) {
		// 일단 j = 0일 때는 직접 구한다.
		samLineHash[i][0] = 0;
		int power = 1;
		for (int j = 0; j < W; j++) {
			samLineHash[i][0] = (samLineHash[i][0] + (power * (samPic[i][W - 1 - j])));
			if (j < W - 1) power = (power * 37);
		}

		// 이제 이 정보를 이용해서 j = 1부터... j = M-1때까지 구한다.
		for (int j = 1; j < M; j++) {
			samLineHash[i][j] = (37 * (samLineHash[i][j - 1] - samPic[i][j - 1] * power) + (samPic[i][W - 1 + j]));
		}
	}

	// 이걸 다 끝나고 나면,
	// 가로 줄로만 본 해쉬값이 samLineHash[i][j]에 들어있다.
	// 그걸 세로로 합친 걸 samRealHash[i][j]에 저장한다.
	for (int j = 0; j <= M - W; j++) {

		// 이거를 세로로
		int power = 1;
		samRealHash[0][j] = 0;
		for (int i = 0; i < H; i++) {
			samRealHash[0][j] = (samRealHash[0][j] + (power * samLineHash[H - 1 - i][j]));
			if (i < H - 1) power = (power * 5831);
		}
		//printf("Naive하게 구한 samRealHash[0][%d] = %lld\n", j, samRealHash[0][j]);

		if (samRealHash[0][j] == myHash) {
			ret++;
		}

		// 이제 이 정보를 이용해서 i = 1 ~ i = N - H때까지 구한다.
		for (int i = 1; i <= N - H; i++) {
			//printf("samLineHash[%d - 1][%d] = %lld임\n", i, j, samLineHash[i - 1][j]);
			samRealHash[i][j] =
				(
					5831 * (samRealHash[i - 1][j] - power * samLineHash[i - 1][j]) + (samLineHash[H - 1 + i][j])
					);

			if (samRealHash[i][j] == myHash) {
				ret++;
			}
		}
	}
	printf("%d\n", ret);

}