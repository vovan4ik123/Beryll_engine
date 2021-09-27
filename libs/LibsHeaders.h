#pragma once

// this file includes all libs needed for engine
// include this file only inside engine

#include "SDL2/include/SDL.h"

#include "SDL2_image/SDL_image.h"

#include "SDL2_mixer/SDL_mixer.h"

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/android_sink.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "assimp/include/assimp/scene.h"
#include "assimp/include/assimp/Importer.hpp"
#include "assimp/include/assimp/postprocess.h"

#include "sqlite/sqlite3.h"

#include "bullet/btBulletDynamicsCommon.h"
#include "bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"

// OpenGL 4.3 (GLSL #version 430) == GLES 3.0 (GLSL #version 300 es)