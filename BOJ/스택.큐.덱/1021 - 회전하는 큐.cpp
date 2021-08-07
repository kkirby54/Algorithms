#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;
int N, M, val, ret;

int main() {
	// 1부터 N까지 있음.
	scanf("%d %d", &N, &M);
	deque<int> DQ;

	for (int i = 1; i <= N; i++) {
		DQ.push_back(i);
	}

	for (int i = 0; i < M; i++) {
		scanf("%d", &val);
		// val값을 갖는 걸 뺀다.
		int H_Dist = 0;
		auto Hitr = DQ.begin();
		while (*Hitr != val) {
			H_Dist++;
			Hitr++;
		}

		int T_Dist = 1;
		auto Titr = DQ.rbegin();
		while(*Titr != val) {
			T_Dist++;
			Titr++;
		}

		if (H_Dist < T_Dist) {
			// 이러면 앞에서부터 빼서, 뒤로 넣는다.
			while (*DQ.begin() != val) {
				int data = DQ.front();
				DQ.pop_front();
				DQ.push_back(data);
			}
			DQ.pop_front();
		}
		else {
			// 뒤에서부터 빼서, 앞으로 넣는다.
			while (*DQ.begin() != val) {
				int data = DQ.back();
				DQ.pop_back();
				DQ.push_front(data);
			}
			DQ.pop_front();
		}
		ret += min(T_Dist, H_Dist);
	}
	printf("%d\n", ret);
}