// stdafx.h include all header files

#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows stuff that we might use 
#define VC_EXTRALEAN
#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#define GLM_FORCE_RADIANS

#if !(defined(DEBUG) | defined(_DEBUG))
#define NDEBUG
#endif

// reference additional headers that are added in later here
#include <glm-0.9.8.5\glm\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.5\glm\glm\gtc\quaternion.hpp>
#include <glm-0.9.8.5\glm\glm\gtx\quaternion.hpp>
#include <glm-0.9.8.5\glm\glm\gtx\euler_angles.hpp>
#include <glm-0.9.8.5\glm\glm\glm.hpp>

#include <OpenGLDep\headers\glew.h>
#include <OpenGLDep\headers\glfw3.h>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <chrono>
#include <string>
#include <memory>
#include <map>
#include <initializer_list>
#include <random>
#include <functional>
#include <cassert>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
