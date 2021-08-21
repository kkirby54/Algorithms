#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
using namespace std;
typedef pair<int, int> P;

string N;
int K;
set<string> visited;

int main() {
	cin >> N >> K;

	queue<string> Q;
	Q.push(N);
	visited.insert(N);
	int M = N.size();
	string ret = "";
	
	if (M == 1 || (M==2&&N[1] == '0')) {
		cout << "-1"; return 0;
	}

	int k = 0;
	while (!Q.empty() && k <= K) {
		int qSize = Q.size();
		//cout << "=====K: " << k << "====\n";
		for (int q = 0; q < qSize; q++) {
			string curr = Q.front();
			Q.pop();

			if (k % 2 == (K) % 2) {
				ret = max(ret, curr);
			}

			for (int i = 0; i < M; i++) {
				// i, j를 바꾼다.
				for (int j = i + 1; j < M; j++) {
					// 단, i == 0일 때 curr[j] = 0이면
					if (i == 0 && curr[j] == '0') continue;

					// 바꿔도 똑같다면?
					// 모든 K에 대해 수행할 수 있다는 말임.
					if (curr[i] == curr[j]) {
						ret = max(ret, curr);
					}
					else {
						swap(curr[i], curr[j]);
						
						if (visited.find(curr) == visited.end()) {
							Q.push(curr);
							visited.insert(curr);

						}
						swap(curr[i], curr[j]);
					}
				}
			}
		}
		k++;
	}
	cout << ret;


}