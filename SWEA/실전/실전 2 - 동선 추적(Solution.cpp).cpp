#include <cstdio>
#include <vector>
using namespace std;
#define MAX_PLACE 50005

// PlaceNode는
// r,c 좌표 저장, 그리고 isPossible.
// pCnt++해가면서 메모리풀에 저장한다.
// 그래서 placeNode[50000]에 저장.
// ★★ pId를 알면, r,c를 접근하고, isPossible을 알 수 있다.

// UserPlace는
// 지금까지 돌아다닌 장소를 저장한다. 배열식으로.
// pId를 접근하는데, pId를 알면, placeNode[pId]로 해당 노드 접근 가능.

struct PNode {
	int r, c;
	bool isPossible;

	PNode* alloc(int _r, int _c, bool _isPossible) {
		r = _r;
		c = _c;
		isPossible = _isPossible;
		return this;
	}
};
PNode placeNode[MAX_PLACE];

int pCnt;
vector<int> placeR[MAX_PLACE], placeC[MAX_PLACE];
vector<int> placeRaddC[20005], placeRsubC[20005]; // r+c가 최대 20000까지 가능. r-c는 -10000 ~ 10000까지. 따라서 1만을 걍 더해준다.
vector<int> userPlace[1000]; // 유저가 방문한 장소 저장한다.

void init()
{
	pCnt = 1;
	for (int i = 0; i < MAX_PLACE; i++) {
		placeR[i].clear();
		placeC[i].clear();
	}
	for (int i = 0; i < 20005; i++) {
		placeRaddC[i].clear();
		placeRsubC[i].clear();
	}
	for (int i = 0; i < 1000; i++)
		userPlace[i].clear();

}

void addPlace(int pID, int r, int c)
{
	//printf("===============장소%d(%d,%d) 추가합니다==================\n", pID, r, c);
	placeNode[pCnt++].alloc(r, c, true);
	
	placeR[r].push_back(pID);
	placeC[c].push_back(pID);
	placeRaddC[r+c].push_back(pID);
	placeRsubC[r - c + 10000].push_back(pID);
}

void removePlace(int pID)
{
	//printf("===============장소%d 지웁니다===========\n", pID);
	int r = placeNode[pID].r;
	int c = placeNode[pID].c;

	// r행에서 지운다.
	int size = placeR[r].size();
	for (int i = 0; i < size; i++)
		// 돌다가 pId를 발견하면, 삭제한다.
		if (placeR[r][i] == pID) {
			placeR[r][i] = placeR[r].back();
			placeR[r].pop_back();
		}

	// c열에서 지운다.
	size = placeC[c].size();
	for (int i = 0; i < size; i++)
		// 돌다가 pId를 발견하면, 삭제한다.
		if (placeC[c][i] == pID) {
			placeC[c][i] = placeC[c].back();
			placeC[c].pop_back();
		}

	// r+c에서 지운다
	size = placeRaddC[r + c].size();
	for (int i = 0; i < size; i++)
		// 돌다가 pId를 발견하면, 삭제한다.
		if (placeRaddC[r+c][i] == pID) {
			placeRaddC[r+c][i] = placeRaddC[r+c].back();
			placeRaddC[r+c].pop_back();
		}

	// r-c에서 지운다.
	size = placeRsubC[r - c + 10000].size();
	for (int i = 0; i < size; i++)
		// 돌다가 pId를 발견하면, 삭제한다.
		if (placeRsubC[r - c + 10000][i] == pID) {
			placeRsubC[r - c + 10000][i] = placeRsubC[r - c + 10000].back();
			placeRsubC[r - c + 10000].pop_back();
		}

}

void contactTracing(int uID, int visitNum, int moveInfo[], int visitList[])
{
	//printf("===============유저 %d에 대한 contactTracing 중=================\n", uID);
	int currR = placeNode[moveInfo[0]].r;
	int currC = placeNode[moveInfo[0]].c;
	visitList[0] = moveInfo[0];

	for (int i = 1; i < visitNum; i++) {
		//printf("%d번째 장소 처리 중입니다\n", i);
		int direction = moveInfo[i];
		int nextPlaceID = 0;

		// direction에 따라 다르게 되는데,
		// direction이 0, 4라면 => placeC[currC]에서 찾는다.
		// direction이 2, 6라면 => placeR[currR]에서 찾는다.
		// direction이 1, 5라면 => placeRaddC[currR + currC]에서 찾는다.
		// direction이 3, 7라면 => placeRsubC[currR - currC + 10000]에서 찾는다.

		if (direction == 0) {
			int nextR = -1;
			for (auto pID : placeC[currC]) {
				// currR보다 작은 최대 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r > nextR &&
					placeNode[pID].r < currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}
		else if (direction == 4) {
			int nextR = 10005;
			for (auto pID : placeC[currC]) {
				// currR보다 큰 최소 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r < nextR &&
					placeNode[pID].r > currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}
		// 같은 행에서 찾는 경우
		else if (direction == 2) {
			int nextC = 10005;
			for (auto pID : placeR[currR]) {
				// currC보다 큰 최소 C를 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].c < nextC &&
					placeNode[pID].c > currC) {
					nextC = placeNode[pID].c;
					nextPlaceID = pID;
				}
			}
		}
		else if (direction == 6) {
			int nextC = -1;
			for (auto pID : placeR[currR]) {
				// currC보다 작은 최대 c를 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].c > nextC &&
					placeNode[pID].c < currC) {
					nextC = placeNode[pID].c;
					nextPlaceID = pID;
				}
			}
		}
		// r + c 값이 같은 경우
		else if (direction == 1) {
			int nextR = -1;
			for (auto pID : placeRaddC[currR + currC]) {
				// currR보다 작은 최대 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r > nextR &&
					placeNode[pID].r < currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}
		else if (direction == 5) {
			int nextR = 10005;
			for (auto pID : placeRaddC[currR + currC]) {
				// currR보다 큰 최소 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r < nextR &&
					placeNode[pID].r > currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}
		// r - c + 10000의 값이 같은 경우
		else if (direction == 3) {
			int nextR = 10005;
			for (auto pID : placeRsubC[currR - currC + 10000]) {
				// currR보다 큰 최소 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r < nextR &&
					placeNode[pID].r > currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}
		else if (direction == 7) {
			int nextR = -1;
			for (auto pID : placeRsubC[currR - currC + 10000]) {
				// currR보다 작은 최대 r을 찾는다.
				if (!placeNode[pID].isPossible) continue;

				if (placeNode[pID].r > nextR &&
					placeNode[pID].r < currR) {
					nextR = placeNode[pID].r;
					nextPlaceID = pID;
				}
			}
		}

		// 다음 장소로 이동하고,
		// currR과 currC를 업데이트 한다.
		visitList[i] = nextPlaceID;
		currR = placeNode[nextPlaceID].r;
		currC = placeNode[nextPlaceID].c;
	}

	//printf("유저%d가 방문한 장소들 : ", uID);
	for (int i = 0; i < visitNum; i++) {
		//printf("%d, ", visitList[i]);
		placeNode[visitList[i]].isPossible = false;
		userPlace[uID].push_back(visitList[i]);
	}
	//puts("");

}

void disinfectPlaces(int uID)
{
	//printf("============유저 %d가 갔던 곳 소독===============\n", uID);
	for (auto pID : userPlace[uID]) {
		//printf("장소 %d 소독 시작\n", pID);
		placeNode[pID].isPossible = true;
	}
}