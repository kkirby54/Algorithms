#include <cstdio>
#include <algorithm>

int N, temp, arr[10001];

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &temp);
		arr[temp] += 1;
	}

	for (int i = 0; i <= 10000; i++) {
		if (arr[i]){
			for (int j = 0; j < arr[i]; j++)
				printf("%d\n", i);
		}
	}

}