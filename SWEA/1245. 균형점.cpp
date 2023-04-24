#include <cstdio>

int T, N;
int x[10], m[10];
double lo, hi;

inline double square(double a){
    return a * a;
}

int main(){
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++){
        scanf("%d", &N);

        for (int i = 0; i < N; i++){
            scanf("%d", x + i);
        }
        for (int i = 0; i < N; i++){
            scanf("%d", m + i);
        }

        printf("#%d ", tc);
        // N-1개의 균형점이 존재한다.
        for (int cnt = 0; cnt < N-1; cnt++){

            lo = x[cnt];
            hi = x[cnt + 1];
            // 0, ... cnt번째 vs cnt+1번째 ... N번째로 나뉜다.
            for (int dummy = 0; dummy < 100; dummy++){
                double mid = (lo + hi) / 2;

                double leftVal = 0;
                // mid를 기준으로 왼쪽에 있는 점.
                for (int i = 0; i <= cnt; i++){
                    leftVal += (m[i] / square(x[i] - mid));
                }

                // 오른쪽에 있는 점
                double rightVal = 0;
                for (int i = cnt + 1; i < N; i++){
                    rightVal += (m[i] / square(x[i] - mid));
                }

                if (leftVal == rightVal){
                    hi = mid;
                    break;
                }
                else if (leftVal < rightVal){
                    hi = mid;
                }
                else lo = mid;
            }

            printf("%.10lf ", hi);
        }
        printf("\n");
    }

}