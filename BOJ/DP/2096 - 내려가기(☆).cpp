#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;


int colMax[3], colMin[3], tempMax[3], tempMin[3];

int main() {
	int N, a, b, c;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &a, &b,&c);

		tempMax[0] = max(colMax[0], colMax[1]) + a;
		tempMax[1] = max(colMax[2], max(colMax[0], colMax[1])) + b;
		tempMax[2] = max(colMax[2], colMax[1]) + c;

		tempMin[0] = min(colMin[0], colMin[1]) + a;
		tempMin[1] = min(colMin[2], min(colMin[0], colMin[1])) + b;
		tempMin[2] = min(colMin[2], colMin[1]) + c;

		for (int j = 0; j < 3; j++) {
			colMax[j] = tempMax[j];
			colMin[j] = tempMin[j];
		}
	}

	sort(colMax, colMax + 3);
	sort(colMin, colMin + 3);
	printf("%d %d\n", colMax[2],colMin[0]);
	
}