#include <cstdio>
#include <algorithm>

int T, N;
int b[10], n[10];

int gcd(int p, int q){
    if (q == 0) return p;
    return gcd(q, p % q);
}

int lcm(int p, int q){
    int GCD = gcd(p, q);

    int d1 = p / GCD;
    int d2 = q / GCD;

    return GCD * d1 * d2;
}

int main(){
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++){
        scanf("%d", &N);
        for (int i = 0; i < N; i++){
            scanf("%d %d", b + i, n + i);
        }

        int currN = n[0];
        int currB = b[0];


        for (int i = 1; i < N; i++){

            int currVal;
            int x = 0;
            while (1){
                currVal = currN * x + currB;
                
                if (currVal % n[i] == b[i]){
                    break;
                }
                x++;
            }

            currN = lcm(currN, n[i]);
            currB = currVal;
        }

        printf("#%d %d\n", tc, currB);

    }
}