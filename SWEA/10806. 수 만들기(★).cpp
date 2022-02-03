//#include <map>
//#include <string>
//#define NAME_MAXLEN 6
//#define PATH_MAXLEN 1999
//using namespace std;
//
//int child[50001][31];
//int childNums[50001];
//int parent[50001];
//char dirNames[50001][NAME_MAXLEN + 1];
//int subtreeNums[50001];
//int nums;
//
//
//int mstrcmp(const char *a, const char *b)
//{
//	int i;
//	for (i = 0; a[i] != '\0'; i++)
//	{
//		if (a[i] != b[i])
//			return a[i] - b[i];
//	}
//	return a[i] - b[i];
//}
//int mstrncmp(const char *a, const char *b, int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		if (a[i] != b[i])
//			return a[i] - b[i];
//	}
//	return 0;
//}
//int mstrlen(const char *a)
//{
//	int len = 0;
//
//	while (a[len] != '\0')
//		len++;
//
//	return len;
//}
//void mstrcpy(char *dest, const char *src)
//{
//	int i = 0;
//	while (src[i] != '\0')
//	{
//		dest[i] = src[i];
//		i++;
//	}
//	dest[i] = src[i];
//}
//void mstrncpy(char *dest, const char *src, int len)
//{
//	for (int i = 0; i<len; i++)
//	{
//		dest[i] = src[i];
//	}
//	dest[len] = '\0';
//}
//
//int findNextLen (const char* a, int pos) {
//	int len = 0;
//	while (a[pos + len] != '\0' && a[pos + len] != '/') {
//		len++;
//	}
//	return len;
//}
//
//void init(int n) {
//	nums = 0;
//	memset(child, 0, sizeof(child));
//	for (int i = 0; i < n; i++) {
//		parent[i] = -1;
//		childNums[i] = 0;
//		subtreeNums[i] = 0;
//	}
//	// 루트를 만든다.
//	mstrcpy(dirNames[0], "/");
//	nums++;
//}
//
//int getParent(char path[PATH_MAXLEN + 1]) {
//	// path를 따라서 가면서 찾아야 한다.
//	int cursor = 1;
//	int curr = 0; // 루트부터 시작한다.
//
//	int pathLen = mstrlen(path);
//	while (cursor < pathLen) {
//		int currLen = findNextLen(path, cursor);
//		// 이러면 "/abcd/sdfa/" 라면, abcd의 길이가 나온다.
//		for (int i = 0; i < childNums[curr]; i++) {
//			int next = child[curr][i];
//			if (next == -1) continue;
//			if (mstrncmp(path + cursor, dirNames[next], currLen) == 0) {
//				cursor += (currLen + 1);
//				curr = next;
//				break;
//			}
//		}		
//	}
//
//	return curr;
//}
//
//void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
//	// path를 통해 parent를 찾는다.
//	int curr = getParent(path);
//
//	// curr의 아래에 name을 생성한다.
//	child[curr][childNums[curr]++] = nums;
//	parent[nums] = curr;
//	mstrcpy(dirNames[nums], name);
//
//	nums++;
//
//	// 이제 curr부터 그 parent의 subtree를 쭉 증가해준다.
//	while (curr != -1) {
//		subtreeNums[curr]++;
//		curr = parent[curr];
//	}
//}
//
//// 다 지워버림.
//void cmd_rm(char path[PATH_MAXLEN + 1]) {
//	// 만약 path가 루트라면?
//	if (mstrlen(path) == 1) {
//		for (int i = 0; i < nums; i++) {
//			parent[i] = -1;
//			memset(child, 0, sizeof(child));
//			subtreeNums[i] = 0;
//		}
//		nums = 0;
//		mstrcpy(dirNames[0], "/");
//		nums++;
//		return;
//	}
//
//	int curr = parent[getParent(path)];
//	int removed = getParent(path);
//	// curr의 자식 중에서 지워버리면 되는데.
//
//	int removedCnt = subtreeNums[removed] + 1;
//	// 일단 curr부터 시작해서 쭉 subtreeNums를 갱신
//
//	for (int i = 0; i < childNums[curr]; i++){
//		int next = child[curr][i];
//		if (next == removed) {
//			child[curr][i] = -1;
//			break;
//		}
//	}
//
//	while (curr != -1) {
//		subtreeNums[curr] -= removedCnt;
//		curr = parent[curr];
//	}
//}
//
//void dfs(int curr, int dst) {
//
//	// curr의 child를 dst의 child로 만들어준다. (값만 같게)
//	for (int i = 0; i < childNums[curr]; i++) {
//		int ch = child[curr][i];
//		if (ch == -1) continue;
//
//		child[dst][childNums[dst]++] = nums;
//		mstrcpy(dirNames[nums], dirNames[ch]);
//		parent[nums] = dst;
//		subtreeNums[nums] = subtreeNums[ch];
//
//		dfs(ch, nums++);
//	}
//
//}
//
//void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//	// srcPath를 다 갖다가 dstPath에 붙여넣는다.
//
//	int srcCurr = getParent(srcPath);
//	int dstCurr = getParent(dstPath);
//
//	// 그러면 srcCurr의 값을 갖는 녀석을 새로 만든다.
//	child[dstCurr][childNums[dstCurr]++] = nums;
//	mstrcpy(dirNames[nums], dirNames[srcCurr]);
//	parent[nums] = dstCurr;
//	subtreeNums[nums] = subtreeNums[srcCurr];
//
//	// 그러면 dstCurr에는 다시 또 루트까지 가면서,
//	// srcCurr + 1만큼 더한다.
//	while (dstCurr != -1) {
//		subtreeNums[dstCurr] += (subtreeNums[srcCurr] + 1);
//		dstCurr = parent[dstCurr];
//	}
//
//
//	// 이제 srcCurr을 전부 돌면서,
//	// nums로 새로 만들어 준다.
//	dfs(srcCurr, nums++);
//
//}
//
//void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//	int dstCurr = getParent(dstPath);
//
//	int srcRemoved = getParent(srcPath);
//	int srcParent = parent[srcRemoved];
//	// srcCurr에 있는걸 빼서 그대로 dstCurr에 넣는다.
//
//	int srcRemovedSubtreeNums = subtreeNums[srcRemoved] + 1;
//	// 일단 srcParent에서 srcCurr을 찾아서 제거한다.
//	// 그리고 그 subtreeNums도 그만큼을 빼준다.
//	for (int i = 0; i < childNums[srcParent]; i++) {
//		int next = child[srcParent][i];
//		if (next == srcRemoved) {
//			child[srcParent][i] = -1;
//			break;
//		}
//	}
//
//	while (srcParent != -1) {
//		subtreeNums[srcParent] -= srcRemovedSubtreeNums;
//		srcParent = parent[srcParent];
//	}
//
//	// 이제는 그냥 srcCurr을 dstPath에 넣어주고,
//	// 거기서도 갱신한다.
//	child[dstCurr][childNums[dstCurr]++] = srcRemoved;
//	parent[srcRemoved] = dstCurr;
//
//
//	while (dstCurr != -1) {
//		subtreeNums[dstCurr] += srcRemovedSubtreeNums;
//		dstCurr = parent[dstCurr];
//	}
//
//}
//
//int cmd_find(char path[PATH_MAXLEN + 1]) {
//	int curr = getParent(path);
//	return subtreeNums[curr];
//}
//
////
////#define CMD_MKDIR 1
////#define CMD_RM 2
////#define CMD_CP 3
////#define CMD_MV 4
////#define CMD_FIND 5
////int main() {
////	int cmd;
////	char name[NAME_MAXLEN + 1];
////	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];
////
////	init(7);
////	int cnt = 0;
////	while (1) {
////		printf("%d번째 명령\n", cnt++);
////		scanf("%d", &cmd);
////
////		if (cmd == CMD_MKDIR) {
////			scanf("%s%s", path1, name);
////			cmd_mkdir(path1, name);
////		}
////		else if (cmd == CMD_RM) {
////			scanf("%s", path1);
////			cmd_rm(path1);
////		}
////		else if (cmd == CMD_CP) {
////			printf("CP\n");
////			scanf("%s%s", path1, path2);
////			cmd_cp(path1, path2);
////		}
////		else if (cmd == CMD_MV) {
////			printf("MV 명령\n");
////			scanf("%s%s", path1, path2);
////			cmd_mv(path1, path2);
////		}
////		else if (cmd == 6) {
////			for (int i = 0; i < nums; i++) {
////				printf("%s에 대해: ", dirNames[i]);
////				for (int next : child[i]) {
////					printf("%s ", dirNames[next]);
////				}
////				printf("subTreeNums = %d", subtreeNums[i]);
////				puts("");
////			}
////
////		}
////		else {
////			int ret;
////			int answer;
////			printf("FIND");
////			scanf("%s", path1);
////			ret = cmd_find(path1);
////			scanf("%d", &answer);
////			printf("===================내답vs답: %d %d\n", ret, answer);
////		}
////	}
////
////
////}
//
////
////#include <cstdio>
////#include <map>
////#include <string>
////#define MAX_POOL 50000
////#define MAX_NODE 10000
////
////int memPoolCnt;
////struct ListNode {
////	int id;
////	ListNode* prev;
////	ListNode(int i, ListNode* p) : id(i), prev(p) {}
////};
////ListNode listNode[MAX_POOL];
////
////struct TreeNode {
////	int parent;
////	char name[10];
////	ListNode* child;
////};
////TreeNode treeNode[MAX_NODE];
////
////void init() {
////	memPoolCnt = 0;
////	for (int i = 0; i < MAX_NODE; i++) {
////		treeNode[i].parent = -1;
////		treeNode[i].child = nullptr;
////	}
////}
////
////// TLE를 피하려면 어떻게 해야대느느느냐?
////
////
////
////
////int main() {
////	int parent, child;
////
////	scanf("%d %d", &parent, &child);
////
////	treeNode[child].parent = parent;
////
////	ListNode* node = &listNode[memPoolCnt++];
////	node->id = memPoolCnt;
////	node->prev = treeNode[parent].child;
////	treeNode[parent].child = node;
////
////
////}

#include <cstdio>
#include <queue>
using namespace std;
typedef pair<int,int> P;

int T, N, A[10], K;

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", A + i);
		}
		scanf("%d", &K);

		priority_queue<P, vector<P>, greater<P>> PQ;
		PQ.push(P(0, K));


		while (!PQ.empty()) {
			int currLeft = PQ.top().second;
			int currCnt = PQ.top().first;
			PQ.pop();

			if (currLeft == 0) {
				printf("#%d %d\n",t, currCnt);
				break;
			}

			// 이제 그러면 currLeft에서,
			// 실제로 다 써본다고.
			PQ.push(P(currCnt + currLeft, 0));

			// 또는 돌아가면서.
			// 써본다고 하자.
			for (int i = 0; i < N; i++) {
				PQ.push(P(currCnt + currLeft % A[i], currLeft / A[i]));
			}
		}
	}

}