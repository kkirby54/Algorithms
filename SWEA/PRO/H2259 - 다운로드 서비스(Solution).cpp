#include <vector>
#include <cstring>
#include <cstdio>
#include <set>
using namespace std;

void trickleDown(int curr);
void proceed(int mTime);

struct Result {
	int finish;
	int param;
};

struct Node {
	int downloadSpeed;
	int numberOfUsed;
	int parent;
	vector<int> children;

	int remainingData;
	int finishTime;

	Node() : downloadSpeed(0), numberOfUsed(0), parent(0), remainingData(0), finishTime(0) {}
};

Node nodes[50001];
set<int> pc; // pc number를 저장
int prevTime;

void init(int mCapa)
{
	memset(nodes, 0, sizeof(nodes));
	nodes[0].downloadSpeed = mCapa;
	// children 다 빼줘야 할수도.
	for (int i = 0; i < 50001; i++) {
		nodes[i].children.clear();
	}

	pc.clear();

	prevTime = 0;
}

void finishPC(int mpcID) {

	int curr = mpcID;
	while (nodes[curr].numberOfUsed == 1) {
		nodes[curr].numberOfUsed--;
		curr = nodes[curr].parent;
	}
	if (nodes[curr].numberOfUsed != 0)
		nodes[curr].numberOfUsed--;

	// curr부터 trickleDown
	trickleDown(curr);

}

void timeFlow(int mTime) {
	
	while (prevTime < mTime) {
		proceed(mTime);
	}
	prevTime = mTime;
}

void proceed(int mTime) {
	if (prevTime >= mTime) return;

	int idx = 0, bestDt = 987654321;
	for (int p : pc) {
		int tmp;
		if (nodes[p].downloadSpeed != 0) {
			tmp = (nodes[p].remainingData / nodes[p].downloadSpeed) + (nodes[p].remainingData % nodes[p].downloadSpeed != 0);
		}
		else tmp = 987654321;

		if (bestDt > tmp) {
			bestDt = tmp;
			idx = p;
		}
	}

	// 이제 bestDt와, mTime - prevTime 중에 더 작은 거만큼 가야 한다.
	int goTime = min(bestDt, mTime - prevTime);
	
	vector<int> candi;
	for (int p : pc) {
		nodes[p].remainingData -= (goTime * nodes[p].downloadSpeed);

		if (nodes[p].remainingData <= 0) {
			candi.push_back(p);
		}
	}

	for (int c : candi) {
		finishPC(c);
		pc.erase(c);
		nodes[c].finishTime = prevTime + goTime;
	}
	

	prevTime += goTime;
}

void addHub(int mTime, int mParentID, int mID)
{
	timeFlow(mTime);

	nodes[mParentID].children.push_back(mID);
	nodes[mID].parent = mParentID;
}

int removeHub(int mTime, int mID)
{
	timeFlow(mTime);

	if (nodes[mID].numberOfUsed != 0) {
		return 0;
	}

	// Remove.
	int p = nodes[mID].parent;
	std::remove(nodes[p].children.begin(), nodes[p].children.end(), mID);

	return 1;
}

void trickleDown(int curr) {
	// target의 children부터 순회.
	if (nodes[curr].numberOfUsed == 0) return;

	for (int child : nodes[curr].children) {
		// 11 = 33 / 3 ( 2 + 1 이므로)
		nodes[child].downloadSpeed = nodes[curr].downloadSpeed / nodes[curr].numberOfUsed;
		trickleDown(child);
	}
}

void requestDL(int mTime, int mParentID, int mpcID, int mSize)
{
	// mTime까지 진행하기.
	timeFlow(mTime);

	nodes[mParentID].children.push_back(mpcID);
	nodes[mpcID].parent = mParentID;
	nodes[mpcID].remainingData = mSize;
	pc.insert(mpcID);


	int target = mParentID;
	while (target != 0 && nodes[target].numberOfUsed == 0) {
		target = nodes[target].parent;
	}
	
	// mpcID부터 target까지 numberOfUsed를 ++
	int start = mpcID;
	nodes[target].numberOfUsed++;

	while (start != target) {
		nodes[start].numberOfUsed++;
		start = nodes[start].parent;
	}

	// target부터 쭉 downloadSpeed를 업데이트.
	trickleDown(target);

}

Result checkPC(int mTime, int mpcID)
{
	timeFlow(mTime);

	Result res;
	res.finish = 0;
	res.param = 0;

	if (nodes[mpcID].remainingData > 0) {
		res.param = nodes[mpcID].remainingData;
	}
	else {
		res.finish = 1;
		res.param = nodes[mpcID].finishTime;
	}

	return res;
}