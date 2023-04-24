#include <cstdio>

int N, board[100][100];

int main(){
    for (int tc = 1; tc <= 10; tc++){
        scanf("%d", &N);

        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                scanf("%d", &board[i][j]);
            }
        }

        int ret = 0;
        // c열에 대해
        for (int c = 0; c < N; c++){

            bool hasOne = false;
            int num = 0;

            for (int r = 0; r < N; r++){
                // 1나오다가 2이면 lock.
                if (board[r][c] == 2){
                    if (hasOne){
                        num++;
                        hasOne = false;
                    }
                }
                    // 1였다면,
                else if (board[r][c] == 1){
                    if (!hasOne) hasOne = true;
                }
            }
            ret += num;
        }

        printf("#%d %d\n", tc, ret);

    }

}