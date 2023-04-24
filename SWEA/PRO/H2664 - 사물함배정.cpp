#include <set>
#include <map>
using namespace std;

int totalNums;
int myN;

struct Node{
    int size;
    int start, end;

    Node(int sz=0, int s=0, int e=0) : size(sz), start(s), end(e) {}
};
struct cmp {
    bool operator()(const Node& a, const Node& b){
        if (a.size == b.size){
            return a.start < b.start;
        }
        return a.size > b.size;
    }
};
set<Node, cmp> cabinet;

struct Range {
    int s1, e1;
    int s2, e2;
    int pos;

    Range(int ss1=0, int ee1=0, int ss2=0, int ee2=0, int p = 0) : s1(ss1), e1(ee1), s2(ss2), e2(ee2), pos(p) {}
};

map<int, Range> owner;
map<int, int> posTomId;


void init(int N) {
    cabinet.clear();
    owner.clear();
    posTomId.clear();

    totalNums = 0;
    myN = N;

    cabinet.insert(Node(N, 1, N));

    return;
}

// mId 배정하기.
int arrive(int mId) {
    auto itr = cabinet.begin();
    auto curr = *itr;
    int start = curr.start;
    int end = curr.end;
    int size = curr.size;
    //printf("지금 골라진 건 (%d ~ %d)\n", start, end);

    int pos;

    if (start == 1){
        pos = 1;
    }
    else if (end == myN){
        pos = myN;
    }
    else if (size % 2 == 0){
        pos = end - size / 2;
    }
    else{
        pos = start + size / 2;
    }
    cabinet.erase(itr);

    posTomId[pos] = mId;

    if (posTomId[start-1]){
        int prevOwner = posTomId[start-1];

        Range prevRange = owner[prevOwner];
        owner[prevOwner] = Range(prevRange.s1, prevRange.e1, prevRange.s2, pos - 1);
    }

    if (posTomId[end+1]){
        int nextOwner = posTomId[end+1];

        Range nextRange = owner[nextOwner];
        owner[nextOwner] = Range(pos + 1, nextRange.e1, nextRange.s2, nextRange.e2);
    }

    owner[mId] = Range(start, pos-1, pos+1, end, pos);

    if (start <= pos-1){
        cabinet.insert(Node(pos - 1 - start + 1, start, pos-1));
    }

    if (pos +1 <= end){
        cabinet.insert(Node(end - pos, pos+1, end));
    }

    totalNums++;
    return pos;
}

// mId 퇴실.
int leave(int mId) {

    Range curr = owner[mId];

    // start - 1
    if (posTomId[curr.s1 - 1]){
        int prevOwner = posTomId[curr.s1 - 1];

        Range prevRange = owner[prevOwner];

        owner[prevOwner].e2 = curr.e2;
    }

    // end + 1
    if (posTomId[curr.e2 + 1]){
        int nextOwner = posTomId[curr.e2 + 1];
        Range nextRange = owner[nextOwner];

        owner[nextOwner].s1 = curr.s1;
    }

    auto itr = cabinet.find(Node(curr.e1 - curr.s1 + 1, curr.s1, curr.e1));
    if (itr != cabinet.end()){
        cabinet.erase(itr);
    }

    auto itr2 = cabinet.find(Node(curr.e2 - curr.s2 + 1, curr.s2, curr.e2));
    if (itr2 != cabinet.end()){
        cabinet.erase(itr2);
    }

    cabinet.insert(Node(curr.e2 - curr.s1 + 1, curr.s1, curr.e2));

    // 제거하기.
    posTomId[curr.pos] = 0;
    totalNums--;
    return myN - totalNums;
}