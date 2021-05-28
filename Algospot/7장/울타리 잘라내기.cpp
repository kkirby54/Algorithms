#include <cstdio>
#include <algorithm>

int height[20001];
int N;

// [left, right)라고 하자
int fence(int left, int right) {
	if (left == right) return height[left];

	int mid = (left + right) / 2;
	int Max_val = std::max(fence(left, mid), fence(mid+1, right));

	// cross의 경우를 따로 계산한다.
	
	// 처음 
	int left_index = mid, right_index = mid+1;
	int curr_height = std::min(height[left_index], height[right_index]);
	Max_val = std::max(Max_val, 2 * curr_height);

	// left나 right가 범위 내에 있으면 됨.
	while (left < left_index || right_index < right) {
		if (right_index < right && (left_index == left || height[left_index - 1] < height[right_index + 1])) {
			right_index++;
			curr_height = std::min(curr_height, height[right_index]);
		}
		else {
			left_index--;
			curr_height = std::min(curr_height, height[left_index]);
		}

		Max_val = std::max(Max_val, (right_index - left_index + 1) * curr_height);
	}

	
	return Max_val;
}

int main() {
	int C;
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			scanf("%d", height + i);
		}

		printf("%d\n", fence(0, N-1));
	}

}