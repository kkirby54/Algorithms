#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
const int INF = 987654321;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};

int W, H;
char board[101][101];
int dist[101][101][4];
int sR = -1, sC = -1, eR, eC;
queue<P> Q;

int main(){
    scanf("%d %d", &W, &H);

    for (int i = 0; i < H; i++){
        scanf("%s", board + i);
        for (int j = 0; j < W; j++){
            if (board[i][j] == 'C'){
                if (sR != -1){
                    eR = i;
                    eC = j;
                }
                else{
                    sR = i;
                    sC = j;
                }
            }
        }
    }

    for (int i = 0; i < 101; i++){
        for (int j = 0; j < 101; j++){
            for (int k = 0; k < 4; k++)
                dist[i][j][k] = INF;
        }
    }

    // sR, sC, 0123에서 시작
    Q.push(P(sR * 101 + sC, 0));
    Q.push(P(sR * 101 + sC, 1));
    Q.push(P(sR * 101 + sC, 2));
    Q.push(P(sR * 101 + sC, 3));

    dist[sR][sC][0] = dist[sR][sC][1] = dist[sR][sC][2] = dist[sR][sC][3] = 0;

    while (!Q.empty()){
        int currR = Q.front().first / 101;
        int currC = Q.front().first % 101;
        int direction = Q.front().second;
        Q.pop();

        // 여기서 4방향으로.
        for (int k = 0; k < 4; k++){
            int nR = currR + dr[k];
            int nC = currC + dc[k];

            if (nR < 0 || nR >= H || nC < 0 || nC >= W) continue;
            if (board[nR][nC] == '*') continue;

            // nR, nC가 온 방향이 중요함.
            if (k == direction){
                // 같다면,
                if (dist[nR][nC][k] > dist[currR][currC][k]){
                    dist[nR][nC][k] = dist[currR][currC][k];
                    Q.push(P(nR * 101 + nC, k));
                }
            }
            // 아니라면, k로 방향을 꺾어야 하는 케이스
            else{
                if (dist[nR][nC][k] > dist[currR][currC][direction] + 1){
                    dist[nR][nC][k] = dist[currR][currC][direction] + 1;
                    Q.push(P(nR * 101 + nC, k));
                }
            }
        }
    }
    int ret = INF;
    for (int i = 0; i < 4; i++){
        ret = min(ret, dist[eR][eC][i]);
    }
    printf("%d", ret);
}