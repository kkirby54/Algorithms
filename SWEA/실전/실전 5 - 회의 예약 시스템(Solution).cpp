#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#define MAX_N (10000)
#define MAX_STR_LEN (13)
using namespace std;

// 회의 요일, 시작~끝 시, 분 저장
struct Conf {
	int day;
	int sH, eH;
	int sM, eM;
	Conf(int d = 0,int _sH=0, int _eH = 0, int _sM = 0, int _eM=0)
		: day(d), sH(_sH), eH(_eH), sM(_sM), eM(_eM) {}
};


int pCnt, tCnt;
int nowDay;
unordered_map<string, int> hashName; // name이 들어오면 pCnt로
unordered_map<string, int> hashTeam; // teamName이 들어오면 tCnt로.

vector<int> teamMember[3005];
Conf teamConf[3005]; // team이 들어오면, 그 Conf를 돌려준다.
vector<int> memberTeam[10005];

// 이건 전역이 아니라, 그 때 그 때 초기화.
int timeTable[8][19][61]; // 월~금, 09~18, 0~60.


void init(int N, char mName[][MAX_STR_LEN])
{
	hashName = {};
	hashTeam = {};
	pCnt = 0;
	tCnt = 0;
	nowDay = 1;

	memset(teamConf, 0, sizeof(teamConf));
	for (int i = 0; i < N; i++) {
		hashName[string(mName[i])] = pCnt++;
	}
	for (int i = 0; i < 3001; i++) {
		teamMember[i].clear();
	}
	for (int i = 0; i < 10005; i++) {
		memberTeam[i].clear();
	}

}

void createTeam(char mTeamName[], int M, char mName[][MAX_STR_LEN])
{
	hashTeam[string(mTeamName)] = tCnt;
	
	for (int i = 0; i < M; i++) {
		int member = hashName[mName[i]];
		teamMember[tCnt].push_back(member);

		memberTeam[member].push_back(tCnt);
	}
	tCnt++;
}

// 회의 conf가 주어지면,
// 그 시각에 해당하는 걸 채운다.
void fillTable(Conf conf) {
	int day = conf.day;
	
	for (int i = conf.sM; i < 60; i++) {
		timeTable[day][conf.sH][i] = true;
		if (conf.sH == conf.eH && i == conf.eM) return;
	}

	for (int i = conf.sH + 1; i <= conf.eH; i++) {
		for (int j = 0; j <= (i == conf.eH ? conf.eM : 59); j++) {
			
			timeTable[day][i][j] = true;

			// 근데 i == conf.eH면 끝낸다.
			if (i == conf.eH && j == conf.eM) {
				return;

			}
		}

	}

}

int bookMeeting(char mTeamName[], int mMinutes)
{
	int team = hashTeam[mTeamName];
	teamConf[team] = { -1,-1,-1,-1,-1};
	
	memset(timeTable, 0, sizeof(timeTable));
	
	bool teamUsed[3001] = { 0 };
	for (int member : teamMember[team]) {
		// 멤버가 속한 팀들을 돌며
		for (int t : memberTeam[member]) {
			if (!teamUsed[t] && teamConf[t].sH != -1) {
				// 그럼 테이블에 채운다.
				fillTable(teamConf[t]);
				teamUsed[t] = true;
			}
		}
	}

	// 돌리다가, timeTable[i][j] = false라면
	// 그 때부터 flag 세우고 세본다. 그러다가
	// mMinutes만큼 cnt가 가다가 끊긴다면(timeTable[i][j]가 true라면)
	// 여긴 안된다는 의미다. 그래서 다시 초기화 후 다음으로 이동한다.
	// 그리고 도중에 18:00을 만나면 그 날은 불가능.
	int H, M;

	bool flag = false; // 이게 true면, 채우고 있다는 말임.
	int cnt = 0;
	
	for (int currD = nowDay; currD < nowDay + 7; currD++) {
		if (currD % 7 == 0 || currD % 7 == 6) continue; // 토, 일 처리

		for (int i = 9; i <= 18; i++) {
			for (int j = 0; j < 60; j++) {
				// 이미 차있다면, 불가
				if (timeTable[currD % 7][i][j]) {
					flag = false;
					cnt = 0;
				}
				else {
					// 처음 시작이라면, 시작 시간도 저장.
					if (!flag) {
						flag = true;
						H = i;
						M = j;
					}

					cnt++; // 이 시각을 채울 수 있다.


					if (cnt == mMinutes) {
						// 그럼 제일 빠른 시각을 찾았다.
						// W = currD / 7 + 1
						// D = currD
						//printf("%d주차, %d요일, %d시%d분,(%d:%d~%d:%d)\n", currD / 7 + 1, currD % 7, H, M,
						//	H, M, i, j);
						teamConf[team].day = (currD % 7);
						teamConf[team].sH = H;
						teamConf[team].eH = i;
						teamConf[team].sM = M;
						teamConf[team].eM = j;

						int ret = (currD / 7 + 1) * 10;
						ret += (currD % 7);
						ret *= 100; ret += H;
						ret *= 100; ret += M;

						return ret;
					}
				}

				// i가 18이라면,
				// 이제 j를 ++할 수 없다.
				// 여기까지 왔는데도, cnt == mMinutes가 안됐다면
				// 이 날은 불가능이다.
				if (i == 18) {
					flag = false;
					cnt = 0;
				}

			}
		}
	}

	return 0;
}

void timeElapse(int mDays)
{
	nowDay += mDays;
}