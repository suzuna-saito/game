#include "pch.h"

// 現在のシーンの初期化
SceneBase::Scene SceneBase::mIsScene = Scene::eInit;

SceneBase::SceneBase()
	: mSceneTransitionFlag(false)
	, mMapCreate(nullptr)
{
}