#include <cstdio>
#include <algorithm>

int N;
char board[9][9];

int checkPalindrome(int r, int c, bool direction){
    if (direction){
        // 가로로 먼저
        //.0printf("%d~%d간다, ", c, (c+N)/2);
        for (int j = c; j < c + (N / 2); j++){
            // board[r][j] vs board[r][c+N-1 - j]
            if (j >= 8 || c + N - (j - c + 1) >= 8) return 0;

            if (board[r][j] != board[r][c + N - (j - c + 1)]) return 0;
        }
        return 1;
    }
    else{
        for (int i = r; i < r + (N / 2); i++){
            // board[r][i] vs board[r][c+N-1 - i]
            if (i >= 8 || r + N - (i - r + 1) >= 8) return 0;

            if (board[i][c] != board[r + N - (i - r + 1)][c]) return 0;
        }
        return 1;
    }

}

int main(){

    for (int tc = 1; tc <= 10; tc++){
        scanf("%d", &N);
        for (int i = 0; i < 8; i++){
            scanf("%s", board[i]);
        }
        int ret = 0;

        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                ret += checkPalindrome(i, j, 0);
                ret += checkPalindrome(i, j, 1);
            }
        }

        printf("#%d %d\n", tc, ret);
    }
}