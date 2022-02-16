#include <queue>
#include <cstring>
#include <unordered_map>
#define MAX_LINE 505
using namespace std;

// 큐에 들어갈 Process.
// 큐에서 빼서 어떤 장비를 쓰는지, 소요시간은 몇인지를 알아야 한다.
struct Process {
	int pID, eID, lineID, time;
	Process(int p = 0, int e = 0, int l = 0, int t = 0) :
		pID(p), eID(e), lineID(l), time(t) {}
};

struct Request {
	int endTime; // 종료 시각을 저장한다.
	Process p; // 그리고 처리하려는 Process를 담는다.
	
	Request(int e, Process _p = 0) {
		endTime = e;
		p = _p;
	}
	// greater<Request> 안하고 이렇게
	// 애초에 부등호를 바꾸면, 기본 최대힙에서 최소힙으로 변경이 가능하다.
	bool operator<(const Request& a) const {
		return endTime > a.endTime;
	}
};


int lineNums, eNums;
int nowTime;
queue<Process> lineQ[MAX_LINE];
priority_queue<Request> totalPQ; // 종료 시각이 빠른 순으로 담아야 한다.
unordered_map<int, int> pIDStatus; // 1~10억 범위인 pIDStatus.

bool eUse[MAX_LINE];
int lineUse[MAX_LINE]; // 쓰고 있는 Process의 pID를 적든가, 안 쓰고 있다면 -1.

void init(int L, int M) {
	lineNums = L;
	eNums = M;
	for (int i = 0; i < L; i++)
		lineQ[i] = {};
	
	totalPQ = {};
	memset(eUse, 0, sizeof(eUse));
	memset(lineUse, -1, sizeof(lineUse));
	pIDStatus.clear();
	
	return;
}

// t시간 까지 모두 다 처리해본다.
void timeFlow(int t) {

	while (!totalPQ.empty() && totalPQ.top().endTime <= t) {
		// 하나 빼서 쓴다.
		nowTime = totalPQ.top().endTime;
		// nowTime에 딱 끝나는 녀석들. 그게 여러 가지 일수가 있다.
		// 그것들을 다 갖다가 사용완료 처리한다.
		while (!totalPQ.empty() && totalPQ.top().endTime == nowTime) {
			Process currP = totalPQ.top().p;
			totalPQ.pop();

			if (currP.pID < 0) continue; // 

			//printf("%d(장비%d)를 %d 시각에 반납\n", currP.pID, currP.eID, nowTime);
			pIDStatus[currP.pID] = 3;
			eUse[currP.eID] = false;
			lineUse[currP.lineID] = -1;
		}

		// 낮은 라인부터 돌면서, 써본다.
		for (int i = 0; i < lineNums; i++) {
			// 라인이 사용 중이지 않고, 또 큐에 기다리는 녀석이 있어야한다.
			if (lineUse[i] == -1 && !lineQ[i].empty()) {
				Process currP = lineQ[i].front();

				// 근데 장비가 다른 사람이 쓰고 있으면 안됨.
				if (eUse[currP.eID]) continue;

				// 여기까지도 통과를 한다면 쓸 수 있다는 말이다.
				eUse[currP.eID] = true;
				pIDStatus[currP.pID] = 2; // 실행 중.
				lineUse[i] = currP.pID;

				//printf("%d(장비%d)를 %d 시각에 쓰고 있음\n", currP.pID, currP.eID, nowTime);


				totalPQ.push(Request(nowTime + currP.time, currP));

				lineQ[i].pop(); // 그리고 하나를 썼으니 pop
			}
		}

	}

}

int request(int tStamp, int pId, int mLine, int eId, int mTime) {
	// 지금 시점 이전에 다 처리를 한다.
	timeFlow(tStamp - 1);
	
	//printf("====%d시각에 %d, 라인%d, 장비%d, %d시간 걸리는 거 들옴====\n",
	//	tStamp, pId, mLine, eId, mTime);

	lineQ[mLine].push(Process(pId, eId, mLine, mTime));
	pIDStatus[pId] = 1;

	totalPQ.push(Request(tStamp, Process(-1))); // Dummy로 넣는다. 이러면 timFlow(tStamp)로 넘어갈 때, 처리 가능.

	nowTime = tStamp;
	timeFlow(tStamp);

	return lineUse[mLine];
}

int status(int tStamp, int pId) {
	timeFlow(tStamp);

	return pIDStatus[pId];
}