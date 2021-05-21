#include <cstdio>
#include <string>
#include <queue>
#include <algorithm>

int T;
int ret = 10000000;
int start, end;
bool isPossible;
bool isPrime[10000];
bool visited[10000] = { 0 };

int to_int(std::string s) {
	int ret = 0;
	int digit = 1;

	for (int i = 3; i >=0; i--) {
		ret += (s[i]-'0') * digit;
		digit *= 10;
	}
	return ret;
}

void bfs(int s) {

	std::queue<int> Q;
	Q.push(s);
	visited[s] = true;

	std::string str = std::to_string(s);

	// curr에서 시작해 바꾼다.
	// '1073'
	int level = 0;
	int curr;

	while (!Q.empty()) {
		int qSize = Q.size();
		//printf("==%d==\n", level);
		for (int k = 0; k < qSize; k++) {
			curr = Q.front();
			Q.pop();

			if (curr == end) {
				ret = std::min(ret, level);
				return;
			}

			// curr을 요리조리 바꾼다.
			for (int i = 0; i < 4; i++) {
				str = std::to_string(curr);

				// str[i]를 0,1,2,3,4,5, ..로 바꾼다.
				for (int j = 0; j < 10; j++) {
					if (i == 0 && j == 0) continue;

					str[i] = j + '0';
					// 그 다음에 str을 숫자로 변환
					int next = to_int(str);

					if (visited[next]) continue;
					if (!isPrime[next]) continue;
					
					Q.push(next);
					visited[next] = true;
				}


			}

		}
		level++;
	}

	isPossible = false;
}

int main() {
	scanf("%d", &T);
	std::fill(isPrime, isPrime + 10000, true);

	// 1000 ~ 9999까지의 소수를 찾는다.
	for (int i = 4; i < 10000; i += 2) {
		isPrime[i] = false;
	}

	for (int i = 3; i < 10000; i += 2) {
		if (!isPrime[i]) continue;

		for (int j = i * i; j < 10000; j += i * 2) {
			isPrime[j] = false;
		}
	}


	// 입력 받기
	for (int t = 0; t < T; t++) {
		scanf("%d %d", &start, &end);

		isPossible = true;
		ret = 10000000;
		std::fill(visited, visited + 10000, false);

		// 이제 각 자리를 바꾼다.
		bfs(start);

		if (isPossible)
			printf("%d\n", ret);
		else puts("Impossible");

	}

}