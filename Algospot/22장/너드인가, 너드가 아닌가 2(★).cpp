#include <cstdio>
#include <algorithm>
#include <map>

int C, N, r, c;
std::map<int, int> coords;

// 새 점 (x,y)가 coords에 있는 애들에게 정복당하는지 or not 반환
bool isDominated(int x, int y) {
	auto itr = coords.lower_bound(x);

	// 바로 오른쪽 애 뽑아가지고 y좌표 비교.
	// 같아도 됨. 

	// 못찾으면 그냥 false.
	if (itr == coords.end()) return false;

	if ((*itr).second > y) return true;

	return false;
}

// 새로운 점 (x, y)에 의해 지배되는 점들을 지운다.
void removeDominated(int x, int y) {

	auto itr = coords.lower_bound(x);
	if (itr == coords.begin()) return;

	// 있다면 일단 --로 더 작은 애들을 본다.
	--itr;

	// itr은 (x,y) 바로 왼쪽에 있는 점.
	while (1) {
		//  *
		//      *
		//               *(x,y)
		//          *      
		//                    *
		if (itr->second > y) break;

		// 아니면, 지워야함.
		// 이전 점이 없으면 itr만 지우고 종료
		if (itr == coords.begin()) {
			coords.erase(itr);
			break;
		}
		else {
			auto jtr = itr;
			--jtr;
			coords.erase(itr);
			itr = jtr;
		}
	}
}

int registered(int x, int y) {
	// (x,y)가 지배되는 경우에는 x,y 버려
	if (isDominated(x, y)) return coords.size();
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		coords.clear();

		int sum = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &r, &c);
			sum += registered(r, c);
		}
		printf("%d\n", sum);
	}

}