#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>

char nums[100005];

int main() {
	scanf("%s", nums);

	int len = strlen(nums);
	int ret = 0;
	bool isPossible = false;

	for (int i = 0; nums[i]; i++) {
		if (nums[i] -'0' == 0) {
			isPossible = true;
		}
		ret += nums[i] -'0';
	}

	if (ret % 3 != 0) isPossible = false;

	if (isPossible) {
		std::sort(nums, nums + len, std::greater<int>());
		for (int i = 0; i < len; i++) {
			printf("%d", nums[i]-'0');
		}
	}
	else printf("-1");

}