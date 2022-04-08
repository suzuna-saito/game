/*
プリコンパイル済みヘッダー
*/

#ifndef PCH_H
#define PCH_H

using namespace std;

// 外部依存
#include <glew.h>
#include <limits>
#include <SDL.h>

// Math
#include "Math.h"

// FPS
#include "FPS.h"

// InputSystem
#include "InputSystem.h"

// Renderer
#include "Renderer.h"

// Scene
#include "SceneBase.h"
#include "Title.h"

// game
#include "Game.h"

#endif // PCH_H