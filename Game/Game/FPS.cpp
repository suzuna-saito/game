#include "pch.h"

FPS::FPS()
	: MSetFps(60)
	, MOneFrameTickCount(1000 / MSetFps)
	, mFpsCount(0)
	, mFrameStartTickTime(0)
	, mFps(0)
	, mBeforeTickCount(0)
	, mDeltaTime(0)
{
}

void FPS::Update()
{
	Wait();

	mDeltaTime = (SDL_GetTicks() - mBeforeTickCount) / 1000.0f;
	if (mDeltaTime >= 0.10f)
	{
		mDeltaTime = 0.10f;
	}
	mBeforeTickCount = SDL_GetTicks();
	//1フレーム目の時刻を保存
	if (mFpsCount == 0)
	{
		mFrameStartTickTime = SDL_GetTicks();
	}
	//設定したフレーム数が経過したら
	if (mFpsCount == MSetFps)
	{
		int nowTickTime = SDL_GetTicks();
		mFps = 1000 / ((nowTickTime - mFrameStartTickTime) / MSetFps);
		mFpsCount = 0;
	}
	else
	{
		mFpsCount++;
	}
}

void FPS::Wait()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mBeforeTickCount + MOneFrameTickCount));

}
