#include "pch.h"

// ���݂̃V�[���̏�����
SceneBase::Scene SceneBase::mIsScene = Scene::eInit;

SceneBase::SceneBase()
	: mSceneTransitionFlag(false)
{
}