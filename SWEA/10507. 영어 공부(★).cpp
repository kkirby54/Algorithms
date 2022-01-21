#include <cstdio>
#include <algorithm>

int T, N, P;
int arr[200001];
bool visited[1000001];

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &P);
		memset(visited, 0, sizeof(visited));

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);
			visited[arr[i]] = true;
		}

		int maxV = arr[N - 1];

		int lo = 0, hi = 0;
		int tmp = 0, ret = P + 1;
		// �׷���, ���� �� ������
		while (hi < maxV + 1) {
			// �湮�ѰŸ�, 
			if (visited[hi]) {
				tmp++;
				hi++;
				ret = std::max(ret, tmp);
			}
			// �湮�� ���ߴٸ�,
			else {
				if (P == 0) {
					ret = std::max(ret, tmp);
					if (visited[lo] == false) P++;
					lo++;
					tmp--;
				}
				else {
					P--;
					tmp++;
					hi++;
				}

			}

		}

		printf("#%d %d\n",t, ret);
	}
}