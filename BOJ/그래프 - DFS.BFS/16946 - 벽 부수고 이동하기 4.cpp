#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> P;

int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

int N, M;
int board[1000][1000];
bool visited[1000][1000];
int components[1000000];
int componentCnt;


int tmpCnt = 0;
void dfs(int r, int c){
    visited[r][c] = true;
    board[r][c] = componentCnt;
    tmpCnt++;

    for (int i = 0; i < 4; i++){
        int nR = r + dr[i];
        int nC = c + dc[i];

        if (nR < 0 || nR >= N || nC <0 || nC >= M) continue;
        if (visited[nR][nC]) continue;
        if (board[nR][nC] != 0) continue;

        dfs(nR, nC);
    }

}


int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            scanf("%1d", &board[i][j]);
            if (board[i][j] == 1)
                board[i][j] = -1;
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (board[i][j] == 0){
                // 컴포넌트 별로 관리한다.
                componentCnt++;
                tmpCnt = 0;

                dfs(i, j);

                components[componentCnt] = tmpCnt;
            }
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (board[i][j] == -1){
                // 4 방향을 보고, 컴포넌트 관리한다.
                int myComponents[4] = {0};
                int myCnt = 0;

                int totalValue = 0;

                for (int k =0; k <4; k++){
                    int nR = i + dr[k];
                    int nC = j + dc[k];

                    if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
                    if (board[nR][nC] == -1) continue;

                    // 어떤 컴포넌트인지 확인한다.
                    int currCompo = board[nR][nC];
                    bool alreadyIn = false;

                    for (int m = 0; m < myCnt; m++){
                        if (myComponents[m] == currCompo){
                            alreadyIn = true;
                            break;
                        }
                    }

                    if (!alreadyIn){
                        myComponents[myCnt++] = currCompo;
                        totalValue += components[currCompo];
                    }

                }
                printf("%d", (totalValue + 1) % 10);
            }
            else printf("0");
        }
        puts("");
    }
}
