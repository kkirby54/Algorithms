#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
const int INF = 1000000005;
typedef std::pair<int, int> P;

int N, arr[1000005];
std::vector<P> track;
std::vector<int> ret;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	ret.push_back(arr[0]);
	track.push_back(P(0, arr[0]));

	int mx_index = 0;

	for (int i = 1; i < N; i++) {
		if (arr[i] > ret.back()) {
			ret.push_back(arr[i]);
			track.push_back(P(++mx_index, arr[i]));
		}
		else {
			auto itr = std::lower_bound(ret.begin(), ret.end(), arr[i]);
			int loc = std::lower_bound(ret.begin(), ret.end(), arr[i]) - ret.begin();

			track.push_back(P(loc, arr[i]));
			*itr = arr[i];
		}
	}

	printf("%d\n", ret.size());

	std::stack<int> s;
	int curr = ret.size() - 1;

	for (int i = N - 1; i >= 0; i--) {
		if (track[i].first == curr) {
			//printf("%d\n", track[i].second);
			s.push(track[i].second);
			curr--;
		}
	}

	while (!s.empty()) {
		printf("%d ", s.top());
		s.pop();
	}

}