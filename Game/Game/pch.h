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
#include <SDL_image.h>
#include <unordered_map>
#include <vector>

// System
#include "Math.h"
#include "FPS.h"
#include "InputSystem.h"
#include "RapidJsonHelper.h"

// Shader
#include "Shader.h"

// Component
#include "Component.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

// Renderer
#include "Texture.h"
#include "VertexArray.h"
#include "Mesh.h"
#include "Renderer.h"

// Scene
#include "SceneBase.h"
#include "Title.h"

// Actor
#include "Actor.h"
#include "Camera.h"
#include "Ground.h"

// ActorManager
#include "ActorManager.h"

// Map
#include "MapCreate.h"

// game
#include "Game.h"

#endif // PCH_H