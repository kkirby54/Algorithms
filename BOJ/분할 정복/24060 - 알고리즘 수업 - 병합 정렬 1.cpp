#include <cstdio>
#include <cstring>

int N, K, arr[500000];
int tmp[500000];
int cnt = 0;

void merge(int lo, int mid, int hi){
    int i = lo, j = mid + 1;
    int idx = 0;

    while (i <= mid && j <= hi){
        if (arr[i] <= arr[j]){
            tmp[idx++] = arr[i++];
        }
        else tmp[idx++] = arr[j++];
    }

    while (i <= mid){
        tmp[idx++] = arr[i++];
    }

    while (j <= hi){
        tmp[idx++] = arr[j++];
    }

    for (int i = lo; i <= hi; i++){
        arr[i] = tmp[i - lo];
        if (++cnt == K){
            printf("%d", arr[i]);
        }
    }
}

void merge_sort(int lo, int hi){
    if (lo < hi){
        int mid = (lo + hi) / 2;
        merge_sort(lo, mid);
        merge_sort(mid + 1, hi);
        merge(lo, mid, hi);
    }
}

int main(){
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++){
        scanf("%d", arr + i);
    }

    merge_sort(0, N-1);

    if (K > cnt) printf("-1");


}