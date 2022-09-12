#include <cstdio>
#include <cstring>

int T;
char S[1005];

int cnt = 0;

int recursion(const char *s, int l, int r){
    cnt++;
    if(l >= r) return 1;
    else if(s[l] != s[r]) return 0;
    else return recursion(s, l+1, r-1);
}

int isPalindrome(const char *s){
    return recursion(s, 0, strlen(s)-1);
}


int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%s", S);
        cnt = 0;

        int ret = isPalindrome(S);
        printf("%d %d\n", ret, cnt);

    }

}