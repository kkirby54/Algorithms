#define MAXM	3

#include <set>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<bool, bool> P;

struct Message {
    int mId;
    int uId1;
    int uId2;
    int timeStamp;
    int scheduleTimeStamp;
};

// timeStamp이 높은 순으로
struct cmp {
    bool operator()(const Message& a, const Message& b) const {
        if (a.timeStamp == b.timeStamp)
            return a.mId > b.mId;
        return a.timeStamp > b.timeStamp;
    }
};

// schedTime이 높은 순으로
struct inBoxCmp {
    bool operator()(const Message& a, const Message& b) const {
        if (a.scheduleTimeStamp == b.scheduleTimeStamp)
            return a.mId > b.mId;
        return a.scheduleTimeStamp > b.scheduleTimeStamp;
    }
};

// scheduleTimeStamp가 높은 순으로 저장.
// 그게 같으면, ID가 높은 순
struct schedCmp {
    bool operator()(const Message& a, const Message& b) const {
        if (a.scheduleTimeStamp == b.scheduleTimeStamp)
            return a.mId < b.mId;
        return a.scheduleTimeStamp < b.scheduleTimeStamp;
    }
};

set<Message, cmp> sentBox[1001];
set<Message, inBoxCmp> inBox[1001];
P isRead[100001];

map<int, Message> messages;
set<Message, schedCmp> schedMessages;

void init(int N)
{
    for (int i = 0; i <= N; i++){
        sentBox[i].clear();
        inBox[i].clear();
    }
    memset(isRead, 0, sizeof(isRead));

    messages.clear();
    schedMessages.clear();
}

// schedMessage -> inBox로 옮기기
void timeFlow(int cTimestamp) {

    auto itr = schedMessages.begin();

    while (itr != schedMessages.end() && itr->scheduleTimeStamp <= cTimestamp) {
        Message msg = (*itr);

        inBox[itr->uId2].insert(msg);

        auto itrPrev = itr;
        itr++;

        schedMessages.erase(itrPrev);
    }

}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
    timeFlow(cTimestamp);

    Message msg = { mID, uID1, uID2, cTimestamp, scheduleTimestamp };

    // 보내기
    sentBox[uID1].insert(msg);

    // 우선 예약 메세지함에 넣기
    schedMessages.insert(msg);

    messages[mID] = msg;
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    timeFlow(cTimestamp);

    // 3개 혹은 적은 것.
    int sz = std::min(3, (int)sentBox[uID].size());
    if (!sz) return 0;

    auto itr = sentBox[uID].begin();
    for (int i = 0; i < sz; i++) {
        mIDList[i] = itr->mId;
        uIDList[i] = itr->uId2; // 받는 사용자
        readList[i] = isRead[itr->mId].second; // 받는 사용자의 읽음 여부.

        itr++;
    }

    return sz;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    timeFlow(cTimestamp);

    // 3개 혹은 적은 것.
    int sz = std::min(3, (int)inBox[uID].size());
    if (!sz) return 0;

    auto itr = inBox[uID].begin();
    for (int i = 0; i < sz; i++) {
        mIDList[i] = itr->mId;
        uIDList[i] = itr->uId1; // 보낸 사용자
        readList[i] = isRead[itr->mId].second; // 받는 사용자의 읽음 여부.

        itr++;
    }

    return sz;
}

int readMessage(int cTimestamp, int uID, int mID)
{
    timeFlow(cTimestamp);

    Message msg = messages[mID];
    if (msg.mId == 0) return 0;

    // Sent
    auto itrSent = sentBox[uID].find(msg);

    // In
    auto itrIn = inBox[uID].find(msg);

    // 둘다 없을 때, 즉 uID가 보내거나 받은 message가 아닌 케이스
    if (itrSent == sentBox[uID].end() && itrIn == inBox[uID].end()) return 0;

    // 보낸 거라면
    if (itrSent != sentBox[uID].end()) {
        isRead[mID].first = true;
    }
    // 받은 거라면
    if (itrIn != inBox[uID].end()) {
        isRead[mID].second = true;
    }

    return 1;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
    timeFlow(cTimestamp);

    Message msg = messages[mID];
    if (msg.mId == 0) return 0;

    // Sent
    auto itrSent = sentBox[uID].find(msg);
    // In
    auto itrIn = inBox[uID].find(msg);

    // 둘다 없을 때, 즉 uID가 보내거나 받은 message가 아닌 케이스
    if (itrSent == sentBox[uID].end() && itrIn == inBox[uID].end()) return 0;

    // 보낸 거라면
    if (itrSent != sentBox[uID].end()) {
        // 1. sentBox에서 지운다
        sentBox[uID].erase(itrSent);
        // 2. schedMessage에서 봐야한다.
        if (cTimestamp < itrSent->scheduleTimeStamp) {
            auto itrSched = schedMessages.find(msg);
            if (itrSched != schedMessages.end()) {
                schedMessages.erase(itrSched);
            }
        }

    }
    // 받은 거라면
    if (itrIn != inBox[uID].end()) {
        // 1. InBox에서 지운다.
        inBox[uID].erase(itrIn);
    }

    return 1;
}
