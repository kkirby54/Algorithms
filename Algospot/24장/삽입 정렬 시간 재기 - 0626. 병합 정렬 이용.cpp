#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int C, N;
int A[50000];

long long mergeSort(int left, int right) {
	if (left >= right) return 0;

	int mid = (left + right) / 2;
	long long ret = mergeSort(left, mid) + mergeSort(mid + 1, right);
	// 반갈죽을 한다.
	// 여기까지 하면 [left, mid], [mid+1, right]가 정렬되었다.

	int leftIdx = left, rightIdx = mid + 1;

	vector<int> tmp(right - left + 1);
	int tmpIdx = 0;

	while (leftIdx <= mid && rightIdx <= right) {
		if (A[leftIdx] > A[rightIdx]) {
			// 그럼 right를 박는다.
			// 여기서.. inversion이 일어나는 케이스는
			// right가 먼저 갖다 박을 때임. 그 때 mid - leftIdx + 1개 만큼의 inversion이 발생한다.
			ret += (mid - leftIdx + 1);
			tmp[tmpIdx++] = A[rightIdx++];
		}
		else tmp[tmpIdx++] = A[leftIdx++];
	}

	while (leftIdx <= mid) {
		tmp[tmpIdx++] = A[leftIdx++];
	}

	while (rightIdx <= right) {
		tmp[tmpIdx++] = A[rightIdx++];
	}
	
	for (int i = left; i <= right; i++) {
		A[i] = tmp[i - left];
	}

	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", A + i);
		}

		printf("%lld\n", mergeSort(0, N - 1));

	}

}