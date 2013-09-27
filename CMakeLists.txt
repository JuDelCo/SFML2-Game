# ----------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# ----------------------------------------------------------------------------------------------

set(EXECUTABLE_NAME "GE_SFML_${CMAKE_BUILD_TYPE}")
set(PROJECT_NAME ${EXECUTABLE_NAME})
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -DSFML_STATIC")
set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-s -O2")
set(SFML_DEBUG_LIBS   "-lmingw32 -lsfml-graphics-s-d -lsfml-audio-s-d -lsfml-window-s-d -lsfml-system-s-d -lopengl32 -lglu32 -static-libgcc -static-libstdc++")
set(SFML_RELEASE_LIBS "-lmingw32 -lsfml-graphics-s   -lsfml-audio-s   -lsfml-window-s   -lsfml-system-s   -lopengl32 -lglu32 -static-libgcc -static-libstdc++ -mwindows")
set(SFML_PATH "C:/Programacion/CppLibs/SFML2_2.1_20130924/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_ENGINE
	Engine/debug/DebugLog.cpp
	Engine/debug/DebugLog.hpp
	Engine/helpers/Event.hpp
	Engine/helpers/Interpolator.cpp
	Engine/helpers/Interpolator.hpp
	Engine/helpers/Motion.cpp
	Engine/helpers/Motion.hpp
	Engine/helpers/TaskInterface.hpp
	Engine/helpers/TaskManager.cpp
	Engine/helpers/TaskManager.hpp
	Engine/helpers/Timer.cpp
	Engine/helpers/Timer.hpp
	Engine/helpers/Util.hpp
	Engine/input/Input.cpp
	Engine/input/Input.hpp
	Engine/input/InputData.hpp
	Engine/video/Sprite.cpp
	Engine/video/Sprite.hpp
	Engine/video/SpriteBatch.cpp
	Engine/video/SpriteBatch.hpp
	Engine/video/TileMap.cpp
	Engine/video/TileMap.hpp
	Engine/video/Video.cpp
	Engine/video/Video.hpp
	Engine/Includes.hpp
	Engine/Defines.hpp
	Engine/GameBase.cpp
	Engine/GameBase.hpp
)
set(SOURCE_GAME
	Game/arkanoid/ArkanoidController.cpp
	Game/arkanoid/ArkanoidController.hpp
	Game/pacman/PacmanController.cpp
	Game/pacman/PacmanController.hpp
	Game/pong/PongController.cpp
	Game/pong/PongController.hpp
	Game/shmup/ShmupController.cpp
	Game/shmup/ShmupController.hpp
	Game/snake/SnakeController.cpp
	Game/snake/SnakeController.hpp
	Game/techdemo/DemoController.cpp
	Game/techdemo/DemoController.hpp
	Game/tetris/TetrisController.cpp
	Game/tetris/TetrisController.hpp
	main.cpp
	Resource/resource.rc
)

# ----------------------------------------------------------------------------------------------

project("${PROJECT_NAME}" CXX)

include_directories("${SFML_PATH}include")
link_directories(   "${SFML_PATH}lib")

add_executable(${EXECUTABLE_NAME} ${SOURCE_ENGINE} ${SOURCE_GAME})

target_link_libraries(${EXECUTABLE_NAME} debug     ${SFML_DEBUG_LIBS})
target_link_libraries(${EXECUTABLE_NAME} optimized ${SFML_RELEASE_LIBS})

# ----------------------------------------------------------------------------------------------
