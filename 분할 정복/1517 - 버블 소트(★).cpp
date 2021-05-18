#include <cstdio>
#include <algorithm>

int arr[500000];
int sorted[500000];

long long ret;

void mergeSort(int s, int e) {
	if (s >= e) return;

	int mid = (s + e) / 2;

	mergeSort(s, mid);
	mergeSort(mid + 1, e);

	int index1 = s, index2 = mid + 1;
	int k = s;

	while (index1 <= mid && index2 <= e) {
		if (arr[index1] <= arr[index2]) {
			sorted[k++] = arr[index1++];
		}
		else {
			sorted[k++] = arr[index2++];
			// 그럼 이제 바꾼 횟수를 더하기
			ret += (long long) mid - index1 + 1;
		}
	}

	while (index1 <= mid) {
		sorted[k++] = arr[index1++];
	}
	while (index2 <= e) {
		sorted[k++] = arr[index2++];
	}

	for (int i = s; i <= e; i++) {
		arr[i] = sorted[i];
	}

}


int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	mergeSort(0, N-1);

	/*
	for (int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	*/

	printf("%lld", ret);
}