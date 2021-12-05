#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N;
bool isFin;
vector<int> ret;

void backtrack(int digits) {
	// Base case
	if (isFin) return;
	if (digits == N) {
		if (ret.size() != N) return;
		for (int e : ret) printf("%d", e);
		//puts("");
		isFin = true;
		ret.pop_back();
		return;
	}

	// 1, 2, 3만 사용 가능.
	for (int i = 1; i <= 3; i++) {
		ret.push_back(i);

		int len = ret.size();
		bool isSame = false;

		// j개 만큼을 비교한다.
		for (int j = 1; j <= len / 2; j++) {
			// 다 같아야 함.
			isSame = true;
			for (int k = 0; k < j; k++) {
				if (ret[len - j + k] != ret[len - j - j + k]) {
					isSame = false;
					break;
				}
			}

			// 다 같다면, 이건 빼야함. 무조건 반복되는 수열이라서.
			if (isSame) {
				break;
			}
		}

		// 반복되는게 있다면, 지금 들어간 걸 빼야함.
		if (isSame) {
			ret.pop_back();
		}
		else {
			backtrack(digits + 1);
		}
	}

	ret.pop_back();
}

int main() {
	scanf("%d", &N);

	backtrack(0);

}
