#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int,int> P;

int dr[] = {-1,1,0,0};
int dc[] = {0, 0, -1, 1};

int N, r, c;
int level, retR, retC;
int eatingCnt = 0;
int babySize = 2;
int board[21][21];
bool visited[21][21];

// currR, currC부터 시작해서 최단 거리로 먹을 수 있는 것들 중,
// r, c가 가장 작은 것 return
bool canEat(int currR, int currC){
    queue<P> Q;
    Q.push(P(currR, currC));
    memset(visited, false, sizeof(visited));

    level = 0;
    bool isFound = false;

    retR = 21, retC = 21;
    while (!Q.empty()){
        int qSize = Q.size();

        isFound = false;

        while (qSize--){
            int cR = Q.front().first;
            int cC = Q.front().second;
            Q.pop();
            //printf("%d,%d에서 확인합니다\n", cR, cC);

            for (int i = 0; i < 4; i++){
                int nR = cR + dr[i];
                int nC = cC + dc[i];
                if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
                if (visited[nR][nC]) continue;

                if (board[nR][nC] > babySize) continue;
                if (board[nR][nC] == babySize || board[nR][nC] == 0){
                    Q.push(P(nR,nC));
                    visited[nR][nC] = true;
                }
                else{
                    // 먹었음을 표시.
                    isFound = true;

                    if (retR > nR){
                        retR = nR;
                        retC = nC;
                    }
                    else if (retR == nR){
                        if (retC > nC)
                            retC = nC;
                    }
                }
            }
        }
        level++;

        if (isFound) break;
    }

    return isFound;
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 9){
                board[i][j] = 0;
                r = i;
                c = j;
            }
        }
    }

    int tick = 0;
    while (1){
        //printf("진행 중..tick = %d\n", tick);
        if (canEat(r, c)){
            r = retR;
            c = retC;
            tick += level;
            eatingCnt++;
            if (eatingCnt == babySize){
                eatingCnt = 0;
                babySize++;
            }

            board[r][c] = 0;
        }
        else break;
    }

    printf("%d\n", tick);

}