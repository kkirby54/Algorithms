#include <cstdio>
#include <cstring>
#include <cmath>
int dp[19][19];

int nCr(int n, int r){
    if (n == r) return 1;
    if (r == 1) return n;

    int& ret = dp[n][r];
    if (ret != -1) return ret;

    return ret = nCr(n - 1, r - 1) + nCr(n - 1, r);
}

int primes[7] = {2,3,5,7,11,13, 17};

int T, A, B;

double getResult(int p){
    double pp = (double) p / 100;

    double sum = 0;
    for (int i = 0; i < 7; i++){
        int currPrime = primes[i];
        sum += nCr(18, currPrime) * pow(pp, currPrime) * pow(1-pp, 18 - currPrime);
    }

    return sum;
}

int main(){
    memset(dp, -1, sizeof(dp));


    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++){
        scanf("%d %d", &A, &B);

        double ret = getResult(A) + getResult(B) - getResult(A) * getResult(B);
        printf("#%d %6lf\n", tc, ret);
    }

}