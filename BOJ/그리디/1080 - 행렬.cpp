#include <cstdio>
using namespace std;

int N, M;
int A[50][50];
int B[50][50];
int C[50][50];  // A와 B의 차이를 기록한다.

void reverseMat(int r, int c){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            C[r + i][c + j] = !C[r + i][c + j];
        }
    }
}

int main(){
    //freopen("test.txt", "r", stdin);

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            scanf("%1d", &A[i][j]);
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            scanf("%1d", &B[i][j]);
            if (A[i][j] != B[i][j])
                C[i][j] = 1;
        }
    }

    int cnt = 0;
    // 위에서부터 보면서, C[i][j]가 1인지 확인한다.
    for (int i = 0; i < N-2; i++) {
        for (int j = 0; j < M - 2; j++) {
            int curr = C[i][j];
            if (curr == 1) {
                reverseMat(i, j);
                cnt++;
            }
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (C[i][j] == 1){
                printf("-1");
                return 0;
            }
        }
    }
    printf("%d\n", cnt);

}