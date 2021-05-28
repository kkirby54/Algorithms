#include <cstdio>
#include <algorithm>

int C, N, L;
int cost[1005];
double ret, val;

int main() {
	scanf("%d", &C);
	
	for (int c = 0; c < C; c++) {
		scanf("%d %d", &N, &L);
		
		int pSum[1005] = { 0 };
		double ret = 987654321;

		for (int i = 0; i < N; i++) {
			scanf("%d", cost + i);
			pSum[i + 1] += pSum[i] + cost[i];
		}

		//최소 L일 빌림.
		// L일 ~ N일이 범위

		int i = 0, j = 0;
		
		for (j = 0; L + i + j <= N; j++) {
			// L+j개의 합을 처리한다.
			//printf("L + %d개 합 처리 중..\n", j);
			for (int i = 0; L + i + j <= N; i++) {
				val = (double) pSum[L + i + j] - pSum[i];
				//printf("%d~%d의 합 : %lf\n", i, L + i + j-1, val);
				val = val / ((double)L + j);

				ret = std::min(ret, val);
			}
		}

		printf("%.12lf\n", ret);

	}


}