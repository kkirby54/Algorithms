#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

char str1[1005], str2[1005], ret[1005];
int len1, len2, nums;
int dp[1005][1005];

int LCS(int curr1, int curr2) {
	int& ret = dp[curr1][curr2];
	if (ret != -1) return ret;
	if (curr1 == len1 || curr2 == len2) return 0;

	if (str1[curr1] == str2[curr2]) {
		ret = LCS(curr1 + 1, curr2 + 1) + 1;
	}
	ret = std::max(LCS(curr1 + 1, curr2), LCS(curr1, curr2 + 1));

	return ret;
}


void printAnswer(int curr1, int curr2) {
	if (curr1 == len1 || curr2 == len2) return;

	if (str1[curr1] == str2[curr2] && LCS(curr1, curr2) == LCS(curr1 + 1, curr2 + 1) + 1) {
		ret[nums++] = str1[curr1];
		printAnswer(curr1 + 1, curr2 + 1);
		return;
	}
	else if (LCS(curr1, curr2) == LCS(curr1 + 1, curr2)) {
		printAnswer(curr1 + 1, curr2);
		return;
	}
	else {
		printAnswer(curr1, curr2 + 1);
		return;
	}

}

int main() {
	scanf("%s %s", str1, str2);

	len1 = strlen(str1);
	len2 = strlen(str2);

	for (int i = 0; i < 1005; i++) {
		for (int j = 0; j < 1005; j++)
			dp[i][j] = -1;
	}

	printf("%d\n", LCS(0, 0));
	if (LCS(0, 0) != 0) {
		printAnswer(0, 0);
		printf("%s", ret);
	}

}