#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define HASH_SIZE (1 << 19)
#define DIV (HASH_SIZE - 1)

int getKey(char str[]) {
	unsigned long long ret = 5381;
	for (int i = 0; str[i]; i++) {
		ret = ((ret << 5) + ret) + str[i] - 'a';
	}

	return (int) ret & DIV;
}

// [s,e]를 해시
int getKeysub(char str[], int s, int e) {
	unsigned long long ret = 5381;
	for (int i = s; i <= e; i++) {
		ret = ((ret << 5) + ret) + str[i] - 'a';
	}

	return (int)ret & DIV;
}


struct HashNode {
	char str[6];
	int value = -1;
	vector<int> candidate; // 가능한 녀석들

	HashNode* next; // 그 다음을 저장해야 하니까

	HashNode* alloc(char _str[], int _value, HashNode* _next) {
		strcpy(str, _str);
		value = _value;
		next = _next;
		return this;
	}

	HashNode* getPrevNode(char _str[]) {
		HashNode* ptr = this;

		while (ptr->next) {
			if (strcmp(ptr->next->str, _str) == 0) {
				break;
			}
			ptr = ptr->next;
		}
		return ptr;
	}

};


struct Restaurant {
	char name[6];
	int cityID; // 이 음식점을 포함하는 city 아이디.
	int value; // 평점 저장.
};


int N, M;
int pCnt;
Restaurant restaurants[10005];
HashNode hashTable[HASH_SIZE];
HashNode buf[HASH_SIZE];
int bCnt;

vector<int> cityRestaturant[51]; // 도시가 갖고 있는 음식점 저장.

// 인접을 저장하자고
vector<int> adj[51];

struct Comp {
	bool operator()(const int a, const int b) {
		return restaurants[a].value < restaurants[b].value;
	}
};

void init(int n, int m, int mRoads[][2])
{
	N = n;
	M = m;
	pCnt = 0;
	bCnt = 0;
	memset(restaurants, 0, sizeof(restaurants));
	memset(buf, 0, sizeof(buf));
	memset(hashTable, 0, sizeof(hashTable));


	for (int i = 0; i < HASH_SIZE; i++) {
		hashTable[i].next = 0;
		hashTable[i].candidate.clear();
	}
	for (int i = 0; i < 51; i++) {
		cityRestaturant[i].clear();
		adj[i].clear();
	}

	for (int i = 0; i < m; i++) {
		int a = mRoads[i][0], b = mRoads[i][1];

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

}


void addRestaurant(int mCityID, char mName[])
{
	cityRestaturant[mCityID].push_back(pCnt);

	// pCnt를 하나씩 늘려간다.
	restaurants[pCnt].cityID = mCityID;
	
	// 각각에 대한 정보를 다 저장해야한다.
	int len = strlen(mName);
	strcpy(restaurants[pCnt].name, mName);

	// 총 15개를 저장해. 이게 그럼 총 10000번 호출 => 따라서 15만번.
	for (int i = 0; i < len; i++) {
		// mName + i부터. j만큼을?
		for (int j = i; j < len; j++) {
			int target = getKeysub(mName, i, j);
	
			char tmp[6];
			int idx = 0;
			for (int k = i; k <= j; k++)
				tmp[idx++] = mName[k];
			tmp[idx] = 0;

			HashNode* prevNode = hashTable[target].getPrevNode(tmp);
			if (prevNode->next == nullptr) {
				prevNode->next = buf[bCnt++].alloc(tmp, 0, prevNode->next);
			}

			int sz = prevNode->next->candidate.size();
			bool isFound = false;
			for (int k = 0; k < sz; k++) {
				if (prevNode->next->candidate[k] == pCnt) {
					isFound = true;
					break;
				}
			}
			if (!isFound)
				prevNode->next->candidate.push_back(pCnt);
		}
	}

	pCnt++;
}

void addValue(char mName[], int mScore)
{
	int target = getKey(mName);
	HashNode* prevNode = hashTable[target].getPrevNode(mName);

	int len = strlen(mName);

	for (int restID : prevNode->next->candidate) {
		if (strcmp(restaurants[restID].name, mName)) continue;
		
		restaurants[restID].value += mScore;

		for (int i = 0; i < len; i++) {
			// mName + i부터. j만큼을?
			for (int j = i; j < len; j++) {
				int target = getKeysub(mName, i, j);

				char tmp[6];
				int idx = 0;
				for (int k = i; k <= j; k++)
					tmp[idx++] = mName[k];
				tmp[idx] = 0;

				HashNode* prevNode = hashTable[target].getPrevNode(tmp);
				
				prevNode->next->value = std::max(prevNode->next->value,
					restaurants[restID].value);
			}
		}


	}
}

int bestValue(char mStr[])
{
	int target = getKey(mStr);

	HashNode* prevNode = hashTable[target].getPrevNode(mStr);

	return	prevNode->next->value;
}


int regionalValue(int mCityID, int mDist)
{
	bool visited[51] = { 0 };
	visited[mCityID] = true;
	queue<int> Q;
	Q.push(mCityID);

	vector<int> candi;
	candi.push_back(mCityID);

	// Q를 돌며, mDist이하인 것만.
	int level = 1;
	while (!Q.empty()) {
		int qSize = Q.size();

		if (level > mDist) break; 
		for (int sz = 0; sz < qSize; sz++) {
			int curr = Q.front();
			Q.pop();

			for (int next : adj[curr]) {
				if (visited[next]) continue;
				
				candi.push_back(next);
				visited[next] = true;
				Q.push(next);
			}
		}
		level++;
	}

	priority_queue<int, vector<int>, Comp> PQ;
	
	for (int c : candi) {
		for (int restID : cityRestaturant[c]) {
			PQ.push(restID);
		}
	}

	int ret = 0;
	for (int i = 0; i < 3; i++) {
		if (PQ.empty()) break;
		int restID = PQ.top();
		PQ.pop();
		ret += restaurants[restID].value;
	}
	
	return ret;
}
