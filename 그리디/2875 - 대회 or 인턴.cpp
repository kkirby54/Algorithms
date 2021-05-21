#include <cstdio>

int main() {
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);

	// 여학생 N
	// 남학생 M

	// K명은 참여 못함

	int rest = 0;
	int cnt = 0;
	
	
	// 이 경우에는 M개팀 만들기 가능
	if (M * 2 <= N) {
		cnt = M;
		rest = (N - M * 2);
	}

	// 그럼 N/2개의 팀이 가능
	else if (M * 2 > N) {
		cnt = N / 2;
		rest += (M - N / 2) + (N - (N / 2) * 2);
	}

	// 잉여 인력을 빼버린다.
	K -= rest;

	// 그래서 음수면 cnt만 출력

	while (K > 0) {
		K -= 3;
		cnt--;
	}
	printf("%d", cnt);

}