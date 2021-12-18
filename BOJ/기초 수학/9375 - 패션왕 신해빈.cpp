#include <iostream>
#include <map>
#include <vector>
using namespace std;
int T, N, category_nums;
map<string, int> HashM;
int M[35];
string item, category;

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		HashM.clear();
		fill(M, M + N + 1, 0);
		category_nums = 0;

		for (int i = 1; i <= N; i++) {
			cin >> item >> category;
			if (HashM[category] == 0) {
				HashM[category] = ++category_nums;
			}
			M[HashM[category]]++;
		}

		int ret = 1;
		for (int i = 1; i <= category_nums; i++) {
			ret *= (M[i] + 1);
		}
		printf("%d\n", ret - 1);
	}

}