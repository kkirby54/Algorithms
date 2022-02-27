#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#define MAX_N 201
#define MAX_FILE 5001
using namespace std;

struct Edge {
	int u, v;
	int maxBand; // 최대 대역폭
	int usingBand; // 사용 중인 대역폭.
};
vector<int> adjEdgeIdx[MAX_N]; // 인덱스 i에 인접한 edge들의 idx를 저장한다.
vector<Edge> edges;

int N;
unordered_map<string, int> hashFile;
unordered_set<int> haveFile[MAX_FILE];
int fileIdx;

int sharingNums[MAX_N]; // 공유하는 파일의 수
int fileSizes[MAX_FILE]; // 파일의 크기.

vector<int> paths[5001]; // mTID가 주어지면, 그에 해당하는 edge들을 모아둔다.

struct Info {
	int requester;
	int fIdx;
	int fileSize;
};

Info amountsTID[5001];

void init(int n, int mUID1[], int mUID2[], int mBandwidth[])
{
	N = n;
	for (int i = 0; i < MAX_N; i++)
		adjEdgeIdx[i] = {};
	edges = {};

	hashFile = {};
	for (int i = 0; i < MAX_FILE; i++)
		haveFile[i] = {};


	fileIdx = 0;


	memset(sharingNums, 0, sizeof(sharingNums));
	memset(fileSizes, 0, sizeof(fileSizes));
	memset(amountsTID, 0, sizeof(amountsTID));

	// N-1개의 edge
	for (int i = 0; i < N - 1; i++) {
		edges.push_back({ mUID1[i], mUID2[i], mBandwidth[i], 0 }); // 실제 Edge

		adjEdgeIdx[mUID1[i]].push_back(i);
		adjEdgeIdx[mUID2[i]].push_back(i);
	}

	for (int i = 0; i < 5001; i++) {
		paths[i].clear();
	}

}

int share(int mUID, char mFilename[], int mFilesize)
{
	int fIdx;
	if (hashFile[mFilename] == 0)
		fIdx = hashFile[mFilename] = ++fileIdx;
	else fIdx = hashFile[mFilename];

	// 파일을 갖고 있는 것으로, mUID를 설정한다.
	// 단, 이미 갖고 있을 수도 있음.

	// 처음 공유하는 거라면
	if (haveFile[fIdx].find(mUID) == haveFile[fIdx].end()) {
		haveFile[fIdx].insert(mUID);
		sharingNums[mUID]++;
		fileSizes[fIdx] = mFilesize;
	}

	return sharingNums[mUID];
}

// mUID가 mFilename을 요청한다.
int request(int mUID, char mFilename[], int mTID)
{
	int fIdx = hashFile[mFilename];
	if (fIdx == 0) return -1; // 애초에 없는 파일이면 안된다.
	int fileSize = fileSizes[fIdx];


	bool isSharer[MAX_N] = { 0 };
	// 파일을 갖고 있는 녀석들 처리.
	for (int sharer : haveFile[fIdx]) {
		isSharer[sharer] = true;
	}

	// 이제 출발지에서 BFS를 돌리면서, 최소 대역폭을 유지한채로
	// Sharer를 만나면,
	bool visited[MAX_N] = { 0 };
	queue<int> Q;
	Q.push(mUID);
	visited[mUID] = true;

	bool isFin = false;
	int target = MAX_N + 5;

	pair<int, int> previous[MAX_N];
	while (!Q.empty()) {
		int qSize = Q.size();
		for (int k = 0; k < qSize; k++) {
			int curr = Q.front();
			Q.pop();

			// 도착한 애가 sharer라면 이번 루프까지 진행한다.
			if (isSharer[curr]) {
				isFin = true;
				target = min(target, curr);
			}

			for (int eIdx : adjEdgeIdx[curr]) {
				int next;
				if (curr == edges[eIdx].u) next = edges[eIdx].v;
				else next = edges[eIdx].u;

				if (visited[next]) continue;

				// curr->next를 잇는게 eIdx인데,
				// 그 대역폭을 본다. 여기서는 max가 아니라 실제 가능한 대역폭
				// 그 대역폭이 더 크다면, 이 edge는 옮길 수 있다는 말
				if (edges[eIdx].maxBand - edges[eIdx].usingBand >= fileSize) {
					Q.push(next);
					visited[next] = true;
					previous[next] = make_pair(curr, eIdx);
				}
			}
		}

		if (isFin) break;
	}

	if (!isFin) return -1; // 끝내지 못했다면, 모든 경로에 대해서도 최소 대역폭 만족 x.

	// 이제 mUID와 target 사이의 경로를 알아내야 한다.
	// prev배열을 이용해서, prev[target].	
	int ret = target;

	while (target != mUID) {
		edges[previous[target].second].usingBand += fileSize;

		paths[mTID].push_back(previous[target].second);
		target = previous[target].first;
	}

	amountsTID[mTID].requester = mUID;
	amountsTID[mTID].fIdx = fIdx;
	amountsTID[mTID].fileSize = fileSize;

	return ret;
}

// mTID인 요청을 완료하고, 할당된 대역폭을 삭제.
int complete(int mTID)
{
	int uID = amountsTID[mTID].requester;
	int fIdx = amountsTID[mTID].fIdx;
	for (int e : paths[mTID]) {
		edges[e].usingBand -= amountsTID[mTID].fileSize;

		int u = edges[e].u, v = edges[e].v;
		if (haveFile[fIdx].find(u) == haveFile[fIdx].end()) {
			haveFile[fIdx].insert(u);
			sharingNums[u]++;
		}

		if (haveFile[fIdx].find(v) == haveFile[fIdx].end()) {
			haveFile[fIdx].insert(v);
			sharingNums[v]++;
		}
	}

	return sharingNums[uID];
}