/*
プリコンパイル済みヘッダー
*/

#ifndef PCH_H
#define PCH_H

using namespace std;

// 外部依存
#include <document.h>
#include <fstream>
#include <glew.h>
#include <sstream>
#include <SDL.h>
#include <vector>

// Math
#include "Math.h"

// FPS
#include "FPS.h"

// InputSystem
#include "InputSystem.h"

// Component
#include "Component.h"

// Renderer
#include "Renderer.h"

// Actor
#include "Actor.h"

// Scene
#include "SceneBase.h"
#include "Title.h"

// RapidJson
#include "RapidJsonHelper.h"

// Map
#include "MapCreate.h"

// ObjectManager
#include "ObjectManager.h"

// game
#include "Game.h"

#endif // PCH_H