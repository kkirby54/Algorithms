#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#define S 0
#define D 1
#define H 2
#define C 3

using namespace std;

int T, N;
char M[2];
vector<int> V[4];
map<char, int> Map;

bool isExist[4][14];
int numCount[14];
char ret[30];

bool checkStraightFlush(){
    for (int i = 0; i < 4; i++){
        if (V[i].size() < 5) continue;

        set<int> Set;
        for (int j = 0; j < V[i].size(); j++) {
            Set.insert(V[i][j]);
        }

        if (*(Set.begin()) == 1){
            Set.insert(14);
        }

        for (int j = 0; j < 4; j++){
            auto itr = Set.begin();
            for (int k= 0; k < j; k++){
                itr++;
            }

            // itr부터 확인.
            int cnt = 1;
            while (itr != Set.end()){
                int a = *itr;
                itr++;
                if (itr == Set.end()) break;

                int b = *itr;

                if (b - a != 1) break;
                cnt++;
            }

            if (cnt == 5) return true;

        }
    }

    return false;
}

bool checkNCard(int n){
    for (int i = 1; i <= 13; i++){
        int cnt = 0;
        for (int j = 0; j < 4; j++){
            cnt += isExist[j][i];
        }
        if (cnt == n) return true;
    }
    return false;
}
bool checkFlush(){
    for (int i = 0; i < 4; i++){
        if (V[i].size() >= 5) return true;
    }
    return false;
}

bool checkStraight(){
    set<int> Set;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < V[i].size(); j++){
            Set.insert(V[i][j]);
        }
    }

    if (*(Set.begin()) == 1){
        Set.insert(14);
    }
    
    for (int i = 0; i < 4; i++){
        auto itr = Set.begin();
        for (int j = 0; j < i; j++){
            itr++;
        }

        // itr부터 확인.
        int cnt = 1;
        while (itr != Set.end()){
            int a = *itr;
            itr++;
            if (itr == Set.end()) break;

            int b = *itr;

            if (b - a != 1) break;
            cnt++;
        }
        if (cnt == 5) return true;
    }

    return false;
}

bool checkNPair(int n){
    int cnt = 0;
    for (int i = 1; i <= 13; i++){
        if (numCount[i] >= 2) cnt++;
    }
    return cnt >= n;
}

int main(){
    Map['S'] = S;
    Map['D'] = D;
    Map['H'] = H;
    Map['C'] = C;

    scanf("%d", &T);

    for (int tc= 1; tc <= T; tc++){
        for (int i = 0; i < 4; i++)
            V[i].clear();

        memset(isExist, false, sizeof(isExist));
        memset(numCount, 0, sizeof(numCount));

        for (int i = 0; i < 7; i++){
            scanf("%s %d", M, &N);

            V[Map[M[0]]].push_back(N);
            isExist[Map[M[0]]][N] = true;
            numCount[N]++;
        }

        for (int i = 0; i < 4; i++)
            sort(V[i].begin(), V[i].end());


        if (checkStraightFlush()){
            strcpy(ret, "Straight Flush");
        }
        else if (checkNCard(4)){
            strcpy(ret, "4 Card");
        }
        else if (checkNCard(3) && checkNPair(2)){
            strcpy(ret, "Full House");
        }
        else if (checkFlush()){
            strcpy(ret, "Flush");
        }
        else if (checkStraight()){
            strcpy(ret, "Straight");
        }
        else if (checkNCard(3)){
            strcpy(ret, "Triple");
        }
        else if (checkNPair(2)){
            strcpy(ret, "2 Pair");
        }
        else if (checkNPair(1)){
            strcpy(ret, "1 Pair");
        }
        else{
            strcpy(ret, "Top");
        }
        printf("#%d %s\n", tc, ret);

    }

}