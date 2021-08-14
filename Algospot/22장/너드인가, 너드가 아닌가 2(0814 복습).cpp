#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;

int C, N, ret;
int p, q;
map<int, int> nerds;

bool isDominated(int x, int y) {
	auto itr = nerds.lower_bound(x);

	if (itr == nerds.end()) return false;

	if (itr->second < y) return false;
	return true;
}

// (x,y)에 의해 지배되는 점을 삭제
void removeDominated(int x, int y) {
	// 지배가 되려면,
	// x보다 작으면서, y도 작아야 함.
	auto itr = nerds.lower_bound(x);
	if (itr == nerds.begin()) return;
	--itr;

	// 이제 itr은 나보다 작은 점들을 가리킨다.
	while (itr->first < x && itr->second < y) {
		if (itr == nerds.begin()) {
			nerds.erase(itr);
			break;
		}

		auto jtr = itr;
		jtr--;
		nerds.erase(itr);
		itr = jtr;
	}

}


int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		ret = 0;
		nerds.clear();

		for (int i = 0; i < N; i++) {
			scanf("%d %d", &p, &q);

			if (!isDominated(p, q)) {
				nerds[p] = q;
				removeDominated(p, q);
			}

			ret += nerds.size();

		}
		printf("%d\n", ret);
	}

}