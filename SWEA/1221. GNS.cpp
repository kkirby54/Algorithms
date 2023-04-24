#include <cstdio>
#include <algorithm>

int T, N;
char tmp[4];
char numToStr[10][4] = {
        "ZRO",
        "ONE",
        "TWO",
        "THR",
        "FOR",
        "FIV",
        "SIX",
        "SVN",
        "EGT",
        "NIN"
};

int nums[10000];

int main(){

    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++){
        scanf("%s %d", tmp, &N);

        for (int i = 0; i < N; i++){
            scanf("%s", tmp);

            int val;
            if (tmp[0] == 'Z')
                val = 0;
            else if (tmp[0] == 'O')
                val = 1;
            else if (tmp[0] == 'T'){
                if (tmp[1] == 'W') val = 2;
                else val = 3;
            }
            else if (tmp[0] == 'F'){
                if (tmp[1] == 'O') val = 4;
                else val = 5;
            }
            else if (tmp[0] == 'S'){
                if (tmp[1] == 'I') val = 6;
                else val = 7;
            }
            else if (tmp[0] == 'E')
                val = 8;
            else val = 9;

            nums[i] = val;
        }

        std::sort(nums, nums + N);

        printf("#%d\n", tc);
        for (int i = 0; i < N; i++){
            printf("%s ", numToStr[nums[i]]);
        }
        printf("\n");

    }

}
