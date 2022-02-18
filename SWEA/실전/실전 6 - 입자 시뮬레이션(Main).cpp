#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <ctime>

#define INIT				(100)
#define INSERT_PARTICLE		(200)
#define REMOVE_PARTICLE		(300)
#define FIND_NEAR_PARTICLE	(400)
#define GO					(500)

extern void init(int L, int R);
extern void insertParticle(int mID, int mPx, int mPy, int mPz, int mVx, int mVy, int mVz);
extern void removeParticle(int mID);
extern int findNearParticle(int mID);
extern void go(int mTick);

static unsigned int mSeed;

static int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (int)((mSeed >> 16) & 0x7FFF);
}

static bool run()
{
	int Q;
	int L = 0, R;

	int mID;
	int mPx, mPy, mPz, mVx, mVy, mVz;
	int mTick;

	int ret = -1, ans;
	int mSeq = 1;

	scanf("%d %d", &Q, &mSeed);

	bool okay = false;
	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			scanf("%d %d", &L, &R);
			init(L, R);
			okay = true;
			break;
		case INSERT_PARTICLE:
			mPx = pseudo_rand() % (L + L - 1) - L + 1;
			mPy = pseudo_rand() % (L + L - 1) - L + 1;
			mPz = pseudo_rand() % (L + L - 1) - L + 1;
			mVx = pseudo_rand() % (L + L + 1) - L;
			mVy = pseudo_rand() % (L + L + 1) - L;
			mVz = pseudo_rand() % (L + L + 1) - L;
			if (okay)
				insertParticle(mSeq, mPx, mPy, mPz, mVx, mVy, mVz);
			++mSeq;
			break;
		case REMOVE_PARTICLE:
			scanf("%d", &mID);
			if (okay)
				removeParticle(mID);
			break;
		case FIND_NEAR_PARTICLE:
			scanf("%d", &mID);
			if (okay)
				ret = findNearParticle(mID);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			break;
		case GO:
			scanf("%d", &mTick);
			if (okay)
				go(mTick);
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d%d", &T, &MARK);

	clock_t start = clock();
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	clock_t end = clock();

	printf("รั : %lld\n", end - start);

	return 0;
}