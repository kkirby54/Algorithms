#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

int main() {
	int N, arr[1001] = { 0 }, dp[1001];
	int prev[1001] = { 0 };

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	int ret = 1;
	int max_index = 0;

	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arr[i] > arr[j]) {
				
				if (dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					prev[i] = j;

				}
				if (ret < dp[i]){
					ret = dp[i];
					max_index = i;
				}

			}
		}
	}

	printf("%d\n", ret);
	//printf("제일 큰 값 : %d\n", arr[max_index]);

	// max_index부터 시작한다.
	// prev[max_index]

	//printf("max_index = %d, 값 : %d, 그 전 인덱스 : %d, 값:%d\n",
	//	max_index, arr[max_index], prev[max_index], arr[prev[max_index]]);

	std::vector<int> track;

	for (int i = 0; i < ret; i++) {
		//printf("%d ", arr[max_index]);
		track.push_back(arr[max_index]);
		max_index = prev[max_index];
	}

	for (auto itr = track.rbegin(); itr != track.rend(); itr++) {
		printf("%d ", *itr);
	}

}