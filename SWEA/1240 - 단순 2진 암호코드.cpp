#include <cstdio>
#include <cstring>
#include <algorithm>
int N, M;
char board[51][101];

int decode[10] = {
        0b1101,
        0b11001,
        0b10011,
        0b111101,
        0b100011,
        0b110001,
        0b101111,
        0b111011,
        0b110111,
        0b1011
};

int s_r, s_c;

int transform(){
    int ret = 0;
    int sumVal = 0;

    int cnt = 0;
    for (int i = s_c; i < s_c + 56; i+=7){
        int decimalVal = 0;
        int digit = 1;
        for (int j = i+6; j >= i; j--){
            decimalVal += ((board[s_r][j] -'0') * digit);
            digit *= 2;
        }

        int j;
        for (j = 0; j < 10; j++){
            if (decimalVal == decode[j]){
                break;
            }
        }

        if (cnt++ % 2 == 0)
            ret += 3*j;
        else ret += j;

        sumVal += j;
    }

    return ret % 10 == 0 ? sumVal : 0;
}

int main(){
    int T;
    scanf("%d", &T);

    for(int tc = 1; tc <= T; ++tc) {
        scanf("%d %d", &N, &M);

        bool find = false;
        for (int i = 0; i < N; i++){
            scanf("%s", board[i]);

            // 시작 지점 찾기
            if (find) continue;
            for (int j = M-1; j >= 0; j--){
                if (board[i][j] == '1'){
                    s_r = i;
                    s_c = j-55;
                    find = true;
                    break;
                }
            }
        }

        printf("#%d %d\n", tc, transform());
    }
}