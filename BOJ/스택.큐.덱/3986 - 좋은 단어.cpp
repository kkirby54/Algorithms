#include <cstdio>
#include <algorithm>
#include <stack>

int N, ret = 0;
char str[100001];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		std::stack<char> S;
		for (int j = 0; str[j]; j++) {
			if (S.empty()) S.push(str[j]);
			else {
				if (S.top() == str[j]) {
					while (!S.empty() && S.top() == str[j]) {
						S.pop();
					}
				}
				else S.push(str[j]);
			}
		}
		if (S.empty()) ret++;
	}
	printf("%d\n", ret);
	
}