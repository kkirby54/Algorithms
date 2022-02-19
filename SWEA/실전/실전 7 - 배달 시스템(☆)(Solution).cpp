#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

// 2022.02.19
// vector<int> userOrders[30]; 벡터를 선언만 해도 이상하게 오류가 남.
// 벡터 -> 배열로 바꾸니 runtime 오류 해결.


struct Point {
	int x, y;
};

int hashP[1000005];
int pCnt;
int uCnt;

Point uLoc[30];
Point pLoc[6005];
bool isAvail[6005];

int pCnt2pID[6005];
int orderNums[30][6005]; // 각 유저가 주문한 횟수를 저장.
int orderFriendsNums[30][6005]; // 유저의 친구들이 주문한 음식점 주문 횟수 통으로 저장.
int userOrders[30][6005];// 유저가 주문한 음식점의 pCnt를 저장. 빠르게 접근 가능. 
int userOrderNums[30];

bool isFriend[30][30];

// 유저와 음식점 거리 return
int getDist(int uID, int pID) {
	return abs(uLoc[uID].x - pLoc[pID].x) + abs(uLoc[uID].y - pLoc[pID].y);
}


class Heap {
public:
	int heap[10000] = { 0 };
	int index2Heap[10000] = { 0 }; // heap에 있는 거
	int user;
	int size = 0;

	void heapify(int curr) {
		while (curr != 0) {
			int parent = (curr - 1) / 2;

			// 일단 orderNums로 비교한다.
			// orderNums가 parent가 높으면 break
			if (orderNums[user][heap[curr]] + orderFriendsNums[user][heap[curr]]
				< orderNums[user][heap[parent]] + orderFriendsNums[user][heap[parent]])
				return;
			// 주문이 같다면
			else if (orderNums[user][heap[curr]] + orderFriendsNums[user][heap[curr]]
				== orderNums[user][heap[parent]] + orderFriendsNums[user][heap[parent]]) {
				if (getDist(user, heap[curr]) > getDist(user, heap[parent]))
					return;
				// 거리조차 같다면
				else if (getDist(user, heap[curr]) == getDist(user, heap[parent])) {
					if (pCnt2pID[heap[curr]] > pCnt2pID[heap[parent]])
						return;
				}
			}

			// 인덱스 업데이트.
			index2Heap[heap[curr]] = parent;
			index2Heap[heap[parent]] = curr;

			// curr과 parent를 바꾼다.
			int tmp = heap[curr];
			heap[curr] = heap[parent];
			heap[parent] = tmp;

			curr = parent;
		}
	}

	void pushHeap(int x) {
		index2Heap[x] = size;

		heap[size++] = x;

		heapify(size - 1);
	}

	int pop() {
		int ret = heap[0];


		// 가장 마지막을 루트로 올린다.
		heap[0] = heap[size - 1];
		// 그리고 사이즈를 아예 줄인다.
		size--;

		int curr = 0;

		// 이제 자식 노드로 내려가면서 swap한다.
		while ((curr * 2 + 1) < size) {
			int child;

			if (curr * 2 + 1 == size - 1) {
				child = curr * 2 + 1;
			}
			else {
				// 왼쪽 오른쪽 중 골라야 한다.
				int leftCh = curr * 2 + 1;
				int rightCh = curr * 2 + 2;

				if (orderNums[user][heap[leftCh]] + orderFriendsNums[user][heap[leftCh]]
					< orderNums[user][heap[rightCh]] + orderFriendsNums[user][heap[rightCh]]) {
					child = rightCh;
				}
				else if (orderNums[user][heap[leftCh]] + orderFriendsNums[user][heap[leftCh]]
					> orderNums[user][heap[rightCh]] + orderFriendsNums[user][heap[rightCh]]) {
					child = leftCh;
				}
				else {
					if (getDist(user, heap[leftCh]) > getDist(user, heap[rightCh]))
						child = rightCh;
					else if (getDist(user, heap[leftCh]) < getDist(user, heap[rightCh]))
						child = leftCh;
					else {
						if (pCnt2pID[heap[leftCh]] > pCnt2pID[heap[rightCh]])
							child = rightCh;
						else child = leftCh;
					}
				}
			}

			// 이제 child와 curr 비교.
			if (orderNums[user][heap[child]] + orderFriendsNums[user][heap[child]]
				< orderNums[user][heap[curr]] + orderFriendsNums[user][heap[curr]])
				break;
			// 주문이 같다면
			else if (orderNums[user][heap[child]] + orderFriendsNums[user][heap[child]]
				== orderNums[user][heap[curr]] + orderFriendsNums[user][heap[curr]]) {
				if (getDist(user, heap[child]) > getDist(user, heap[curr]))
					break;
				// 거리조차 같다면
				else if (getDist(user, heap[child]) == getDist(user, heap[curr])) {
					if (pCnt2pID[heap[child]] > pCnt2pID[heap[curr]])
						break;
				}
			}

			index2Heap[heap[curr]] = child;
			index2Heap[heap[child]] = curr;

			int tmp = heap[curr];
			heap[curr] = heap[child];
			heap[child] = tmp;

			curr = child;
		}

		return ret;
	}

};

Heap placeRank[30];

void init(int N, int px[], int py[])
{
	uCnt = N;
	pCnt = 0;
	memset(hashP, 0, sizeof(hashP));
	
	memset(orderNums, 0, sizeof(orderNums));
	memset(pCnt2pID, 0, sizeof(pCnt2pID));
	memset(isAvail, 0, sizeof(isAvail));
	memset(pLoc, 0, sizeof(pLoc));
	memset(uLoc, 0, sizeof(uLoc));
	memset(placeRank, 0, sizeof(placeRank));
	memset(orderFriendsNums, 0, sizeof(orderFriendsNums));
	memset(userOrders, 0, sizeof(userOrders));
	memset(userOrderNums, 0, sizeof(userOrderNums));
	memset(isFriend, 0, sizeof(isFriend));

	for (int i = 0; i < N; i++) {
		uLoc[i].x = px[i];
		uLoc[i].y = py[i];

		placeRank[i].user = i;
	}

}

void addRestaurant(int pID, int x, int y)
{
	hashP[pID] = pCnt;
	pCnt2pID[pCnt] = pID;
	pLoc[pCnt].x = x;
	pLoc[pCnt].y = y;

	isAvail[pCnt] = true;
	
	for (int i = 0; i < uCnt; i++) {
		placeRank[i].pushHeap(pCnt);
	}
	
	pCnt++;
}

void removeRestaurant(int pID)
{
	int target = hashP[pID];
	isAvail[target] = false;
}

void order(int uID, int pID)
{
	int targetP = hashP[pID];
	++orderNums[uID][targetP];

	// 처음 주문하는 거라면?
	int size = userOrderNums[uID];
	int j;
	for (j = 0; j < size; j++) {
		if (userOrders[uID][j] == targetP) {
			break;
		}
	}
	if (j == size) {
		userOrderNums[uID]++;
		userOrders[uID][size] = targetP;
	}


	// targetP는 어차피 다 들어가 있을 것이다.
	// 없는 음식점에 order할 수는 없기 때문.
	// 그니까 그냥 heapify만 한다.
	placeRank[uID].heapify(placeRank[uID].index2Heap[targetP]);

	// 친구들 처리
	for (int i = 0; i < uCnt; i++) {
		if (isFriend[uID][i]) {
			// 친구 i의 입장, 하나를 올려주고, Heapify
			orderFriendsNums[i][targetP]++;
			
			placeRank[i].heapify(placeRank[i].index2Heap[targetP]);
		}

	}


}

void beFriend(int uID1, int uID2)
{
	// uID1과 uID2가 친구가 되면,
	// 얘네 둘만 보면 된다.
	// How? uID1의 모든 주문내역을 돌면서,

	isFriend[uID1][uID2] = true;
	isFriend[uID2][uID1] = true;
	
	int sz = userOrderNums[uID1];
	for (int i = 0; i < sz; i++) {
		int orderedPlace = userOrders[uID1][i];

		if (!isAvail[orderedPlace]) continue;

		orderFriendsNums[uID2][orderedPlace] +=
			orderNums[uID1][orderedPlace];

		placeRank[uID2].heapify(placeRank[uID2].index2Heap[orderedPlace]);
	}
	
	sz = userOrderNums[uID2];
	for (int i = 0; i < sz; i++) {
		int orderedPlace = userOrders[uID2][i];

		if (!isAvail[orderedPlace]) continue;

		orderFriendsNums[uID1][orderedPlace] +=
			orderNums[uID2][orderedPlace];

		placeRank[uID1].heapify(placeRank[uID1].index2Heap[orderedPlace]);
	}
	

}

int rets[10] = { 0 };

int recommend(int uID)
{
	int nums = 0;

	while (nums != 10) {
		int candi = placeRank[uID].pop();
		if (!isAvail[candi])
			continue;
		
		rets[nums++] = candi;
	}

	for (int i = 0; i < 10; i++) {
		placeRank[uID].pushHeap(rets[i]);
	}

	return pCnt2pID[rets[9]];
}