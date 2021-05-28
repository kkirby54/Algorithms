#include <cstdio>
#include <algorithm>

int C, N, L;
int cost[1005];
double ret, val;

int main() {
	scanf("%d", &C);
	
	for (int c = 0; c < C; c++) {
		scanf("%d %d", &N, &L);
		
		double ret = 987654321;
		int day;

		for (int i = 0; i < N; i++) {
			scanf("%d", cost + i);
		}

		for (int i = 0; i <= N - L; i++) {
			day = 1;
			val = 0;

			for (int j = i; j < N; j++) {
				val += cost[j];

				if (day >= L) {
					ret = std::min(ret, val / (double)day);
				}

				day++;
			}

		}
		

		printf("%.12lf\n", ret);

	}


}