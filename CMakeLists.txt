cmake_minimum_required(VERSION 3.16)
project(beatcovid)
set(CMAKE_CXX_STANDARD 14)
include_directories(project/include)
include_directories(project/include/tinyxml)
include_directories(project/include/imgui-master)
include_directories( ${OPENGL_INCLUDE_DIRS} )

add_executable(beatcovid
        main.cpp
        project/src/Player.cpp
        project/src/Enemy.cpp
        project/src/Bullet.cpp
        project/src/Level_map.cpp
        project/src/Animation.cpp
        project/src/AnimationManager.cpp
        project/src/Entity.cpp
        project/src/GameManager.cpp
        project/src/Antibodies.cpp
        project/src/GameLables.cpp
        project/src/Arrmor.cpp
        project/src/Robe.cpp
        project/src/Gloves.cpp
        project/src/Glasses.cpp
        project/src/Mask.cpp
        project/include/imgui-master/imgui.cpp
        project/include/imgui-master/imgui_draw.cpp
        project/include/imgui-master/imgui_demo.cpp
        project/include/imgui-master/imgui_widgets.cpp
        project/include/imgui-master/imgui-SFML.cpp
        project/src/Interface.cpp)

add_subdirectory(project/include/tinyxml)

find_package(OpenGL REQUIRED)

find_package(SFML REQUIRED system window graphics network audio)
target_link_libraries(beatcovid sfml-graphics sfml-audio tinyxml ${OPENGL_LIBRARIES})
