#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> P;

int dr[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

char board[9][9];
bool visited[9][9];
vector<P> obstacles;

int main(){
    for (int i = 0; i < 8; i++){
        scanf("%s", board[i]);
    }

    // 밑에서 부터 obstacles를 push한다.
    for (int i = 7; i >= 0; i--){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == '#'){
                obstacles.push_back(P(i,j));
            }
        }
    }

    queue<P> Q;
    Q.push(P(7,0));
    visited[7][0] = true;

    while (!Q.empty()){
        int qSize = Q.size();
        for (int k = 0; k < qSize; k++){
            int currR = Q.front().first;
            int currC = Q.front().second;
            Q.pop();

            if (board[currR][currC] == '#') continue;

            if (currR == 0 && currC == 7){
                printf("1");
                return 0;
            }

            for (int i = 0; i < 9; i++){
                int nR = currR + dr[i];
                int nC = currC + dc[i];

                if (nR < 0 || nR >= 8 || nC <0 || nC >= 8) continue;
                if (board[nR][nC] == '#') continue;
                if (visited[nR][nC] && (currR != nR || currC != nC)) continue;

                Q.push(P(nR,nC));
            }
        }

        // obstacle들 내리기
        for (int i = 0; i < obstacles.size(); i++){
            int oR = obstacles[i].first;
            int oC = obstacles[i].second;

            if (oR == 0) board[oR][oC] = '.';
            else board[oR][oC] = board[oR-1][oC];

            if (oR < 7){
                board[oR+1][oC] = '#';
                obstacles[i].first++;
            }
        }

    }

    printf("0");

}