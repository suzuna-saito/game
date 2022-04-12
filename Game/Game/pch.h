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

// System
#include "Math.h"
#include "FPS.h"
#include "InputSystem.h"
#include "RapidJsonHelper.h"

// Component
#include "Component.h"

// Renderer
#include "Renderer.h"
#include "VertexArray.h"

// Actor
#include "Actor.h"
#include "Ground.h"

// Scene
#include "SceneBase.h"
#include "Title.h"

// Map
#include "MapCreate.h"

// ObjectManager
#include "ObjectManager.h"

// game
#include "Game.h"

#endif // PCH_H